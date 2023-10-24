const Joi = require('@hapi/joi').extend(require('@joi/date'));

//Register Validation
const registerValidation = data => {
    const schema = Joi.object({
        name: Joi.string()
            .min(6)
            .max(60)
            .required(),
        email: Joi.string()
            .min(6)
            .max(60)
            .required()
            .email(),
        password: Joi.string()
            .min(8)
            .max(32)
            .required(),
        date: Joi.date().format('YYYY-MM-DD')
            .required(),
    });
    return schema.validate(data);
}

const editUserValidation = data =>{
    const schema = Joi.object({
        name: Joi.string()
            .min(6)
            .max(60)
            .required(),
        cpf: Joi.string()
            .length(10)
            .pattern(/^[0-9]+$/)
            .allow(null)
            .required(),
        descricao: Joi.string()
            .min(0)
            .max(65535)
            .allow(null)
            .required(),
        dataNasc: Joi.date().format('YYYY-MM-DD')
            .required()
    });
    return schema.validate(data);
}

//Login Validation
const loginValidation = data => {
    const schema = Joi.object({
        email: Joi.string()
            .min(6)
            .max(60)
            .required()
            .email(),
        password: Joi.string()
            .min(8)
            .max(32)
            .required(),
    });
    return schema.validate(data);
}

//Event validation
const eventValidation = data => {
    const schema = Joi.object({
        codEvento_fk: Joi.number()
            .integer()
            .optional()
            .min(0)
            .allow(null)
            .empty(null),
        foto: Joi
            .allow(null),
        nome: Joi.string()
            .min(6)
            .max(100)
            .required(),
        endereco: Joi.string()
            .min(6)
            .max(100)
            .required(),
        estabelecimento: Joi.string()
            .min(3)
            .max(100)
            .allow(null)
            .required(),
        inicio: Joi.date().format('YYYY-MM-DD')
            .required(),
        fim: Joi.date().format('YYYY-MM-DD')
            .allow(null),
        horario: Joi.date().format('YYYY-MM-DD HH:mm:ss')
            .required(),
        descricao: Joi.string()
            .min(0)
            .max(65535)
            .allow(null),
        latitude: Joi.string().regex(/^(\+|-)?(?:90(?:(?:\.0{1,30})?)|(?:[0-9]|[1-8][0-9])(?:(?:\.[0-9]{1,30})?))$/, 'numbers').max(12).min(12)
            .min(8)
            .max(32)
            .allow(null),
        longitude: Joi.string().regex(/^(\+|-)?(?:180(?:(?:\.0{1,30})?)|(?:[0-9]|[1-9][0-9]|1[0-7][0-9])(?:(?:\.[0-9]{1,30})?))$/, 'numbers').max(12).min(12)
            .min(8)
            .max(32)
            .allow(null),
    });
    return schema.validate(data);
}

//Event Update validation
const eventUpdateValidation = data => {
    const schema = Joi.object({
        codEvento: Joi.number()
            .integer()
            .min(0)
            .required,
        nome: Joi.string()
            .min(6)
            .max(100)
            .required(),
        foto: Joi
            .allow(null),
        endereco: Joi.string()
            .min(6)
            .max(100)
            .required(),
        estabelecimento: Joi.string()
            .min(3)
            .max(100)
            .required(),
        inicio: Joi.date().format('YYYY-MM-DD')
            .required(),
        fim: Joi.date().format('YYYY-MM-DD')
            .allow(null),
        horario: Joi.date().format('YYYY-MM-DD HH:mm:ss')
            .required(),
        descricao: Joi.string()
            .min(0)
            .max(65535)
            .allow(null),
        latitude: Joi.string().regex(/^(\+|-)?(?:90(?:(?:\.0{1,30})?)|(?:[0-9]|[1-8][0-9])(?:(?:\.[0-9]{1,30})?))$/, 'numbers').max(12).min(12)
            .min(8)
            .max(32)
            .allow(null),
        longitude: Joi.string().regex(/^(\+|-)?(?:180(?:(?:\.0{1,30})?)|(?:[0-9]|[1-9][0-9]|1[0-7][0-9])(?:(?:\.[0-9]{1,30})?))$/, 'numbers').max(12).min(12)
            .min(8)
            .max(32)
            .allow(null),
    });
    // const schema = Joi.object({
    //     nome: Joi.string()
    //         .min(6)
    //         .max(100),
    //     endereco: Joi.string()
    //         .min(6)
    //         .max(100),
    //     estabelecimento: Joi.string()
    //         .min(3)
    //         .max(100),
    //     inicio: Joi.date().format('YYYY-MM-DD'),
    //     fim: Joi.date().format('YYYY-MM-DD'),
    //     horario: Joi.date().format('YYYY-MM-DD HH:mm:ss'),
    //     descricao: Joi.string()
    //         .min(0)
    //         .max(65535),
    //     latitude: Joi.string().regex(/^(\+|-)?(?:90(?:(?:\.0{1,8})?)|(?:[0-9]|[1-8][0-9])(?:(?:\.[0-9]{1,8})?))$/, 'numbers').max(12).min(12)
    //         .min(8)
    //         .max(32),
    //     longitude: Joi.string().regex(/^(\+|-)?(?:180(?:(?:\.0{1,8})?)|(?:[0-9]|[1-9][0-9]|1[0-7][0-9])(?:(?:\.[0-9]{1,8})?))$/, 'numbers').max(12).min(12)
    //         .min(8)
    //         .max(32),
    // });
    return schema.validate(data);
}

const avaliaValidation = data => {
    const schema = Joi.object({
        codEvento_fk: Joi.number()
            .min(0)
            .required(),
        rating: Joi.number()
            .min(0)
            .max(5)
            .required(),
        comentario: Joi.string()
            .max(256)
            .optional()
            .allow(null)
    })
    return schema.validate(data);
}
function convertStringNullsToNull(obj) {
    for (const key in obj) {
        if (obj.hasOwnProperty(key) && obj[key] === "null") {
            obj[key] = null;
        }
    }
    return obj;
}

module.exports.registerValidation = registerValidation;
module.exports.loginValidation = loginValidation;
module.exports.eventValidation = eventValidation;
module.exports.eventUpdateValidation = eventUpdateValidation;
module.exports.avaliaValidation = avaliaValidation;
module.exports.editUserValidation = editUserValidation;
