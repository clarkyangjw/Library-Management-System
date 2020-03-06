#include "Record.h"

namespace sict {
	Record::Record() {
	}

	Record::~Record() {
	}

	int Record::getRecordNum() {
		return m_recordNum;
	}
	void Record::setRecordNum(int recordNum) {
		m_recordNum = recordNum;
	}
	int Record::getBookID() {
		return m_bookID;
	}
	void Record::setBookID(int bookid) {
		m_bookID = bookid;
	}
	int Record::getUserID() {
		return m_userID;
	}
	void Record::setUserID(int userID) {
		m_userID = userID;
	}
	string Record::getLoanDate() {
		return m_loanDate;
	}
	void Record::setLoanDate(string loanDate) {
		m_loanDate = loanDate;
	}
	string Record::getExpiryDate() {
		return m_expiryDate;
	}
	void Record::setExpiryDate(string expiryDate) {
		m_expiryDate = expiryDate;
	}
	string Record::getReturnDate() {
		return m_returnDate;
	}
	void Record::setReturnDate(string returnDate) {
		m_returnDate = returnDate;
	}
	int Record::getRenew() {
		return m_renew;
	}
	void Record::setRenew(int renew) {
		m_renew = renew;
	}
}