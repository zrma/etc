export const req = (route: string, method: string = "GET", body?: any) => {
  const url = `${process.env.NEXT_PUBLIC_API_URL}${route}`;
  const options = {
    method,
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(body),
  };

  return fetch(url, options);
};
