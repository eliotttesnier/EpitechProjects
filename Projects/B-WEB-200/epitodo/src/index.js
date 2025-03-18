require('dotenv').config();
const { PORT, MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_ROOT_PASSWORD } = process.env;

const express = require('express');
const pool = require('./config/db');

const app = express();

const authRouter = require('./routes/auth/auth');
const userRouter = require('./routes/user/user')
const todoRouter = require('./routes/todos/todos')

app.use(express.json());
app.use('/', authRouter);
app.use('/users', userRouter);
app.use('/todos', todoRouter);

app.listen(PORT, () => {
    console.log(`Epytodo app listening on port ${PORT}`);
});
