const Sequelize = require('sequelize');
module.exports = function(sequelize, DataTypes) {
  return sequelize.define('avalia', {
    email_fk: {
      type: DataTypes.STRING(60),
      allowNull: false,
      primaryKey: true,
      references: {
        model: 'usuarios',
        key: 'email'
      }
    },
    codEvento_fk: {
      type: DataTypes.INTEGER.UNSIGNED,
      allowNull: false,
      primaryKey: true,
      references: {
        model: 'eventos',
        key: 'codEvento'
      }
    },
    comentario: {
      type: DataTypes.STRING(256),
      allowNull: true
    },
    horario: {
      type: DataTypes.DATE,
      allowNull: false
    },
    rating: {
      type: DataTypes.INTEGER,
      allowNull: false
    }
  }, {
    sequelize,
    tableName: 'avalia',
    timestamps: false,
    indexes: [
      {
        name: "PRIMARY",
        unique: true,
        using: "BTREE",
        fields: [
          { name: "email_fk" },
          { name: "codEvento_fk" },
        ]
      },
      {
        name: "Avalia_FK",
        using: "BTREE",
        fields: [
          { name: "email_fk" },
        ]
      },
      {
        name: "Avalia_FK_1",
        using: "BTREE",
        fields: [
          { name: "codEvento_fk" },
        ]
      },
    ]
  });
};
