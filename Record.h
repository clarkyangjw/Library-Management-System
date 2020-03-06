#ifndef SICT_RECORD_H
#define SICT_RECORD_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
using namespace std;

namespace sict {
	class Record {
		int m_recordNum;					//����ID
		int m_bookID;					//ͼ��ID
		int m_userID;					//�û�ID
		string m_loanDate;				//����ʱ��
		string m_expiryDate;		//Ӧ��ʱ��
		string m_returnDate;				//ʵ�ʹ黹ʱ��
		int m_renew;					//�������
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