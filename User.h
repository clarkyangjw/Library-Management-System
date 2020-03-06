#ifndef SICT_USER_H
#define SICT_USER_H
#define _CRT_SECURE_NO_WARNINGS

#include <string>

using namespace std;

namespace sict {
	class User {
		int m_userID;
		string m_userName;
		string m_userPassword;
		int m_userType;

	public:
		User();
		~User();
		//User(const User&) = delete;
		//User(const User&&) = delete;
		//User& operator=(const User&) = delete;
		//User& operator=(const User&&) = delete;
		int getUserID();
		void setUserID(const int);
		string getUserName();
		void setUserName(const string);
		string getUserPassword();
		void setUserPassword(const string);
		int getUserType();
		void setUserType(const int);
	};
}
#endif