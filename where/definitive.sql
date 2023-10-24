CREATE DATABASE `base_de_dados` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;

-- base_de_dados.Usuarios definition
USE base_de_dados;

CREATE TABLE `Usuarios` (
  `cpf` varchar(11) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `nome` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `foto` LONGBLOB,
  `descricao` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `dataNasc` date NOT NULL,
  `email` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `senha` varchar(1024) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- base_de_dados.Promoters definition

CREATE TABLE `Promoters` (
  `email_fk` varchar(60) COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`email_fk`),
  CONSTRAINT `Promoters_FK` FOREIGN KEY (`email_fk`) REFERENCES `Usuarios` (`email`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;


-- base_de_dadosDS.Eventos definition

CREATE TABLE `Eventos` (
  `codEvento` INT UNSIGNED AUTO_INCREMENT NOT NULL,
  `descricao` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci,
  `nome` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `endereco` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `foto` LONGBLOB,
  `inicio` date NOT NULL,
  `fim` date DEFAULT NULL,
  `horario` datetime NOT NULL,
  `estabelecimento` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `latitude` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `longitude` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `codEvento_fk` INT UNSIGNED DEFAULT NULL,
  `email_fk` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`codEvento`),
  KEY `Eventos_FK` (`email_fk`),
  KEY `Eventos_FK_1` (`codEvento_fk`),
  CONSTRAINT `Eventos_FK` FOREIGN KEY (`email_fk`) REFERENCES `Usuarios` (`email`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Eventos_FK_1` FOREIGN KEY (`codEvento_fk`) REFERENCES `Eventos` (`codEvento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- base_de_dados.Avalia definition

CREATE TABLE `Avalia` (
  `email_fk` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `codEvento_fk` INT UNSIGNED NOT NULL,
  `comentario` varchar(256) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `horario` datetime NOT NULL,
  `rating` int NOT NULL,
  PRIMARY KEY (`email_fk`,`codEvento_fk`),
  KEY `Avalia_FK` (`email_fk`),
  KEY `Avalia_FK_1` (`codEvento_fk`),
  CONSTRAINT `Avalia_FK` FOREIGN KEY (`email_fk`) REFERENCES `Usuarios` (`email`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Avalia_FK_1` FOREIGN KEY (`codEvento_fk`) REFERENCES `Eventos` (`codEvento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- base_de_dados.Participam definition

CREATE TABLE `Participam` (
  `email_fk` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `codEvento_fk` INT UNSIGNED NOT NULL,
  `confirmado` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`email_fk`,`codEvento_fk`),
  KEY `Participam_FK` (`email_fk`),
  KEY `Participam_FK_1` (`codEvento_fk`),
  CONSTRAINT `Participam_FK` FOREIGN KEY (`email_fk`) REFERENCES `Usuarios` (`email`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Participam_FK_1` FOREIGN KEY (`codEvento_fk`) REFERENCES `Eventos` (`codEvento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- base_de_dados.Lembrete definition

CREATE TABLE `Lembrete` (
  `mensagem` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `data` date NOT NULL,
  `codEvento_fk` INT UNSIGNED NOT NULL,
  `email_fk` varchar(60) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  PRIMARY KEY (`email_fk`,`codEvento_fk`),
  KEY `Lembrete_FK` (`email_fk`),
  KEY `Lembrete_FK_1` (`codEvento_fk`),
  CONSTRAINT `Lembrete_FK` FOREIGN KEY (`email_fk`) REFERENCES `Usuarios` (`email`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `Lembrete_FK_1` FOREIGN KEY (`codEvento_fk`) REFERENCES `Eventos` (`codEvento`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;