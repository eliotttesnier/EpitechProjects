const pool = require('../../config/db');
const {errorHandler, badParameter} = require('../../middleware/notFound');

const getEveryTask = (callback) => {
    pool.query('SELECT * FROM todo', (err, results) => {
        if (err) {
            errorHandler();
            return;
        }
        callback(null, results);
    });
}

const getTaskById = (id, callback) => {
    pool.query('SELECT * FROM todo WHERE id = ?', [id], (err, results) => {
        if (err) {
            errorHandler(err, null);
            return;
        }
        callback(null, results[0]);
    });
};

const addTask = (args, callback) => {
    const { title, description, due_time, user_id, status } = args;

    pool.query('INSERT INTO todo (title, description, due_time, user_id, status) VALUES (?, ?, ?, ?, ?)', [title, description, due_time, user_id, status], (err, result) => {
        if (err) {
            callback(err, null)
            return;
        }
        getTaskById(result.insertId, callback);
    });
};

const updateTaskById = (id, args, callback) => {
    const { title, description} = args;

    pool.query('UPDATE todo SET title = ?, description = ? WHERE id = ?', [title, description, id], (err, results) => {
            if (err) {
                callback(err, null);
                return;
            }
            getTaskById(id, callback);
        }
    );
};

const deleteTaskById = (id, callback) => {
    pool.query('DELETE FROM todo WHERE id = ?', [id], (err, result) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, result);
    });
};

module.exports = {
    getEveryTask,
    getTaskById,
    addTask,
    updateTaskById,
    deleteTaskById
};
