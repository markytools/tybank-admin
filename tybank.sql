-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 22, 2018 at 11:59 AM
-- Server version: 5.6.37
-- PHP Version: 5.6.30

USE database_name;

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `slylily_tybank`
--

-- --------------------------------------------------------

--
-- Table structure for table `acct_type`
--

CREATE TABLE `acct_type` (
  `idacct_type` int(10) UNSIGNED NOT NULL,
  `account_type` varchar(45) NOT NULL,
  `account_desc` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `acct_type`
--

INSERT INTO `acct_type` (`idacct_type`, `account_type`, `account_desc`) VALUES
(1, 'SAVINGS', 'portion of the liquid assets set aside while earning monetary return'),
(2, 'CURRENT', 'offers flexible payment method by distributing money to others'),
(3, 'PERSONAL', 'individual account');

-- --------------------------------------------------------

--
-- Table structure for table `amount`
--

CREATE TABLE `amount` (
  `idamount` int(10) UNSIGNED NOT NULL,
  `currency` varchar(10) NOT NULL,
  `amount` decimal(10,2) NOT NULL DEFAULT '0.00',
  `accountno` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `online_acct`
--

CREATE TABLE `online_acct` (
  `idonline_acct` int(10) UNSIGNED NOT NULL,
  `email` varchar(45) DEFAULT NULL,
  `username` varchar(45) DEFAULT NULL,
  `password` varchar(45) DEFAULT NULL,
  `personal_info_id` int(10) UNSIGNED NOT NULL,
  `last_login` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `personal_info`
--

CREATE TABLE `personal_info` (
  `idpersonal_info` int(10) UNSIGNED NOT NULL,
  `firstname` varchar(45) NOT NULL,
  `middlename` varchar(45) NOT NULL,
  `lastname` varchar(45) NOT NULL,
  `address` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `transaction`
--

CREATE TABLE `transaction` (
  `idtransaction` int(10) UNSIGNED NOT NULL,
  `credit` decimal(10,2) NOT NULL DEFAULT '0.00',
  `debit` decimal(10,2) NOT NULL DEFAULT '0.00',
  `account_no` varchar(12) NOT NULL,
  `trans_post_id` int(10) UNSIGNED NOT NULL,
  `datetime_post` datetime NOT NULL,
  `recipient_num` varchar(20) DEFAULT NULL,
  `trans_balance` decimal(10,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `trans_post`
--

CREATE TABLE `trans_post` (
  `idtrans_post` int(10) UNSIGNED NOT NULL,
  `trans_type_id` int(10) UNSIGNED NOT NULL,
  `post_data` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `trans_post`
--

INSERT INTO `trans_post` (`idtrans_post`, `trans_type_id`, `post_data`) VALUES
(1, 1, 'TRANS_FROM_'),
(2, 1, 'TRANS_TO_'),
(3, 2, 'GLOBE_'),
(4, 2, 'SMART_'),
(5, 2, 'NORECO_'),
(6, 3, 'MASTERCARD_PAY_'),
(7, 4, 'DEPO_SELF'),
(8, 5, 'WITHDRAW_SELF');

-- --------------------------------------------------------

--
-- Table structure for table `trans_type`
--

CREATE TABLE `trans_type` (
  `idtrans_type` int(10) UNSIGNED NOT NULL,
  `trans_type` varchar(45) NOT NULL,
  `trans_desc` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `trans_type`
--

INSERT INTO `trans_type` (`idtrans_type`, `trans_type`, `trans_desc`) VALUES
(1, 'MONEY_TRANSFER', 'money transfer from one account to another'),
(2, 'BILL_PAY', 'payment of bills from one account to the company\'s account'),
(3, 'MASTERCARD', 'using mastercard as mode of payment'),
(4, 'DEPOSIT', 'simple bank account deposit'),
(5, 'WITHDRAW', 'simple bank account withdraw');

-- --------------------------------------------------------

--
-- Table structure for table `user_account`
--

CREATE TABLE `user_account` (
  `iduser_account` int(10) UNSIGNED NOT NULL,
  `account_no` varchar(12) NOT NULL,
  `pin_num` varchar(6) DEFAULT NULL,
  `account_type_id` int(10) UNSIGNED NOT NULL,
  `personal_info_id` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `acct_type`
--
ALTER TABLE `acct_type`
  ADD PRIMARY KEY (`idacct_type`),
  ADD UNIQUE KEY `idacct_type_UNIQUE` (`idacct_type`),
  ADD UNIQUE KEY `account_type_UNIQUE` (`account_type`);

--
-- Indexes for table `amount`
--
ALTER TABLE `amount`
  ADD PRIMARY KEY (`idamount`,`accountno`),
  ADD UNIQUE KEY `idamount_UNIQUE` (`idamount`),
  ADD KEY `account_num_idx` (`accountno`);

--
-- Indexes for table `online_acct`
--
ALTER TABLE `online_acct`
  ADD PRIMARY KEY (`idonline_acct`,`personal_info_id`),
  ADD UNIQUE KEY `idonline_acct_UNIQUE` (`idonline_acct`),
  ADD UNIQUE KEY `personal_info_id_UNIQUE` (`personal_info_id`),
  ADD UNIQUE KEY `email_UNIQUE` (`email`),
  ADD UNIQUE KEY `username_UNIQUE` (`username`),
  ADD UNIQUE KEY `password_UNIQUE` (`password`);

--
-- Indexes for table `personal_info`
--
ALTER TABLE `personal_info`
  ADD PRIMARY KEY (`idpersonal_info`),
  ADD UNIQUE KEY `idpersonal_info_UNIQUE` (`idpersonal_info`);

--
-- Indexes for table `transaction`
--
ALTER TABLE `transaction`
  ADD PRIMARY KEY (`idtransaction`,`account_no`),
  ADD UNIQUE KEY `idtransaction_UNIQUE` (`idtransaction`),
  ADD KEY `accountno_idx` (`account_no`),
  ADD KEY `transPostId_idx` (`trans_post_id`);

--
-- Indexes for table `trans_post`
--
ALTER TABLE `trans_post`
  ADD PRIMARY KEY (`idtrans_post`),
  ADD UNIQUE KEY `idtrans_post_UNIQUE` (`idtrans_post`),
  ADD KEY `trans_type_id_idx` (`trans_type_id`);

--
-- Indexes for table `trans_type`
--
ALTER TABLE `trans_type`
  ADD PRIMARY KEY (`idtrans_type`),
  ADD UNIQUE KEY `idtrans_type_UNIQUE` (`idtrans_type`),
  ADD UNIQUE KEY `trans_type_UNIQUE` (`trans_type`);

--
-- Indexes for table `user_account`
--
ALTER TABLE `user_account`
  ADD PRIMARY KEY (`iduser_account`,`account_no`,`personal_info_id`),
  ADD UNIQUE KEY `iduser_account_UNIQUE` (`iduser_account`),
  ADD UNIQUE KEY `accountno_UNIQUE` (`account_no`),
  ADD KEY `account_type_id_idx` (`account_type_id`),
  ADD KEY `personalInfoId_idx` (`personal_info_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `acct_type`
--
ALTER TABLE `acct_type`
  MODIFY `idacct_type` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `amount`
--
ALTER TABLE `amount`
  MODIFY `idamount` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT for table `online_acct`
--
ALTER TABLE `online_acct`
  MODIFY `idonline_acct` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT for table `personal_info`
--
ALTER TABLE `personal_info`
  MODIFY `idpersonal_info` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;
--
-- AUTO_INCREMENT for table `transaction`
--
ALTER TABLE `transaction`
  MODIFY `idtransaction` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=32;
--
-- AUTO_INCREMENT for table `trans_post`
--
ALTER TABLE `trans_post`
  MODIFY `idtrans_post` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;
--
-- AUTO_INCREMENT for table `trans_type`
--
ALTER TABLE `trans_type`
  MODIFY `idtrans_type` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT for table `user_account`
--
ALTER TABLE `user_account`
  MODIFY `iduser_account` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=28;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `amount`
--
ALTER TABLE `amount`
  ADD CONSTRAINT `account_num` FOREIGN KEY (`accountno`) REFERENCES `user_account` (`account_no`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Constraints for table `online_acct`
--
ALTER TABLE `online_acct`
  ADD CONSTRAINT `personal_info_id` FOREIGN KEY (`personal_info_id`) REFERENCES `personal_info` (`idpersonal_info`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `transaction`
--
ALTER TABLE `transaction`
  ADD CONSTRAINT `accountno` FOREIGN KEY (`account_no`) REFERENCES `user_account` (`account_no`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `transPostId` FOREIGN KEY (`trans_post_id`) REFERENCES `trans_post` (`idtrans_post`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `trans_post`
--
ALTER TABLE `trans_post`
  ADD CONSTRAINT `trans_type_id` FOREIGN KEY (`trans_type_id`) REFERENCES `trans_type` (`idtrans_type`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `user_account`
--
ALTER TABLE `user_account`
  ADD CONSTRAINT `account_type_id` FOREIGN KEY (`account_type_id`) REFERENCES `acct_type` (`idacct_type`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `personalInfoId` FOREIGN KEY (`personal_info_id`) REFERENCES `personal_info` (`idpersonal_info`) ON DELETE NO ACTION ON UPDATE NO ACTION;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
