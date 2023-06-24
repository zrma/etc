"use client";
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
          <meta name="description" content="My awesome blog" />
          <link rel="icon" href="/src/app/favicon.ico" />
        </Head>
      </div>
    );
  }

  return (
    <div className="flex flex-col items-center justify-center min-h-screen py-2">
      <Head>
        <title>My Blog</title>
        <meta name="description" content="My awesome blog" />
        <link rel="icon" href="/src/app/favicon.ico" />
      </Head>

      <main className="flex flex-col items-center justify-center flex-1 px-20 text-center">
        <h1 className="text-6xl font-bold">Blog</h1>
        <div style={{ height: "50px" }}></div>
        {posts.map((post) => {
          return (
            <a href={`/post/${post.id}`} key={post.id}>
              <div className={`mb-3 text-2xl font-semibold`}>
                <p>{post.title}</p>
              </div>
            </a>
          );
        })}
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
