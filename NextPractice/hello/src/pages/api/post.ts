import type { NextApiRequest, NextApiResponse } from "next";
import { createClient } from "edgedb";
import e, { $infer } from "@/../dbschema/edgeql-js";

export const client = createClient();

const selectPosts = e.select(e.BlogPost, (post) => ({
  id: true,
  title: true,
  content: true,
  created_at: true,

  order_by: {
    expression: post.created_at,
    direction: e.DESC,
  },
}));

const insertPost = (title: string, content: string) => {
  return e.insert(e.BlogPost, {
    title: title,
    content: content,
  });
};

const deleteOldPosts = () => {
  const targets = e.select(e.BlogPost, (post) => ({
    id: true,
    created_at: true,
    order_by: {
      expression: post.created_at,
      direction: e.DESC,
    },
    offset: 6,
  }));
  return e.delete(targets);
};

export type Posts = $infer<typeof selectPosts>;

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse
) {
  const actions = {
    POST: async () => {
      const { title, content } = req.body;

      await client.transaction(async (tx) => {
        await insertPost(title, content).run(tx);
        await deleteOldPosts().run(tx);
      });
      res.status(200).json({ message: "Post created" });
    },
    GET: async () => {
      const posts = await selectPosts.run(client);
      res.status(200).json(posts);
    },
  };

  const method = req.method as "POST" | "GET";
  const action = actions[method];

  if (action) {
    await action();
  } else {
    res.status(405).end(); // Method Not Allowed
  }
}
