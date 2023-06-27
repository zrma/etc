import "@/app/globals.css";
import { GetServerSidePropsContext, InferGetServerSidePropsType } from "next";
import { client } from "@/pages/api/post";
import e from "@/../dbschema/edgeql-js";

export const getServerSideProps = async (
  context?: GetServerSidePropsContext
) => {
  const post = await e
    .select(e.BlogPost, (post) => ({
      id: true,
      title: true,
      content: true,
      created_at: true,
      filter_single: e.op(post.id, "=", e.uuid(context!.params!.id as string)),
    }))
    .run(client);
  return {
    props: {
      post: {
        id: post!.id,
        title: post!.title,
        content: post!.content,
        created_at: JSON.parse(JSON.stringify(post!.created_at)),
      },
    },
  };
};

export type GetPost = InferGetServerSidePropsType<typeof getServerSideProps>;

const Post: React.FC<GetPost> = (props) => {
  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gray-200">
      <main className="w-full max-w-2xl px-4 py-8 mx-auto bg-gray-300 rounded-lg shadow-md h-[720px] overflow-auto">
        <h1 className="text-3xl font-semibold text-center text-gray-700">
          {props.post.title}
        </h1>
        <p className="mt-4 text-xl font-semibold text-gray-700">
          {props.post.content}
        </p>
        <p className="mt-4 text-l text-right font-semibold text-gray-500">
          {new Date(props.post.created_at).toLocaleString()}
        </p>
      </main>
    </div>
  );
};

export default Post;
