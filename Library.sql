SET FOREIGN_KEY_CHECKS=0;
DROP DATABASE library;
CREATE DATABASE library;
USE library;
-- ----------------------------
-- book
-- ----------------------------
DROP TABLE IF EXISTS `book`;
CREATE TABLE `book` (
  `bookid` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(50) NOT NULL,
  `author` varchar(32)	 NOT NULL,
  `isbn` varchar(13) NOT NULL,
  `publisher` varchar(32) NOT NULL,
  `indate` date NOT NULL,
  `copies` int(5) NOT NULL,
  `remaining` int(5) NOT NULL,
  PRIMARY KEY(`bookid`),
  CONSTRAINT isbn_un UNIQUE (`isbn`) 
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `userid` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(20) NOT NULL,
  `password` varchar(20) NOT NULL,
  `usertype` int(1) NOT NULL,
  PRIMARY KEY(`userid`),
  CONSTRAINT username_un UNIQUE (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

-- ----------------------------
-- record
-- ----------------------------
DROP TABLE IF EXISTS `record`;
CREATE TABLE `record` (
  `recordnum` int(11) NOT NULL AUTO_INCREMENT,
  `bookid` int(11) NOT NULL,
  `userid` int(11) NOT NULL,
  `loandate` date NOT NULL,
  `expirydate` date NOT NULL,
  `returndate` date DEFAULT NULL,
  `renew` int(1) DEFAULT NULL,
  PRIMARY KEY(`recordnum`),
  CONSTRAINT record_book_fk FOREIGN KEY(`bookid`) REFERENCES book(`bookid`) on delete cascade on update cascade,
  CONSTRAINT record_user_fk FOREIGN KEY(`userid`) REFERENCES user(`userid`) on delete cascade on update cascade
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
-- ----------------------------
-- insert data
-- ----------------------------
INSERT INTO user VALUES(NULL, "Clark", "123", 1);
INSERT INTO user VALUES(NULL, "Dora", "123", 2);
--INSERT INTO book VALUES(NULL, "Harry Potter and the Philosopher's Stone", "J.K. Rowling", "9781408855898", "Bloomsbury", sysdate, 0, 0);