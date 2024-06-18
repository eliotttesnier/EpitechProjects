const express = require('express');
const router = express.Router();
const { getEveryUser, getUserById, getUserByEmail, updateUserById, deleteUserById} = require('./user.query');
const {notFound, errorHandler, badParameter} = require('../../middleware/notFound')
const {checkArgumentsLogin, checkArgumentsRegister, verifyToken} = require('../../middleware/auth');

router.get('/:id', verifyToken, (req, res) => {
    const id = req.params.id;

    if (!id) {
        badParameter(req, res);
        return;
    }
    getUserById(id, (err, user) => {
        if (!user) {
            getUserByEmail(id, (err, user) => {
                if (!user) {
                    notFound(req, res);
                    return;
                }
                res.json(user);
            })
            return;
        }
        res.status(200).json(user);
    });
});

router.put('/:id', verifyToken, (req, res) => {
    const id = req.params.id;
    const args = req.body;

    if (!id || !args.email || !args.password || !args.firstname || !args.name) {
        badParameter(req, res);
        return;
    }
    updateUserById(id, args, (err, user) => {
        if (err) {
            if (err.code === 'ER_DUP_ENTRY') {
                badParameter(req, res);
                return;
            }
            errorHandler(req, res);
            return;
        }
        if (!user) {
            notFound(req, res);
            return;
        }
        res.status(200).json(user);
    });
});

router.delete('/:id', verifyToken, (req, res) => {
    const id = req.params.id;

    if (!id) {
        badParameter();
        return;
    }
    deleteUserById(id, (err, result) => {
        if (err) {
            errorHandler(err, req, res);
            return;
        }
        if (!result.affectedRows) {
            notFound(req, res);
            return;
        }
        res.status(200).json({ msg: `Successfully deleted record number: ${id}` });
    });
})

module.exports = router;
