
const pool = require('../../config/db');
const {errorHandler, badParameter} = require('../../middleware/notFound');

const getUserById = (id, callback) => {
    pool.query('SELECT * FROM user WHERE id = ?', [id], (err, results) => {
        if (err) {
            errorHandler(err, null);
            return;
        }
        callback(null, results[0]);
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

const getEveryUser = (callback) => {
    pool.query('SELECT * FROM user', (err, results) => {
        if (err) {
            errorHandler();
            return;
        }
        callback(null, results);
    });
}

const updateUserById = (id, updatedUser, callback) => {
    const { email, password, firstname, name } = updatedUser;

    pool.query('UPDATE user SET email = ?, password = ?, firstname = ?, name = ? WHERE id = ?', [email, password, firstname, name, id], (err, results) => {
            if (err) {
                callback(err, null);
                return;
            }
            getUserById(id, callback);
        }
    );
};

const deleteUserById = (id, callback) => {
    pool.query('DELETE FROM user WHERE id = ?', [id], (err, result) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, result);
    });
};

module.exports = {
    getEveryUser,
    getUserById,
    getUserByEmail,
    updateUserById,
    deleteUserById
};
