import {Router, Request, Response} from 'express';
import sb from "./supabase";

const router = Router();

router.get('/', index);
router.get('/hello/:name', hello);
router.post('/signup', signup);
router.post('/login', login);

function index(req: Request, res: Response) {
    res.send('hello world!');
}

function hello(req: Request, res: Response) {
    const name = req.params.name ?? "world";
    res.send(`hello ${name}!`);
}

interface User {
    email: string;
    password: string;
}

async function signup(req: Request<{}, {}, User>, res: Response) {
    const {email, password} = req.body;
    const {data, error} = await sb.auth.signUp({
        email,
        password
    })

    if (error) {
        res.status(400).send(error.message);
        return;
    }
    res.send(data);
}

async function login(req: Request<{}, {}, User>, res: Response) {
    const {email, password} = req.body;
    const {data, error} = await sb.auth.signInWithPassword({
        email,
        password
    })
    if (error) {

        res.status(400).send(error.message);
        return;
    }
    res.send(data);
}

export default router;
