const Sequelize = require('sequelize');
module.exports = function(sequelize, DataTypes) {
  return sequelize.define('promoters', {
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
    tableName: 'promoters',
    timestamps: false,
    indexes: [
      {
        name: "PRIMARY",
        unique: true,
        using: "BTREE",
        fields: [
          { name: "email_fk" },
        ]
      },
    ]
  });
};
