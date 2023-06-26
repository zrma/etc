import React from "react";
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
    <div
      style={{
        margin: "auto",
        width: "100%",
        maxWidth: "600px",
      }}
    >
      <h1 style={{ padding: "50px 0px" }}>{props.post.title}</h1>
      <p style={{ color: "#666" }}>{props.post.content}</p>
      <p style={{ color: "#999" }}>{props.post.created_at}</p>
    </div>
  );
};

export default Post;
