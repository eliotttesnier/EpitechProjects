const express = require('express');
const router = express.Router();
const { getEveryTask, getTaskById, addTask, updateTaskById, deleteTaskById} = require('./todos.query');
const {notFound, errorHandler, badParameter} = require('../../middleware/notFound')
const {checkArgumentsLogin, checkArgumentsRegister, verifyToken} = require('../../middleware/auth');

router.get('/', verifyToken, (req, res) => {
    getEveryTask((err, task) => {
        if (!task) {
            notFound(req, res);
            return;
        }
        res.status(200).json(task);
    });
});

router.get('/:id', verifyToken, (req, res) => {
    const id = req.params.id;

    if (!id) {
        badParameter(req, res);
        return;
    }
    getTaskById(id, (err, task) => {
        if (err) {
            errorHandler(err, req, res);
            return;
        }
        if (!task) {
            notFound(req, res);
            return;
        }
        res.status(200).json(task);
    });
});

router.post('/', verifyToken, (req, res) => {
    const { title, description, due_time, user_id, status } = req.body;

    if (!title || !description || !due_time || !user_id || !status) {
        badParameter(req, res);
        return;
    }
    addTask({ title, description, due_time, user_id, status }, (err, task) => {
        if (err) {
            console.log(err);
            errorHandler(err, req, res);
            return;
        }
        res.status(201).json(task);
    });
});

router.put('/:id', verifyToken, (req, res) => {
    const id = req.params.id;
    const args = req.body;

    if (!id || !args.title || !args.description) {
        badParameter(req, res);
        return;
    }
    updateTaskById(id, args, (err, task) => {
        if (err) {
            errorHandler(req, res);
            return;
        }
        if (!task) {
            notFound(req, res);
            return;
        }
        res.status(200).json(task);
    });
});

router.delete('/:id', verifyToken, (req, res) => {
    const id = req.params.id;

    if (!id) {
        badParameter();
        return;
    }
    deleteTaskById(id, (err, result) => {
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
