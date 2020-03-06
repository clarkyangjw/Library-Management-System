#ifndef SICT_BOOK_H
#define SICT_BOOK_H
#define _CRT_SECURE_NO_WARNINGS

#include <string>
using namespace std;

namespace sict {
	class Book {
		int m_bookID;
		string m_title;
		string m_author;
		long long m_ISBN;
		string m_publisher;
		string m_inDate;
		int m_copies;
		int m_remaining;
	public:
		Book();
		Book(int, string, string, long long, string, time_t, int, int);
		~Book();
		int getBookID();
		void setBookID(int);
		string getTitle();
		void setTitle(string);
		string getAuthor();
		void setAuthor(string);
		long long getISBN();
		void setISBN(long long);
		string getPublisher();
		void setPublisher(string);
		string getInDate();
		void setInDate(string);
		int getCopies();
		void setCopies(int);
		int getRemaining();
		void setRemaining(int);
	};
}
#endif