import * as request from "supertest";
import router from './route';
import express from "express";

const app = express();
app.use('/', router);

describe('Good Home Routes', function () {

    test('responds to /', async () => {
        const res = await request.default(app).get('/');
        expect(res.header['content-type']).toBe('text/html; charset=utf-8');
        expect(res.statusCode).toBe(200);
        expect(res.text).toEqual('hello world!');
    });

    test('responds to /hello/:name', async () => {
        const res = await request.default(app).get('/hello/jaxnode');
        expect(res.header['content-type']).toBe('text/html; charset=utf-8');
        expect(res.statusCode).toBe(200);
        expect(res.text).toEqual('hello jaxnode!');
    });

    test('responds to /hello/Annie', async () => {
        const res = await request.default(app).get('/hello/Annie');
        expect(res.header['content-type']).toBe('text/html; charset=utf-8');
        expect(res.statusCode).toBe(200);
        expect(res.text).toEqual('hello Annie!');
    });
});