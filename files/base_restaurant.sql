-- phpMyAdmin SQL Dump
-- version 4.6.4
-- https://www.phpmyadmin.net/
--
-- Client :  127.0.0.1
-- Généré le :  Sam 13 Janvier 2018 à 02:54
-- Version du serveur :  5.7.14
-- Version de PHP :  5.6.25

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `base_restaurant`
--

-- --------------------------------------------------------

--
-- Structure de la table `ingredient`
--

CREATE TABLE `ingredient` (
  `id_ingredient` int(11) NOT NULL,
  `name` varchar(50) NOT NULL,
  `quantity` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `ingredient`
--

INSERT INTO `ingredient` (`id_ingredient`, `name`, `quantity`) VALUES
(1, 'eggs', 10),
(2, 'pork', 10),
(3, 'noodles', 10),
(4, 'soya sauce', 10),
(5, 'mushroom', 10),
(6, 'rice', 10),
(7, 'morue', 10),
(8, 'chicken', 10),
(9, 'beef', 10),
(10, 'vegetables', 10),
(11, 'donut', 10),
(12, 'seafood', 10),
(13, 'octopus', 10),
(14, 'potato', 10),
(15, 'ketchup', 10),
(16, 'salmon', 10),
(17, 'algae', 10),
(18, 'tofu', 10),
(19, 'chive', 10);

-- --------------------------------------------------------

--
-- Structure de la table `link_orders_product`
--

CREATE TABLE `link_orders_product` (
  `id_order` int(11) NOT NULL,
  `id_product` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `link_product_ingredient`
--

CREATE TABLE `link_product_ingredient` (
  `id_product` int(11) NOT NULL,
  `id_ingredient` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Contenu de la table `link_product_ingredient`
--

INSERT INTO `link_product_ingredient` (`id_product`, `id_ingredient`) VALUES
(1, 1),
(1, 2),
(1, 3),
(1, 4),
(1, 5),
(2, 1),
(2, 3),
(2, 4),
(2, 5),
(2, 7),
(3, 1),
(3, 3),
(3, 4),
(3, 5),
(3, 9),
(4, 6),
(4, 8),
(5, 7),
(5, 8),
(6, 3),
(6, 4),
(6, 9),
(6, 10),
(7, 10),
(7, 11),
(7, 12),
(8, 1),
(8, 13),
(8, 14),
(9, 1),
(9, 6),
(9, 15),
(10, 4),
(10, 6),
(10, 16),
(11, 1),
(11, 2),
(11, 6),
(12, 2),
(12, 6),
(12, 17),
(12, 18),
(13, 17),
(13, 18),
(13, 19);

-- --------------------------------------------------------

--
-- Structure de la table `orders`
--

CREATE TABLE `orders` (
  `id_order` int(11) NOT NULL,
  `total_price` double NOT NULL,
  `purchase_time` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `id_terminal` int(11) NOT NULL,
  `id_table` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `place`
--

CREATE TABLE `place` (
  `id_place` int(11) NOT NULL,
  `free_place` tinyint(1) DEFAULT NULL,
  `id_table` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `place`
--

INSERT INTO `place` (`id_place`, `free_place`, `id_table`) VALUES
(1, 0, 1),
(2, 1, 1);

-- --------------------------------------------------------

--
-- Structure de la table `product`
--

CREATE TABLE `product` (
  `id_product` int(11) NOT NULL,
  `name` varchar(50) NOT NULL,
  `price` double NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `product`
--

INSERT INTO `product` (`id_product`, `name`, `price`) VALUES
(1, 'ramen pork', 16),
(2, 'ramen fish', 16),
(3, 'ramen beef', 16),
(4, 'chick and rice', 12),
(5, 'fish and rice', 12),
(6, 'yakisoba', 14),
(7, 'tempura', 9),
(8, 'oden', 11),
(9, 'omuraisu', 12),
(10, 'Sushi', 3),
(11, 'katsudon', 8),
(12, 'onigiri', 15),
(13, 'soup miso', 5);

-- --------------------------------------------------------

--
-- Structure de la table `table_place`
--

CREATE TABLE `table_place` (
  `id_table` int(11) NOT NULL,
  `free_table` tinyint(1) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `table_place`
--

INSERT INTO `table_place` (`id_table`, `free_table`) VALUES
(1, 1);

-- --------------------------------------------------------

--
-- Structure de la table `terminal`
--

CREATE TABLE `terminal` (
  `id_terminal` int(11) NOT NULL,
  `staff` tinyint(4) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Contenu de la table `terminal`
--

INSERT INTO `terminal` (`id_terminal`, `staff`) VALUES
(1, 1);

--
-- Index pour les tables exportées
--

--
-- Index pour la table `ingredient`
--
ALTER TABLE `ingredient`
  ADD PRIMARY KEY (`id_ingredient`);

--
-- Index pour la table `link_orders_product`
--
ALTER TABLE `link_orders_product`
  ADD PRIMARY KEY (`id_order`,`id_product`);

--
-- Index pour la table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`id_order`);

--
-- Index pour la table `place`
--
ALTER TABLE `place`
  ADD PRIMARY KEY (`id_place`);

--
-- Index pour la table `product`
--
ALTER TABLE `product`
  ADD PRIMARY KEY (`id_product`);

--
-- Index pour la table `table_place`
--
ALTER TABLE `table_place`
  ADD PRIMARY KEY (`id_table`);

--
-- Index pour la table `terminal`
--
ALTER TABLE `terminal`
  ADD PRIMARY KEY (`id_terminal`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `ingredient`
--
ALTER TABLE `ingredient`
  MODIFY `id_ingredient` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;
--
-- AUTO_INCREMENT pour la table `orders`
--
ALTER TABLE `orders`
  MODIFY `id_order` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pour la table `place`
--
ALTER TABLE `place`
  MODIFY `id_place` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT pour la table `product`
--
ALTER TABLE `product`
  MODIFY `id_product` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;
--
-- AUTO_INCREMENT pour la table `table_place`
--
ALTER TABLE `table_place`
  MODIFY `id_table` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
--
-- AUTO_INCREMENT pour la table `terminal`
--
ALTER TABLE `terminal`
  MODIFY `id_terminal` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
