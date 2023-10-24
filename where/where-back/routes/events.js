const express = require('express');
const router = express.Router();
const {participam, eventos, promoters, avalia, usuarios} = require('../models');
const {validateToken, createTokens} = require('../utils/JWT')
const {eventUpdateValidation, eventValidation} = require('../utils/validation')
const {Sequelize, Op} = require("sequelize");
const {valid} = require("joi");
const moment = require('moment');
const multer = require('multer');
const buffer = require("buffer");
const upload = multer();

router.get('/teste/:id', async function (req, res, next) {

    const foto = await eventos.findOne({
        where: {codEvento: req.params.id}})
    const utf8EncodedBuffer = Buffer.from(foto.foto, 'utf-8');
    const decodedString = utf8EncodedBuffer.toString('utf-8');
    foto.foto = JSON.parse(decodedString)
    console.log("teste")
    console.log(JSON.parse(decodedString))
    res.status(200).json(foto)
})
router.get('/teste3', validateToken, upload.any(), async function (req, res, next) {

    try {
        // get all events from database
        const listEventos = await eventos.findAll(
            //     {
            //     attributes: {
            //         exclude:
            //             ['email_fk']},
            // }
        );
        for(const evento of listEventos){
            const interested = await participam.findOne({where: {
                email_fk: evento.email_fk,
                codEvento_fk: evento.codEvento}})

            evento.dataValues.isParticipant = interested ? true : false
        }

        listEventos.forEach(evento => {
            evento.dataValues.isCreator = evento.email_fk == req.username
            evento.email_fk = undefined
            if (evento.foto){
                const utf8EncodedBuffer = Buffer.from(evento.foto, 'utf-8');
                const decodedString = utf8EncodedBuffer.toString('utf-8');
                evento.foto = JSON.parse(decodedString)
            }
        })
        listEventos.forEach(evento => console.log(evento.dataValues))
        return res.status(200).json(listEventos);
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }
})


router.post('/teste2', validateToken, upload.any(), async function (req, res, next) {

    //Create flags
    req.responseJson.isPromoter = false;
    req.responseJson.isValidated = false;
    req.responseJson.isCreated = false;

    console.log(req.body)

    //Verfiy if user is promoter
    const isPromoter = await promoters.findOne({
        where:
            {email_fk: req.username}
    });
    if (!isPromoter) return res.status(400).json(req.responseJson);
    req.responseJson.isPromoter = true;

    //Verify input
    const {error} = eventValidation(req.body);
    if (error) {
        req.responseJson.error = error.details[0].message;
        return res.status(400).json(req.responseJson);
    }
    req.responseJson.isValidated = true;

    try {
        await eventos.create({
            descricao: req.body.descricao,
            nome: req.body.nome,
            //foto: req.body.foto,
            endereco: req.body.endereco,
            inicio: req.body.inicio,
            fim: req.body.fim,
            email_fk: req.username,
            codEvento_fk: req.body.codEvento_fk,
            latitude_fk: req.body.latitude_fk,
            longitude_fk: req.body.longitude_fk,
            horario: req.body.horario,
            estabelecimento: req.body.estabelecimento
        }).then(
            evento => {
                return res.status(200).json({isCreated: true, id: evento.codEvento});
            }
        );
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }
})

router.get('/name/:substring', validateToken, async function (req, res, next) {

    try {
        const substring = req.params.substring
        const listEventos = await eventos.findAll({
            attributes: {exclude: ['email_fk']},
            where: {
                nome: {
                    [Op.substring]: req.params.substring
                }
            }
        });
        return res.status(200).json(listEventos)
    } catch (error) {
        req.responseJson.error = error
        return res.status(400).json(req.responseJson)
    }
})


// READ: Get all future and current events
//
// JSON INPUT - Not necessary
router.get('/all', validateToken, async function (req, res, next) {

    try {
        // get all events from database
        const listEventos = await eventos.findAll(
            //     {
            //     attributes: {
            //         exclude:
            //             ['email_fk']},
            // }
        );
        for(const evento of listEventos){
            const interested = await participam.findOne({where: {
                    email_fk: evento.email_fk,
                    codEvento_fk: evento.codEvento}})

            evento.dataValues.isParticipant = interested ? true : false
        }

        listEventos.forEach(evento => {
            evento.dataValues.isCreator = evento.email_fk == req.username
            evento.email_fk = undefined
            if (evento.foto){
                const utf8EncodedBuffer = Buffer.from(evento.foto, 'utf-8');
                const decodedString = utf8EncodedBuffer.toString('utf-8');
                evento.foto = JSON.parse(decodedString)
            }
        })
        listEventos.forEach(evento => console.log(evento.dataValues))
        return res.status(200).json(listEventos);
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }
});

