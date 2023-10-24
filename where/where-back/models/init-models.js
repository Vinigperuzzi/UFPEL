var DataTypes = require("sequelize").DataTypes;
var _avalia = require("./avalia");
var _eventos = require("./eventos");
var _lembrete = require("./lembrete");
var _participam = require("./participam");
var _promoters = require("./promoters");
var _usuarios = require("./usuarios");

function initModels(sequelize) {
  var avalia = _avalia(sequelize, DataTypes);
  var eventos = _eventos(sequelize, DataTypes);
  var lembrete = _lembrete(sequelize, DataTypes);
  var participam = _participam(sequelize, DataTypes);
  var promoters = _promoters(sequelize, DataTypes);
  var usuarios = _usuarios(sequelize, DataTypes);

  eventos.belongsToMany(usuarios, { as: 'email_fk_usuarios', through: avalia, foreignKey: "codEvento_fk", otherKey: "email_fk" });
  eventos.belongsToMany(usuarios, { as: 'email_fk_usuarios_lembretes', through: lembrete, foreignKey: "codEvento_fk", otherKey: "email_fk" });
  eventos.belongsToMany(usuarios, { as: 'email_fk_usuarios_participams', through: participam, foreignKey: "codEvento_fk", otherKey: "email_fk" });
  usuarios.belongsToMany(eventos, { as: 'codEvento_fk_eventos', through: avalia, foreignKey: "email_fk", otherKey: "codEvento_fk" });
  usuarios.belongsToMany(eventos, { as: 'codEvento_fk_eventos_lembretes', through: lembrete, foreignKey: "email_fk", otherKey: "codEvento_fk" });
  usuarios.belongsToMany(eventos, { as: 'codEvento_fk_eventos_participams', through: participam, foreignKey: "email_fk", otherKey: "codEvento_fk" });
  avalia.belongsTo(eventos, { as: "codEvento_fk_evento", foreignKey: "codEvento_fk"});
  eventos.hasMany(avalia, { as: "avalia", foreignKey: "codEvento_fk"});
  eventos.belongsTo(eventos, { as: "codEvento_fk_eventos_evento", foreignKey: "codEvento_fk"});
  eventos.hasMany(eventos, { as: "eventos", foreignKey: "codEvento_fk"});
  lembrete.belongsTo(eventos, { as: "codEvento_fk_evento", foreignKey: "codEvento_fk"});
  eventos.hasMany(lembrete, { as: "lembretes", foreignKey: "codEvento_fk"});
  participam.belongsTo(eventos, { as: "codEvento_fk_evento", foreignKey: "codEvento_fk"});
  eventos.hasMany(participam, { as: "participams", foreignKey: "codEvento_fk"});
  avalia.belongsTo(usuarios, { as: "email_fk_usuario", foreignKey: "email_fk"});
  usuarios.hasMany(avalia, { as: "avalia", foreignKey: "email_fk"});
  eventos.belongsTo(usuarios, { as: "email_fk_usuario", foreignKey: "email_fk"});
  usuarios.hasMany(eventos, { as: "eventos", foreignKey: "email_fk"});
  lembrete.belongsTo(usuarios, { as: "email_fk_usuario", foreignKey: "email_fk"});
  usuarios.hasMany(lembrete, { as: "lembretes", foreignKey: "email_fk"});
  participam.belongsTo(usuarios, { as: "email_fk_usuario", foreignKey: "email_fk"});
  usuarios.hasMany(participam, { as: "participams", foreignKey: "email_fk"});
  promoters.belongsTo(usuarios, { as: "email_fk_usuario", foreignKey: "email_fk"});
  usuarios.hasOne(promoters, { as: "promoter", foreignKey: "email_fk"});

  return {
    avalia,
    eventos,
    lembrete,
    participam,
    promoters,
    usuarios,
  };
}
module.exports = initModels;
module.exports.initModels = initModels;
module.exports.default = initModels;
