import Head from "next/head";
import "@/app/globals.css";
import { GetServerSideProps } from "next";
import { Posts } from "@/pages/api/post";
import { useState } from "react";
import { req } from "@/api/fetch";

export default function Home({ posts }: { posts: Posts }) {
  const [title, setTitle] = useState("");
  const [content, setContent] = useState("");

  const submitPost = async () => {
    const resp = await fetch("/api/post", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ title, content }),
    });

    if (resp.ok) {
      // Refresh the page to show the new post
      window.location.reload();
    } else {
      console.error("Failed to create post");
    }
  };

  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gray-200">
      <Head>
        <title>Memo</title>
        <meta name="description" content="My awesome memo site" />
        <link rel="icon" href="/src/app/favicon.ico" />
      </Head>

      <main className="w-full max-w-2xl px-4 py-8 mx-auto bg-gray-300 rounded-lg shadow-md h-[610px] flex flex-col">
        <h1 className="text-3xl font-semibold text-center text-gray-700">
          Memo
        </h1>
        <div className="mt-4">
          <input
            id="new-title-input"
            name="new-title-input"
            placeholder="Write your title..."
            className="w-full px-3 py-2 mb-1 text-gray-700 border rounded-lg focus:outline-none"
            onChange={(e) => setTitle(e.target.value)}
          />
          <textarea
            id="new-content-input"
            name="new-content-input"
            placeholder="Write your content..."
            className="w-full px-3 py-2 text-gray-700 border rounded-lg focus:outline-none"
            rows={4}
            onChange={(e) => setContent(e.target.value)}
          />
          <button
            type="submit"
            className={`w-full px-4 py-2 font-semibold text-white bg-gray-400 rounded ${
              !title ? "opacity-50 hover:bg-neutral-500" : "hover:bg-blue-300"
            }`}
            onClick={submitPost}
            disabled={!title}
          >
            Post
          </button>
        </div>

        <div className="mt-6 overflow-auto scrollbar scrollbar-thumb-gray-400 scrollbar-track-gray-200">
          {posts.map((post) => {
            return (
              <a href={`/post/${post.id}`} key={post.id} className="block mt-4">
                <div className="text-xl font-semibold text-gray-700">
                  {trimString(post.title, 50)}
                </div>
              </a>
            );
          })}
        </div>
      </main>
    </div>
  );
}

const trimString = (str: string, length: number) => {
  return str.length > length ? str.substring(0, length) + "..." : str;
};

export const getServerSideProps: GetServerSideProps = async () => {
  const resp = await req(`/api/post`);
  const posts: Posts = await resp.json();

  return {
    props: {
      posts,
    },
  };
};
