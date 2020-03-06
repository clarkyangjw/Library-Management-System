#include "DBUtility.h"

namespace sict {
	DBUtility::DBUtility() {
		db_userName = "root";
		db_password = "root";
		db_host = "localhost";
		db_database = "library";
		db_port = 3306;
		db_isOpen = false;
	}

	DBUtility::~DBUtility() {
		closeDB();
	}

	bool DBUtility::openDB() {
		mysql_init(&db_connect);
		if (mysql_real_connect(&db_connect, db_host.c_str(), db_userName.c_str(), db_password.c_str(), db_database.c_str(), db_port, NULL, 0)) {
			db_isOpen = true;
		}
		return db_isOpen;
	}

	bool DBUtility::closeDB() {		//���ܲ��ܸĳɷ���void
		mysql_close(&db_connect);
		return true;
	}

	void DBUtility::readUser(string userName, string userPassword, User& user) {
		int res;
		string sql;
		if (db_isOpen) {
			sql += "select * from user where username='" + userName + "' and password='" + userPassword + "'";
			res = mysql_query(&db_connect, sql.c_str());
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result->row_count > 0) {
					db_row = mysql_fetch_row(db_result);
					user.setUserID(atoi(db_row[0]));
					user.setUserName(db_row[1]);
					user.setUserType(atoi(db_row[3]));
				}
				else {
					user.setUserID(-1);
				}
			}
			else {
				cout << "Query database failed!" << endl;
			}
		}
		else {
			cout << "Connection failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}

	void DBUtility::selectAllBook(vector<Book>& books) {
		int res;
		string sql;
		if (db_isOpen) {
			sql += "select * from book";
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result) {
					while (db_row = mysql_fetch_row(db_result)) {//��ȡ���������
						Book book;
						book.setBookID(atoi(db_row[0]));
						book.setTitle(db_row[1]);
						book.setAuthor(db_row[2]);
						book.setISBN(atol(db_row[3]));
						book.setPublisher(db_row[4]);
						book.setInDate(db_row[5]);
						book.setCopies(atoi(db_row[6]));
						book.setRemaining(atoi(db_row[7]));
						books.push_back(book);
					}
				}
			}
			else {
				cout << "query sql failed!" << endl;
			}
		}
		else {
			cout << "connect failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}


	void DBUtility::addBook(Book book) {
		string sql = "";
		char copies[6];
		char remaining[6];
		sprintf(copies, "%d", book.getCopies());
		sprintf(remaining, "%d", book.getCopies());

		if (db_isOpen) {
			//���ʱ��
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "insert into book values(null,'" + book.getTitle() + "','" + book.getAuthor() + "','" + to_string(book.getISBN()) + "','" + book.getPublisher() + "','" + book.getInDate() + "', " + copies + ", " + remaining + ")";
			mysql_query(&db_connect, sql.c_str());
		}
		else {
			cout << "connect failed!" << endl;
		}
		cin.get();
		cin.get();

	}

	void DBUtility::selectBookByTitle(string title, vector<Book>& books) {
		int res;
		string sql;
		if (db_isOpen) {
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "select * from book where title like '%" + title + "%'";
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result) {
					while (db_row = mysql_fetch_row(db_result)) { //��ȡ���������
						Book book;
						book.setBookID(atoi(db_row[0]));
						book.setTitle(db_row[1]);
						book.setAuthor(db_row[2]);
						book.setISBN(atol(db_row[3]));
						book.setPublisher(db_row[4]);
						book.setInDate(db_row[5]);
						book.setCopies(atoi(db_row[6]));
						book.setRemaining(atoi(db_row[7]));
						books.push_back(book);
					}
				}
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else
		{
			cout << "Connection failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}

	//����ͼ��ID��ѯ�鼮
	void DBUtility::selectBookById(int nBookId, Book& book) {
		int res;
		string sql;
		char bookId[11] = { 0 };
		sprintf(bookId, "%d", nBookId);
		if (db_isOpen) {
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "select * from book where bookid=";
			sql += bookId;
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result) {
					while (db_row = mysql_fetch_row(db_result)) {//��ȡ���������
						book.setBookID(atoi(db_row[0]));
						book.setTitle(db_row[1]);
						book.setAuthor(db_row[2]);
						book.setISBN(atol(db_row[3]));
						book.setPublisher(db_row[4]);
						book.setInDate(db_row[5]);
						book.setCopies(atoi(db_row[6]));
						book.setRemaining(atoi(db_row[7]));
					}
				}
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else {
			cout << "Connection failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}

	//����IDɾ��ͼ��
	void DBUtility::deleteBookById(int nBookId) {
		int res;
		string sql;
		char bookId[11] = { 0 };
		sprintf(bookId, "%d", nBookId);
		if (db_isOpen) {
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "delete from book where bookid=";
			sql += bookId;
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				cout << "Delete succeeded��" << endl;
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else {
			cout << "Connection failed!" << endl;
		}
	}

	void DBUtility::addUser(User user) {
		string sql = "";
		//char userType[1];
		//sprintf(userType, "%d", user.getUserType());//�����ܲ��ܼ�ɾ����һ��

		if (db_isOpen) {
			sql += "insert into user values(null,'" + user.getUserName() + "','" + user.getUserPassword() + "'," + to_string(user.getUserType()) + ")";
			mysql_query(&db_connect, sql.c_str());
		}
		else {
			cout << "connect failed!" << endl;
		}
	}

	//��ѯ�����û�
	void DBUtility::selectAllUser(vector<User>& users) {
		int res;
		string sql;
		if (db_isOpen) {
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "select * from user";
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result) {
					while (db_row = mysql_fetch_row(db_result)) { //��ȡ��������� 
						User user;
						user.setUserID(atoi(db_row[0]));
						user.setUserName(db_row[1]);
						user.setUserType(atoi(db_row[3]));
						users.push_back(user);
					}
				}
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else {
			cout << "Connection failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}

	//�������ļ�¼
	void DBUtility::addRecord(Record record) {
		string sql = "";
		char szBookId[16];
		char szUserId[16];
		sprintf(szBookId, "%d", record.getBookID());
		sprintf(szUserId, "%d", record.getUserID());
		if (db_isOpen) {
			sql = sql + "insert into record values(null," + to_string(record.getBookID()) + "," + to_string(record.getUserID()) + ",'" + record.getLoanDate() + "','" + record.getExpiryDate() + "',NULL,0)";
			mysql_query(&db_connect, sql.c_str());

			sql = "";

			sql += "update book set book.left=book.left-1 where id = " + to_string(record.getBookID());//remember to change left to remaining
			mysql_query(&db_connect, sql.c_str());
			cout << "Succeed to loan a book!" << endl;
		}
		else {
			cout << "Connection failed!" << endl;
		}
	}

	void DBUtility::selectRecordByUserId(vector<Record>& records, int userId, int type)
	{
		//nType=1��ʾѡ��δ�黹 nType=2��ʾѡ��ȫ��
		int res;
		string sql;
		//char szUserId[8] = { 0 };
		//sprintf(szUserId, "%d", userId);
		if (db_isOpen)
		{
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql = sql + "select * from record where userid=" + to_string(userId);
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res)
			{
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result)
				{
					while (db_row = mysql_fetch_row(db_result))//��ȡ���������
					{
						//�����ڿձ�ʾ�Ѿ��黹
						if (type == 1)
						{
							if (db_row[5] != NULL)
							{
								continue;
							}
						}

						Record record;
						record.setRecordNum(atoi(db_row[0]));
						record.setBookID(atoi(db_row[1]));
						record.setUserID(atoi(db_row[2]));
						record.setLoanDate(db_row[3]);
						record.setExpiryDate(db_row[4]);
						record.setReturnDate(db_row[5] == NULL ? "" : db_row[5]);
						record.setRenew(atoi(db_row[6]));
						records.push_back(record);
					}
				}
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else {
			cout << "Connection failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}

	User DBUtility::selectUserById(int userId) {
		int res;
		string sql;
		User user;
		//char szUserId[5] = { 0 };
		//sprintf(szUserId, "%d", userId);
		if (db_isOpen) {
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "select * from user where userid=" + to_string(userId);
			//sql += szUserId;
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result) {
					while (db_row = mysql_fetch_row(db_result)) {//��ȡ���������
						user.setUserID(atoi(db_row[0]));
						user.setUserName(db_row[1]);
					}
				}
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else {
			cout << "connect failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
		return user;
	}

	void DBUtility::completeRecord(int recordId, int bookId) {
		string sql = "";
		//char szRecordId[16];
		//char szBookId[16];
		//sprintf(szRecordId, "%d", recordId);
		//sprintf(szBookId, "%d", bookId);
		time_t tTemp = time(NULL);
		char szTime[16] = { 0 };
		timeUtility.timeToString(tTemp, szTime);
		if (db_isOpen) {
			sql = sql + "update record set returndate='" + szTime + "' where recordnum=" + to_string(recordId);
			mysql_query(&db_connect, sql.c_str());

			sql = "";

			sql = sql + "update book set book.left=book.left+1 where id = " + to_string(bookId);;//gai left wei remaining
			mysql_query(&db_connect, sql.c_str());
		}
		else{
			cout << "Connection failed!" << endl;
		}
	}

	void DBUtility::extendRecord(int recordNum){
		string sql = "";
		//char szRecordId[16];
		//char szBookId[16];
		//sprintf(szRecordId, "%d", recordNum);
		time_t tTemp = time(NULL);
		if (db_isOpen){
			sql = sql + "update record set expirydate='" + timeUtility.addMonth(tTemp) + "',record.renew=record.renew+1 where recordnum=" + to_string(recordNum);
			mysql_query(&db_connect, sql.c_str());
		}
		else{
			cout << "Connection failed!" << endl;
		}
	}

	void DBUtility::selectAllRecord(vector<Record>& records)
	{
		int res;
		string sql;
		if (db_isOpen) {
			//mysql_query(&db_connect, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����
			sql += "select * from record";
			res = mysql_query(&db_connect, sql.c_str());//��ѯ
			if (!res) {
				db_result = mysql_store_result(&db_connect);//�����ѯ�������ݵ�result
				if (db_result){
					while (db_row = mysql_fetch_row(db_result)){//��ȡ���������
						Record record;
						record.setRecordNum(atoi(db_row[0]));
						record.setBookID(atoi(db_row[1]));
						record.setUserID(atoi(db_row[2]));
						record.setLoanDate(db_row[3]);
						record.setExpiryDate(db_row[4]);
						record.setReturnDate(db_row[5] == NULL ? "" : db_row[5]);
						record.setRenew(atoi(db_row[6]));
						records.push_back(record);
					}
				}
			}
			else {
				cout << "Query sql failed!" << endl;
			}
		}
		else {
			cout << "Connection failed!" << endl;
		}
		if (db_result != NULL) {
			mysql_free_result(db_result);//�ͷŽ����Դ
		}
	}
}