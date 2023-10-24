const express = require('express');
const router = express.Router();
const jwt = require('jsonwebtoken')
const { usuarios } = require('../models');

require('dotenv').config();

const bcrypt = require('bcrypt')
const {loginValidation} = require("../utils/validation");
const { createTokens } = require("../utils/JWT")

router.post('/', async function(req, res,next){

    req.responseJson = {}

    //Create flags
    req.responseJson.isValidated = false
    req.responseJson.isUser = false
    req.responseJson.validPassword = false


    // Validate fields
    const {error} = loginValidation(req.body);
    if(error) {
        req.responseJson.error = error.details[0].message;
        return res.status(400).json(req.responseJson);
    }
    req.responseJson.isValidated = true;

    // Search email
    const user = await usuarios.findOne({ where: {email: req.body.email}});
    if (!user) return res.status(400).json(req.responseJson);
    req.responseJson.isUser = true;

    // Verify password
    const validPass = await bcrypt.compare(req.body.password, user.senha);
    if(!validPass) return res.status(400).json(req.responseJson);
    req.responseJson.validPassword = true;


    //Create Token
    try {
        const accessToken = createTokens(user);
        return res.status(200)
            .cookie('where-access-token', accessToken)
            .json({isLogged: true, cookieName: 'where-access-token', cookieInfo: accessToken});
    } catch(error) {
        //Failed to create tokend
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }
});

module.exports = router;

