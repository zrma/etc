import Head from "next/head";
import "@/app/globals.css";
import { GetServerSideProps } from "next";
import { Posts } from "@/pages/api/post";

export default function Home({ posts }: { posts: Posts }) {
  if (!posts) {
    return (
      <div className="flex flex-col items-center justify-center min-h-screen py-2">
        <Head>
          <title>Loading...</title>
          <meta name="description" content="My awesome memo site" />
          <link rel="icon" href="/src/app/favicon.ico" />
        </Head>
      </div>
    );
  }

  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gray-200">
      <Head>
        <title>Memo</title>
        <meta name="description" content="My awesome memo site" />
        <link rel="icon" href="/src/app/favicon.ico" />
      </Head>

      <main className="w-full max-w-2xl px-4 py-8 mx-auto bg-gray-300 rounded-lg shadow-md h-[720px] overflow-auto">
        <h1 className="text-3xl font-semibold text-center text-gray-700">
          Memo
        </h1>
        <div className="mt-4">
          <textarea
            id="new-msg-input"
            name="new-msg-input"
            placeholder="Write your new post..."
            className="w-full px-3 py-2 text-gray-700 border rounded-lg focus:outline-none"
            rows={4}
          />
          <button
            type="submit"
            className="w-full px-4 py-2 mt-2 font-semibold text-white bg-blue-400 rounded hover:bg-blue-300"
          >
            Post
          </button>
        </div>

        <div className="mt-6">
          {posts.map((post) => {
            return (
              <a href={`/post/${post.id}`} key={post.id} className="block mt-4">
                <div className="text-xl font-semibold text-gray-700">
                  {post.title}
                </div>
              </a>
            );
          })}
        </div>
      </main>
    </div>
  );
}

export const getServerSideProps: GetServerSideProps = async () => {
  const resp = await fetch(`http://localhost:3000/api/post`);
  const posts: Posts = await resp.json();

  return {
    props: {
      posts,
    },
  };
};
