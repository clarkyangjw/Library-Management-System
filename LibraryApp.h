#ifndef SICT_LIBRARYAPP_H
#define SICT_LIBRARYAPP_H
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iomanip>
#include "User.h"
#include "Book.h"
#include "Record.h"
#include "DBUtility.h"
#include "TimeUtility.h"
namespace sict {
	class LibraryApp {
		DBUtility m_dbUtility;
		TimeUtility m_timeUtility;
	public:
		LibraryApp();
		LibraryApp(const LibraryApp&) = delete;
		LibraryApp(const LibraryApp&&) = delete;
		LibraryApp& operator=(const LibraryApp&) = delete;
		LibraryApp& operator=(const LibraryApp&&) = delete;
		~LibraryApp();

		bool login(User&);
		void run();

		int showMenu(int);
		void displayAllBook();
		void addBook();
		void queryBook(string);
		void deleteBook(int);
		void diaplayAllRecord();
		void addUser();
		void displayAllUser();



		void loanBook(int nBookId, User& user);
		void returnBook(User& user);
		void showMyRecord(User user);
		void renewBook(User& user);
	};


}
#endif