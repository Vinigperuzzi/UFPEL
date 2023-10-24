const jwt = require('jsonwebtoken');

function auth(req, res, next) {
    const token = req.header('auth-token');
    if(!token) return res.status(400).json("not auth");

    try{
        const verified = jwt.verify(token, process.env.JWT_TOKEN_SECRET);
        req.user = verified;
    }catch(err){
        res.status(400).json("ivalid token");
    }
}