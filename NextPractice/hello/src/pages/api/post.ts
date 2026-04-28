import type { NextApiRequest, NextApiResponse } from "next";
import { createClient } from "edgedb";

export const client = createClient();

export interface Post {
  id: string;
  title: string;
  content: string;
  created_at: Date;
}

export type Posts = Post[];

const selectPostsQuery = `
  select BlogPost {
    id,
    title,
    content,
    created_at,
  }
  order by .created_at desc;
`;

const insertPostQuery = `
  insert BlogPost {
    title := <str>$title,
    content := <str>$content,
  };
`;

const deleteOldPostsQuery = `
  delete (
    select BlogPost
    order by .created_at desc
    offset 6
  );
`;

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse,
) {
  const actions = {
    POST: async () => {
      const { title, content } = req.body;

      await client.transaction(async (tx) => {
        await tx.execute(insertPostQuery, { title, content });
        await tx.execute(deleteOldPostsQuery);
      });
      res.status(200).json({ message: "Post created" });
    },
    GET: async () => {
      const posts = await client.query<Post>(selectPostsQuery);
      res.status(200).json(posts);
    },
  };

  const method = req.method as "POST" | "GET";
  const action = actions[method];

  if (action) {
    await action();
  } else {
    res.status(405).end(); // Method Isn't Allowed
  }
}
