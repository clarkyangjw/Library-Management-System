#ifndef SICT_RECORD_H
#define SICT_RECORD_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
using namespace std;

namespace sict {
	class Record {
		int m_recordNum;					//借阅ID
		int m_bookID;					//图书ID
		int m_userID;					//用户ID
		string m_loanDate;				//借阅时间
		string m_expiryDate;		//应还时间
		string m_returnDate;				//实际归还时间
		int m_renew;					//续借次数
	public:
		Record();
		~Record();
		int getRecordNum();
		void setRecordNum(int);
		int getBookID();
		void setBookID(int);
		int getUserID();
		void setUserID(int);
		string getLoanDate();
		void setLoanDate(string);
		string getExpiryDate();
		void setExpiryDate(string);
		string getReturnDate();
		void setReturnDate(string);
		int getRenew();
		void setRenew(int);
	};
}
#endif