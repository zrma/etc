import "@/app/globals.css";
import type { GetServerSideProps, InferGetServerSidePropsType } from "next";
import { client, type Post as BlogPost } from "@/pages/api/post";

type SerializedPost = Omit<BlogPost, "created_at"> & {
  created_at: string;
};

export const getServerSideProps = (async (context) => {
  const id = context.params?.id;
  if (typeof id !== "string") {
    return { notFound: true };
  }

  const [post] = await client.query<BlogPost>(
    `
      select BlogPost {
        id,
        title,
        content,
        created_at,
      }
      filter .id = <uuid>$id;
    `,
    { id },
  );

  if (!post) {
    return { notFound: true };
  }

  return {
    props: {
      post: {
        id: post.id,
        title: post.title,
        content: post.content,
        created_at: post.created_at.toISOString(),
      },
    },
  };
}) satisfies GetServerSideProps<{ post: SerializedPost }>;

export type GetPost = InferGetServerSidePropsType<typeof getServerSideProps>;

const Post = (props: GetPost) => {
  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gray-200">
      <main className="w-full max-w-2xl px-4 py-8 mx-auto bg-gray-300 rounded-lg shadow-md h-[610px] overflow-auto">
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
