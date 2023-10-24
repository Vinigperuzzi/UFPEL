const Sequelize = require('sequelize');
module.exports = function(sequelize, DataTypes) {
  return sequelize.define('eventos', {
    codEvento: {
      autoIncrement: true,
      type: DataTypes.INTEGER.UNSIGNED,
      allowNull: false,
      primaryKey: true
    },
    descricao: {
      type: DataTypes.TEXT,
      allowNull: true
    },
    nome: {
      type: DataTypes.STRING(100),
      allowNull: false
    },
    endereco: {
      type: DataTypes.STRING(100),
      allowNull: false
    },
    foto: {
      type: DataTypes.BLOB,
      allowNull: true
    },
    inicio: {
      type: DataTypes.DATEONLY,
      allowNull: false
    },
    fim: {
      type: DataTypes.DATEONLY,
      allowNull: true
    },
    horario: {
      type: DataTypes.DATE,
      allowNull: false
    },
    estabelecimento: {
      type: DataTypes.STRING(100),
      allowNull: true
    },
    latitude: {
      type: DataTypes.STRING(100),
      allowNull: true
    },
    longitude: {
      type: DataTypes.STRING(100),
      allowNull: true
    },
    codEvento_fk: {
      type: DataTypes.INTEGER.UNSIGNED,
      allowNull: true,
      references: {
        model: 'eventos',
        key: 'codEvento'
      }
    },
    email_fk: {
      type: DataTypes.STRING(60),
      allowNull: false,
      references: {
        model: 'usuarios',
        key: 'email'
      }
    }
  }, {
    sequelize,
    tableName: 'eventos',
    timestamps: false,
    indexes: [
      {
        name: "PRIMARY",
        unique: true,
        using: "BTREE",
        fields: [
          { name: "codEvento" },
        ]
      },
      {
        name: "Eventos_FK",
        using: "BTREE",
        fields: [
          { name: "email_fk" },
        ]
      },
      {
        name: "Eventos_FK_1",
        using: "BTREE",
        fields: [
          { name: "codEvento_fk" },
        ]
      },
    ]
  });
};
