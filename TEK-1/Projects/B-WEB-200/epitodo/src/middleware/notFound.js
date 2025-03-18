function notFound(req, res, next)
{
    res.status(404).json({ msg: 'Not found' });
}

function badParameter(req, res)
{
    res.status(400).json({ msg: 'Bad parameter' });
}

function errorHandler(err, req, res, next)
{
    res.status(500).json({ msg: 'Internal server error' });
}

module.exports = {
    notFound,
    errorHandler,
    badParameter
};
