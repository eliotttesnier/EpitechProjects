const express = require('express');
const router = express.Router();
const jwt = require('jsonwebtoken');
const bcrypt = require('bcryptjs');
const pool = require('../../config/db');
const {notFound, errorHandler } = require('../../middleware/notFound');
const {checkArgumentsLogin, checkArgumentsRegister, verifyToken} = require('../../middleware/auth');
const SECRET = process.env.SECRET

router.post('/register', checkArgumentsRegister, (req, res) => {
    const { email, password, name, firstname } = req.body;

    bcrypt.hash(password, 10, (hashErr, hashedPassword) => {
        pool.query('INSERT INTO user (email, password, name, firstname) VALUES (?, ?, ?, ?)', [email, hashedPassword, name, firstname], (err, results) => {
            if (err) {
                if (err.code === 'ER_DUP_ENTRY') {
                    res.status(400).json({ msg: 'Account already exists' });
                    return;
                }
                errorHandler(err, req, res);
                return;
            }
            const token = jwt.sign({ email }, SECRET, { expiresIn: '1h' });

            res.status(201).json({ token });
        });
    });
});

router.post('/login', checkArgumentsLogin, (req, res) => {
    const { email, password } = req.body;

    pool.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
        if (err) {
            errorHandler(err, req, res);
            return;
        }

        if (results.length === 0) {
            res.status(401).json({ msg: 'Invalid Credentials' });
            return;
        }

        const user = results[0];
        const valid = await bcrypt.compare(password, user.password);

        if (valid == false) {
            res.status(401).json({ msg: 'Invalid Credentials' });
            return;
        }

        const token = jwt.sign({ email: user.email }, SECRET, { expiresIn: '1h' });
        res.status(200).json({ token });
    });
});

router.get('/user', verifyToken, (req, res) => {
    const email = req.user.email;
    getUserByEmail(email, (err, user) => {
        if (!user) {
            notFound(req, res);
            return;
        }
        res.status(200).json(user);
    });
});

router.get('/user/todos', verifyToken, (req, res) => {
    const email = req.user.email;
    getUserByEmail(email, (err, user) => {
        if (!user) {
            notFound(req, res);
            return;
        }
        getTodosById(user.id, (error, todos) => {
            if (error) {
                return;
            }
            res.status(200).json(todos);
        });
    })
});

const getTodosById = (id, callback) => {
    pool.query('SELECT * FROM todo WHERE user_id = ?', [id], (err, results) => {
        if (err) {
            errorHandler(err, null);
            return;
        }
        callback(null, results);
    });
};

const getUserByEmail = (email, callback) => {
    pool.query('SELECT * FROM user WHERE email = ?', [email], (err, results) => {
        if (err) {
            errorHandler(err, null);
            return;
        }
        callback(null, results[0]);
    });
};

module.exports = router;
