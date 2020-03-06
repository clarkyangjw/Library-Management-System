#include "User.h"
namespace sict {
	User::User() :m_userID(0), m_userName(""), m_userPassword(""), m_userType(0) {
	}

	User::~User() {
	}

	int User::getUserID() {
		return m_userID;
	}

	void User::setUserID(const int userid) {
		m_userID = userid;
	}

	string User::getUserName() {
		return m_userName;
	}

	void User::setUserName(const string userName) {
		m_userName = userName;
	}

	string User::getUserPassword() {
		return m_userPassword;
	}

	void User::setUserPassword(const string userPassword) {
		m_userPassword = userPassword;
	}

	int User::getUserType() {
		return m_userType;
	}

	void User::setUserType(const int userType) {
		m_userType = userType;
	}
}