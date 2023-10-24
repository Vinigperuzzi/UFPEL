const express = require('express');
const router = express.Router();
const { participam, eventos, usuarios, promoters} = require('../models');
const {registerValidation, editUserValidation} = require('../utils/validation')
const bcrypt = require('bcrypt')
const {validateToken} = require("../utils/JWT");

//Get user info
router.get('/', validateToken, async function(req,res,next) {
    try {
        const user = await usuarios.findOne({where: {email: req.username}});
        if(!user) return res.json("rroer")

        return res.status(200).json({
            cpf: user.cpf,
            nome: user.nome,
            foto: user.foto,
            descricao: user.descricao,
            dataNasc: user.dataNasc,
            email: user.email
        })
    } catch (error){
        return res.status(400).json(error);
    }
})

// CREATE: Create new user
//
// JSON INPUT
// {
//     "email": "STRING",
//     "password": "STRING",
//     "name": "STRING,
//     "date": "YYYY-MM-DD"
// }
router.post('/create', async function(req, res, next) {

    //Create flags


    // Validate fields
    const {error} = registerValidation(req.body);
    if(error) return res.status(400).json({ isValidated:false, error:error.details[0].message});

    // Check if user is already in database
    const email = await usuarios.findOne({ where: {email: req.body.email}});
    if(email) {
        return res.status(400).json({isValidated:true, validEmail:false});
    }

    //Hash password
    const salt = await bcrypt.genSalt(10);
    const hashPassword = await bcrypt.hash(req.body.password, salt);

    // Create user
    try {
        await usuarios.create({
            email: req.body.email,
            senha: hashPassword,
            nome: req.body.name,
            dataNasc: req.body.date
        });
        return res.status(200).json({isCreated:true});
    } catch (error){
        return res.status(400).json({
            isValidated:true,
            validEmail:true,
            isCreated:false,
            error});
    }


})

// ROTA DE EVENTOS POSSUI UM MELHOR
// READ: Get list of confirmed events from logged user ----- EVE
//
router.get('/confirmed', validateToken, async function(req, res, next) {

    try {
        const codEvents = await participam.findAll({attributes: ['codEvento_fk'], where: {email_fk: req.username}});

        const listEvents = await eventos.findAll({where: {codEvento_fk: codEvents, confirmado: true}});
        listEvents.email_fk = undefined;

        return res.status(200).json(listEvents);
    } catch( error ){
        res.status(400).json("Database error ")
    }
})

// ROTA DE EVENTOS POSSUI UM MELHOR
//Get list of confirmed events from logged user
router.get('/interested', validateToken, async function(req, res, next) {

    try {

        const codEvents = await participam.findAll({attributes: ['codEvento_fk'], where: {email_fk: req.username}});
        console.log(codEvents)
        idArray = []
        codEvents.forEach(eventId => idArray.push(eventId.dataValues.codEvento_fk))
        console.log(idArray)
        const listEvents = await eventos.findAll({where: {codEvento_fk: codEvents, confirmado: false}});
        listEvents.email_fk = undefined;

        return res.status(200).json(listEvents);
    } catch (error) {
        res.status(400).json("Database Error");
    }
})

//Edit user information
router.put('/edit', validateToken, async function(req,res,next){

    // Create flags
    req.responseJson.isValidated = false;
    req.responseJson.isEdited = false;

    //Validate input
    const {error} = editUserValidation(req.body);
    if(error) {
        req.responseJson.error = error.details[0].message;
        return res.status(400).json(req.responseJson);
    }

    try {
        await usuarios.update({
            nome: req.body.nome,
            cpf: req.body.cpf,
            descricao: req.body.descricao,
            dataNasc: req.body.dataNasc,
        }, {where: {
                email_fk: req.username
                }})
        return res.status(200).json({isEdited: true});
    } catch(error) {
        return res.status(400).json(req.responseJson);
    }
})

//Delete user
router.delete('/', validateToken, async function(req, res, next) {

    //Create flags
    req.responseJson.isDeleted = false

   try {
       await usuarios.destroy({ where: {
           email_fk: req.username
           }
       })
       return res.status(200).json({isDeleted: true});
   } catch (error) {
       return res.status(400).json(req.responseJson);
   }
})

// Upgrade user to promoter
router.post('/upgrade', validateToken, async function(req,res,next){

    //Create flags
    req.responseJson.isPromoter = null

    //Verify if user is already promoter
    const isPromoter = await promoters.findOne({where :{email_fk:req.username}})
    if(isPromoter) {
        req.responseJson.alreadyPromoter = true
        return res.status(400).json(req.responseJson);
    }
    req.responseJson.isPromoter = true

    try {
        await promoters.create({
            email_fk: req.username
        });
        return res.status(200).json({isUpgraded: true})
    } catch (error){
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }
})




router.get('/promoter', validateToken, async function(req, res, next) {
    req.responseJson.isPromoter = false;

    try {
        const user = await promoters.findOne({where : {
            email_fk: req.username
            }})
        if(!user) return res.status(200).json(req.responseJson);
        req.responseJson.isPromoter = true;

        return res.status(200).json(req.responseJson);
    } catch(error) {
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }
})


router.post('/downgrade', validateToken, async function(req,res,next){

    //Create flags
    req.responseJson.isPromoter = false;
    req.responseJson.isDeleted = false;

    //Verify if user is already promoter
    const isPromoter = await promoters.findOne({where :{email_fk:req.username}})
    if(!isPromoter) return res.status(400).json(req.responseJson);
    req.responseJson.isPromoter = true

    try {
        await promoters.destroy({ where : {email_fk: req.username}
        });
        req.responseJson.isDeleted = true;
        await eventos.destroy({where :{
            email_fk : req.username
            }
        })

        return res.status(200).json({isDowngraded: true})
    } catch (error){
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }
})


module.exports = router;

