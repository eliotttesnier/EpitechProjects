function checkArgumentsRegister(req, res, next) {
    const { email, password, name, firstname} = req.body;
    if (!email || !password || !name || !firstname) {
        res.status(400).json({ msg: 'Bad parameter' });
        return;
    }
    next();
}

function checkArgumentsLogin(req, res, next) {
    const { email, password} = req.body;
    if (!email || !password) {
        res.status(400).json({ msg: 'Bad parameter' });
        return;
    }
    next();
}

const jwt = require('jsonwebtoken');
const SECRET = process.env.SECRET;

function verifyToken(req, res, next) {
    const token = req.headers.authorization;

    if (!token) {
        return res.status(401).json({ msg: 'No token, authorization denied' });
    }

    try {
        const decoded = jwt.verify(token.split(' ')[1], SECRET);
        req.user = decoded;
        next();
    } catch (error) {
        return res.status(401).json({ msg: 'Token is not valid' });
    }
};


module.exports = {
    checkArgumentsRegister,
    checkArgumentsLogin,
    verifyToken,
};
