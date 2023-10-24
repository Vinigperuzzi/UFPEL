const express = require('express');
const router = express.Router();
const { participam,eventos, promoters} = require('../models');
const {validateToken} = require('../utils/JWT')
const {eventUpdateValidation,eventValidation} = require('../utils/validation')


// READ: GET interested and confirmed values
//
// JSON
//  {
//
//  }
// router.get('/:id', validateToken, async function(req, res, next) {
//
//
//     const part = await participam.findOne({where: {email_fk:req.username, codEvento_fk:req.params.id}});
//     if(!part) return res.status(200).json({
//         interested:false,
//         confirmed:false
//     });
//
//     if(part.confirmado == true) return res.status(200).json({
//         interested:false,
//         confirmed:true
//     })
//
//     return res.status(200).json({
//         interested:true,
//         confirmed:false
//     })
//
// })

// CREATE:Add user to "PARTICIPAM" table
//
//  JSON
//  {
//      "codEvento_fk": "id do evento",
//      "confirmado": "true/false"
//  }
router.post('/', validateToken, async function(req, res,next) {

    // Create flags
    req.responseJson.isEvent = false;


    // Verify if event exists
    const event = await eventos.findByPk(req.body.codEvento_fk);
    if(!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;

    // Verify if user is already participating
    const participando = await participam.findOne({
        where : {
            codEvento_fk: req.body.codEvento_fk,
            email_fk: req.username
        }
    })
    if(participando) {
        req.responseJson.alreadyParticipating = true;
        return res.status(400).json(req.responseJson);
    }
    req.responseJson.alreadyParticipating = false;

    try {
        await participam.create({
            codEvento_fk: req.body.codEvento_fk,
            email_fk: req.username,
            confirmado: req.body.confirmado
        })
        res.status(200).json("Participando!");
    } catch(error) {
        req.responseJson.error = error;
        res.status(400).json(req.responseJson);
    }

})

// DELETE from "PARTICIPAM
//
//  JSON
//  {
//         "codEvento_fk": "id do evento"
//  }
router.delete('/', validateToken, async function(req,res,next) {
    try {
        await participam.destroy({
            where : {
                codEvento_fk: req.body.codEvento_fk,
                email_fk: req.username
            }
        })
        res.status(200).json("Nao ta mais participando");
    } catch(error) {
        req.responseJson.error = error;
        res.status(400).json(req.responseJson);
    }
})

// Update "confirmado" from "PARTICIPAM
//
//  JSON
//  {
//      "codEvento_fk": "id do evento",
//      "confirmado": "true/false"
//  }
router.put('/', validateToken, async function(req,res,next) {

    // Create flags
    req.responseJson.isEvent = false;
    req.responseJson.participating = false;


    // Verify if event exists
    const event = await eventos.findByPk(req.body.codEvento_fk);
    if(!event) return res.status(400).json(req.responseJson);
    req.responseJson.isEvent = true;
    console.log("ROLA")
    // Verify if user is already participating
    const participando = await participam.findOne({
        where : {
            codEvento_fk: req.body.codEvento_fk,
            email_fk: req.username
        }
    })
    if(!participando) return res.status(400).json(req.responseJson);
    req.responseJson.participating = true;


    try {
            await participam.update({
                confirmado: req.body.confirmado
            }, {
                    where: {
                        codEvento_fk:req.body.codEvento_fk,
                        email_fk: req.username
                    }
                })

            res.status(200).json("UPDATADO")
    } catch(error) {
        req.responseJson.error = error;
        res.status(400).json(req.responseJson);
    }
})

// IsParticipating
router.get('/:id', validateToken, async function(req,res,next) {
    try {
        const participa = await participam.findOne({
            where : {
                codEvento_fk: req.params.id,
                email_fk: req.username
            }
        })

        if(participa) {
            return res.status(200).json({isParticipating: true, confirmed: participa.confirmado})
        } else {
            return res.status(200).json({isParticipating: false})
        }
    } catch(error) {
            req.responseJson.error = error
            return res.status(400).json(req.responseJson)
    }
})




module.exports = router;