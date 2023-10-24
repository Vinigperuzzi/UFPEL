const {sign, verify} = require('jsonwebtoken')

const createTokens = (user) => {
    const accessToken = sign({
            username: user.email},
            process.env.JWT_TOKEN_SECRET,
        {expiresIn: 60*60*24}
        )

    return accessToken;
}

const validateToken = (req, res, next) => {
    const accessToken = req.headers['where-access-token']

    //Verify if user has the cookie
    if (!accessToken) {
        return res
            .status(400)
            .json({auth: false, error: "No cookie."});
    }

    try {
        //Verify if token is valid
        const validToken = verify(accessToken, process.env.JWT_TOKEN_SECRET)
        if (validToken){
            req.authenticated = true;
            req.username = validToken.username;
            req.responseJson = {auth:true}
            return next();
        }
    } catch(err){
        return res.status(400).json({auth: false, error: err});
    }
}


module.exports = { createTokens, validateToken }