// READ: Get subevents from x event
//
// JSON INPUT
//
// -
router.get('/sub/:id', validateToken, async function (req, res, next) {

    //Create flag
    req.responseJson.isEvent = false;

    //Get event
    const event = await eventos.findByPk(req.params.id);

    // Verify if event exists
    if (!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;

    try {
        const listSubEvents = await eventos.findAll({
            where: {codEvento_fk: req.params.id}
        });
        listSubEvents.each(event => {
            if(event.foto) {
                event.foto = bindecode(event.foto)
            }
        })
        return res.status(200).json(listSubEvents);

    } catch (error) {
        req.responseJson.message = "Database error";
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }

})


// READ: Get events where logged user is the creator/owner
//
// JSON INPUT NOT NECESSARY
router.get('/user/creator', validateToken, async function (req, res, next) {

    // Create flag
    req.responseJson.listEvents = null;

    try {
        // Get all events of a LOGGED USER from database
        const listEvents = await eventos.findAll({
            where: {
                email_fk: req.username
            }
        })
        //Remove email from response
        listEvents.forEach(event => event.email_fk = undefined);
        return res.status(200).json({listEvents: listEvents});
    } catch (error) {
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }

})


// Get events where user is interested or confirmed
router.get('/user/participating', validateToken, async function (req, res, next) {

    // Create flag
    req.responseJson.listEvents = null;

    try {


        //
        const listId = await participam.findAll({
            attributes: {exclude: ['email_fk', 'confirmado']},
            where: {
                email_fk: req.username
            }
        })

        //
        // listId.forEach(event => {
        //     event.email_fk = undefined;
        //     event.confirmado = undefined;
        // });
        //console.log(listId)
        idArray = []
        listId.forEach(entry => idArray.push(entry.dataValues.codEvento_fk))

        const listEvents = await eventos.findAll({
            where: {
                codEvento: idArray
            }
        })
        listEvents.forEach(event => event.email = undefined);
        return res.status(200).json({listEvents: listEvents});
    } catch (error) {
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }

})

// CREATE: Create Event
//
// JSON INPUT - FALTA ADICIONAR FOTO
//
// {
//          "descricao": "STRING",
//          "nome": "STRING",
//          "endereco": "STRING",
//          "inicio": "DATE YYYY-MM-DD",
//          "fim": "DATE YYYY-MM-DD",
//          "codEvento_fk": "ID DO EVENTO PAI",
//          "latitude_fk": "latitude 90.x ~~ -90.xx",
//          "longitude_fk": "Longitude  180.x ~~ -180.xxx",
//          "horario": "DATETIME YYYY-MM-DD HH:mm:ss",
//          "estabelecimento": "STRING"
//   }
router.post('/', validateToken, upload.any(), async function (req, res, next) {

    //Create flags
    req.responseJson.isPromoter = false;
    req.responseJson.isValidated = false;
    req.responseJson.isCreated = false;
    req.body = convertStringNullsToNull(req.body)

    //Verfiy if user is promoter
    const isPromoter = await promoters.findOne({
        where:
            {email_fk: req.username}
    });
    if (!isPromoter) return res.status(400).json(req.responseJson);
    req.responseJson.isPromoter = true;

    //Verify input
    const {error} = eventValidation(req.body);
    if (error) {
        req.responseJson.error = error.details[0].message;
        return res.status(400).json(req.responseJson);
    }
    req.responseJson.isValidated = true;

    try {
        const jsonString = JSON.stringify(req.files[0]);
        const buffer = Buffer.from(jsonString, 'utf-8');

        await eventos.create({
            descricao: req.body.descricao,
            nome: req.body.nome,
            foto: buffer,
            endereco: req.body.endereco,
            inicio: req.body.inicio,
            fim: req.body.fim,
            email_fk: req.username,
            codEvento_fk: req.body.codEvento_fk,
            latitude: req.body.latitude,
            longitude: req.body.longitude,
            horario: req.body.horario,
            estabelecimento: req.body.estabelecimento
        }).then(
            evento => {
                return res.status(200).json({isCreated: true, id: evento.codEvento});
            }
        );
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }
})

// READ: Get X event
//
//
//
router.get('/:id', validateToken, async function (req, res, next) {
    //Create flag
    req.responseJson.isEvent = false;

    //Get event
    const event = await eventos.findByPk(req.params.id);


    // Verify if event exists
    if (!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;

    // const utf8EncodedBuffer = Buffer.from(event.foto, 'utf-8');
    // const decodedString = utf8EncodedBuffer.toString('utf-8');
    event.foto = bindecode(event.foto)//JSON.parse(decodedString)

    //Remove email value from response
    event.email_fk = undefined;
    return res.status(200).json(event);
})

//UPDATE: Update event information
//
// JSON INPUT
// {
//          "codEvento: "ID DO EVENTO",
//          "descricao": "STRING",
//          "nome": "STRING",
//          "endereco": "STRING",
//          "inicio": "DATE YYYY-MM-DD",
//          "fim": "DATE YYYY-MM-DD",
//          "latitude_fk": "latitude 90.x ~~ -90.xx",
//          "longitude_fk": "Longitude  180.x ~~ -180.xxx",
//          "horario": "DATETIME YYYY-MM-DD HH:mm:ss",
//          "estabelecimento": "STRING"
//   }
router.put('/:id', validateToken, upload.any(), async function (req, res, next) {

    //Create flags
    req.responseJson.isEvent = false;
    req.responseJson.isOwner = false;
    req.responseJson.isPromoter = false;
    req.responseJson.isValidated = false;
    req.responseJson.isUpdated = false;
    req.body = convertStringNullsToNull(req.body)

    //Get event
    const event = await eventos.findByPk(req.params.id);

    // Verify if event exists
    if (!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;

    //Verify if user is event owner
    if (event.email_fk != req.username) return res.status(400).json(req.responseJson);
    req.responseJson.isOwner = true;

    //Verify if user is a promoter
    const isPromoter = await promoters.findOne({
        where:
            {email_fk: req.username}
    });
    if (!isPromoter) return res.status(400).json(req.responseJson);
    req.responseJson.isPromoter = true;


    //Verify input
    const {error} = eventUpdateValidation(req.body);
    if (error) {
        req.responseJson.error = error.details[0].message;
        return res.status(400).json(req.responseJson);
    }
    req.responseJson.isValidated = true;

    try {
        const jsonString = JSON.stringify(req.files[0]);
        const buffer = Buffer.from(jsonString, 'utf-8');
        // Try to update event
        await eventos.update({
            descricao: req.body.descricao,
            nome: req.body.nome,
            foto: buffer,
            endereco: req.body.endereco,
            inicio: req.body.inicio,
            fim: req.body.fim,
            latitude: req.body.latitude,
            longitude: req.body.longitude,
            horario: req.body.horario,
            estabelecimento: req.body.estabelecimento
        }, {
            where: {codEvento: req.params.id}
        });
        return res.status(200).json({isUpdated: true});

    } catch (error) {
        req.responseJson.error = error
        return res.status(400).json(req.responseJson);
    }


})

//Delete event
//
// rota "/codEvento"

router.delete('/:id', validateToken, async function (req, res, next) {

    //Create flags
    req.responseJson.isEvent = false;
    req.responseJson.isOwner = false;
    req.responseJson.isDeleted = false;

    //Get event
    const event = await eventos.findByPk(req.params.id);

    // Verify if event exists
    if (!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;

    //Verify if user is owner
    if (event.email_fk != req.username) return res.status(400).json(req.responseJson);
    req.responseJson.isOwner = true;

    try {
        //Try to delete event
        await eventos.destroy({
            where: {codEvento: req.params.id}
        });
        //Return success
        return res.status(200).json({isDeleted: true});
    } catch (error) {
        res.status(400).json(req.responseJson);
    }
})

// READ: Get number of interested users
//
// JSON INPUT
//
// {
//      "codEvento": "ID DO EVENTO"
// }
router.get('/interested/:id', validateToken, async function (req, res, next) {

    //Create flags
    req.responseJson.isEvent = false;

    //Get event
    const event = await eventos.findByPk(req.params.id);

    //Verify if event exists
    if (!event) return res.status(400).json(req.params.id);
    req.responseJson.isEvent = true;

    try {
        const numberOfInterested = await participam.count({
            where: {
                codEvento_fk: req.params.id,
                confirmado: 0
            }
        })
        return res.status(200).json({numberOfInterested: numberOfInterested});
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }

})

// READ: Get number of confirmed users
//
// JSON INPUT
//
// {
//      "codEvento": "ID DO EVENTO"
// }
router.get('/confirmed/:id', validateToken, async function (req, res, next) {

    //Create flags
    req.responseJson.isEvent = false;

    //Get event
    const event = await eventos.findByPk(req.params.id);

    //Verify if event exists
    if (!event) return res.status(400).json(req.params.id);
    req.responseJson.isEvent = true;

    try {
        const numberOfInterested = await participam.count({
            where: {
                codEvento_fk: req.params.id,
                confirmado: true
            }
        })
        return res.status(200).json({numberOfInterested: numberOfInterested});
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }
})


router.get('/:id/participating', validateToken, async function (req, res, next) {

    //Create flags
    req.responseJson.isEvent = false;

    //Get event
    const event = await eventos.findByPk(req.params.id);

    //Verify if event exists
    if (!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;

    try {
        const numberOfParticipating = await participam.count({
            where: {
                codEvento_fk: req.params.id,
            }
        })
        return res.status(200).json({numberOfParticipating: numberOfParticipating});
    } catch (error) {
        req.responseJson.error = error;
        return res.status(400).json(req.responseJson);
    }
})

function convertStringNullsToNull(obj) {
    for (const key in obj) {
        if (obj[key] === "null") {
            obj[key] = null;
        }
    }
    return obj;
}

function bindecode(obj) {
    const utf8EncodedBuffer = Buffer.from(obj, 'utf-8');
    const decodedString = utf8EncodedBuffer.toString('utf-8');
    return JSON.parse(decodedString)
}

module.exports = router;