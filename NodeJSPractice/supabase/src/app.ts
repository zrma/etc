import express from 'express';

import route from './route';
import bodyParser from "body-parser";

const app = express();
const port = 8888;

app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());
app.use("/", route);

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
