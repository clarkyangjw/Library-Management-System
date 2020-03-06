#include "Book.h"

namespace sict {
	Book::Book() {
		m_bookID = 0;
		m_title = "";
		m_author = "";
		m_ISBN = 0LL;
		m_publisher = "";
		m_inDate = "";
		m_copies = 0;
		m_remaining = 0;
	}

	Book::Book(int bookID, string title, string author, long long isbn, string publisher, time_t inDate, int copies, int remaining) {
		m_bookID = bookID;
		m_title = title;
		m_author = author;
		m_ISBN = isbn;
		m_publisher = publisher;
		m_inDate = inDate;
		m_copies = copies;
		m_remaining = remaining;
	}

	Book::~Book() {
	}

	int Book::getBookID() {
		return m_bookID;
	}

	void Book::setBookID(int bookID) {
		m_bookID = bookID;
	}

	string Book::getTitle() {
		return m_title;
	}

	void Book::setTitle(string title) {
		m_title = title;
	}

	string Book::getAuthor() {
		return m_author;
	}

	void Book::setAuthor(string author) {
		m_author = author;
	}

	long long Book::getISBN() {
		return m_ISBN;
	}

	void Book::setISBN(long long isbn) {
		m_ISBN = isbn;
	}

	string Book::getPublisher() {
		return m_publisher;
	}

	void Book::setPublisher(string publisher) {
		m_publisher = publisher;
	}

	string Book::getInDate() {
		return m_inDate;
	}

	void Book::setInDate(string inDate) {
		m_inDate = inDate;
	}

	int Book::getCopies() {
		return m_copies;
	}

	void Book::setCopies(int copies) {
		m_copies = copies;
	}

	int Book::getRemaining() {
		return m_remaining;
	}

	void Book::setRemaining(int remianing) {
		m_remaining = remianing;
	}
}