console.log("Welcome to Deno 🦕");

const url = Deno.args[0] || "https://github.com";
const res = await fetch(url);

const body = new Uint8Array(await res.arrayBuffer());
await Deno.stdout.write(body);
