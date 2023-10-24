const Sequelize = require('sequelize');
module.exports = function(sequelize, DataTypes) {
  return sequelize.define('lembrete', {
    mensagem: {
      type: DataTypes.STRING(100),
      allowNull: true
    },
    data: {
      type: DataTypes.DATEONLY,
      allowNull: false
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
    email_fk: {
      type: DataTypes.STRING(60),
      allowNull: false,
      primaryKey: true,
      references: {
        model: 'usuarios',
        key: 'email'
      }
    }
  }, {
    sequelize,
    tableName: 'lembrete',
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
        name: "Lembrete_FK",
        using: "BTREE",
        fields: [
          { name: "email_fk" },
        ]
      },
      {
        name: "Lembrete_FK_1",
        using: "BTREE",
        fields: [
          { name: "codEvento_fk" },
        ]
      },
    ]
  });
};
