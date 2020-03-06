#ifndef SICT_DBUTILITY_H
#define SICT_DBUTILITY_H
#define _CRT_SECURE_NO_WARNINGS

#include <winsock.h>
#include <mysql.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "User.h"
#include "Book.h"
#include "Record.h"
#include "TimeUtility.h"

using namespace std;

namespace sict {
	class DBUtility {
		string db_userName;
		string db_password;
		string db_host;
		string db_database;
		int db_port;

		MYSQL db_connect;
		MYSQL_RES* db_result;
		MYSQL_FIELD* db_field;
		MYSQL_ROW db_row;

	public:
		bool db_isOpen;
		TimeUtility timeUtility;

		DBUtility();
		~DBUtility();
		bool openDB();
		bool closeDB();
		void readUser(string, string, User&);
		void selectAllBook(vector<Book>& books);
		void addBook(Book book);
		void selectBookByTitle(string, vector<Book>&);
		void selectBookById(int nBookId, Book& book);
		void deleteBookById(int nBookId);
		void addUser(User user);
		void selectAllUser(vector<User>& users);
		User selectUserById(int userId);
		void addRecord(Record record);
		void selectRecordByUserId(vector<Record>& Records, int userId, int type);
		void completeRecord(int recordId, int bookId);
		void extendRecord(int recordNum);
		void selectAllRecord(vector<Record>& records);
	};
}
#endif