#include "LibraryApp.h"

using namespace std;

namespace sict {
	LibraryApp::LibraryApp() {
	}

	LibraryApp::~LibraryApp() {
	}

	bool LibraryApp::login(User& user) {
		string userName = "";
		string userPassword = "";
		bool login = false;
		m_dbUtility.openDB();
		do {
			cout << "========== Welcome to Clark's Library Management System ==========" << endl;
			cout << "Please enter username: ";
			cin >> userName;
			cout << endl;
			cout << "Please enter password: ";
			cin >> userPassword;
			cout << endl;
			m_dbUtility.readUser(userName, userPassword, user);
			if (user.getUserID() == -1) {
				cout << "User Name or Password is incorrect, please try again!" << endl;
				cout << "press any key to continue..." << endl;
				cin.get();
				cin.get();
				system("cls");
			}
		} while (user.getUserID() == -1);
		if (user.getUserID() != -1) {
			login = true;
		}
		return login;
	}

	void LibraryApp::run() {
		User user;
		if (login(user)) {
			bool isLogin = true;
			if (user.getUserType() == 1) {
				string title = "";
				int nBookId = 0;
				while (isLogin) {
					switch (showMenu(user.getUserType())) {			//改为选择非数字也能继续
					case 1:
						displayAllBook();
						break;
					case 2:
						cout << "Please enter a book title: ";
						cin >> title;
						queryBook(title);
						break;
					case 3:
						addBook();
						break;
					case 4:
						cout << "Please enter a book ID for delete: " << endl;
						cin >> nBookId;
						deleteBook(nBookId);
						break;
					case 5:
						diaplayAllRecord();
						break;
					case 6:
						addUser();
						break;
					case 7:
						displayAllUser();
						break;
					case 0:
						//选择退出登录
						isLogin = false;
						break;
					default:
						break;
					}
				}
			}
			else if (user.getUserType() == 2) {
				string title = "";
				int bookId;
				while (isLogin) {
					switch (showMenu(user.getUserType())) {
					case 1:
						cout << "Please enter a book title: ";
						cin >> title;
						queryBook(title);
						break;
					case 2:
						cout << "Please enter a book ID：";
						cin >> bookId;
						loanBook(bookId, user);
						break;
					case 3:
						returnBook(user);
						break;
					case 4:
						showMyRecord(user);
						break;
					case 5:
						renewBook(user);
						break;
					case 0:
						//选择退出登录
						isLogin = false;
						break;
					default:
						break;
					}
				}
			}
			cout << "You have logout the system, press any key to exit..." << endl;
		}
	}


	int LibraryApp::showMenu(int userType) {
		int selection;
		system("cls");
		cout << "========== Welcome to Clark's Library Management System ==========" << endl;
		if (userType == 1) {
			cout << "1. Display book list" << endl;
			cout << "2. Query books by title" << endl;
			cout << "3. Add a book" << endl;
			cout << "4. Delete a book" << endl;
			cout << "5. Display record list" << endl;
			cout << "6. Add an user" << endl;
			cout << "7. Display user list" << endl;
			cout << "0. Exit program" << endl;
		}
		else if (userType == 2) {
			cout << "1. Query books by title" << endl;
			cout << "2. Loan a book by book ID" << endl;
			cout << "3. Ruturn books" << endl;
			cout << "4. Query records" << endl;
			cout << "5. Renew a book" << endl;
			cout << "0. Exit program" << endl;
		}
		cout << "Please select an option: ";
		std::cin >> selection;
		if (std::cin.fail() || selection < 0 || selection > 7) {
			std::cin.clear();
			selection = -1;
		}
		std::cin.ignore(2000, '\n');
		return selection;
	}

	void LibraryApp::displayAllBook() {
		vector<Book> books;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}
		m_dbUtility.selectAllBook(books);
		vector<Book>::iterator vecIter;
		cout << "ID     Title            Author           Publisher       InDate     Copies   Remianing" << endl;
		for (vecIter = books.begin(); vecIter != books.end(); vecIter++) {
			cout << left
				<< setw(11) << vecIter->getBookID() << "  "
				<< setw(50) << vecIter->getTitle() << "  "
				<< setw(32) << vecIter->getAuthor() << "  "
				<< setw(32) << vecIter->getPublisher() << "  "
				<< setw(10) << vecIter->getInDate() << "  "
				<< setw(5) << vecIter->getCopies() << "  "
				<< setw(5) << vecIter->getRemaining() << endl;
		}
		cin.get();
		cin.get();
	}

	void LibraryApp::queryBook(string title) {
		vector<Book> books;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}

		m_dbUtility.selectBookByTitle(title, books);
		vector<Book>::iterator vecIter;
		cout << "ID     Title            Author           Publisher       InDate     Copies   Remianing" << endl;
		for (vecIter = books.begin(); vecIter != books.end(); vecIter++) {
			cout << setiosflags(ios::left) << setw(4) << vecIter->getBookID() << "  " << setw(14) << vecIter->getTitle() << "  " << setw(10) << vecIter->getAuthor() << "  " << setw(14) << vecIter->getPublisher() << "  " << setw(14) << vecIter->getInDate() << "  " << setw(8) << vecIter->getCopies() << "  " << setw(3) << vecIter->getRemaining() << endl;
		}
		cin.get();
		cin.get();
	}

	void LibraryApp::addBook() {  //did not show book is added message!
		string title;
		string author;
		long long isbn;
		string publisher;
		int copies;
		char szTime[32] = { 0 };
		time_t lt;
		lt = time(NULL);
		m_timeUtility.timeToString(lt, szTime);

		cout << "Please enter book's information: " << endl;
		cout << "Title Author ISBN Publisher Copies" << endl;
		cin >> title;
		cin >> author;
		cin >> isbn;
		cin >> publisher;
		cin >> copies;

		Book book;
		book.setTitle(title);
		book.setAuthor(author);
		book.setISBN(isbn);
		book.setPublisher(publisher);
		book.setCopies(copies);
		book.setRemaining(0);
		book.setInDate(szTime);

		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}
		m_dbUtility.addBook(book);
		cout << "A new book is added." << endl;

	}

	//根据图书ID删除图书
	void LibraryApp::deleteBook(int bookId) {
		Book book;
		book.setBookID(-1);
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}
		m_dbUtility.selectBookById(bookId, book);
		if (book.getBookID() != -1) {
			cout << "ID     Title            Author           Publisher       InDate     Copies   Remianing" << endl;
			cout << setiosflags(ios::left) << setw(4) << book.getBookID() << "  " << setw(14) << book.getTitle() << "  " << setw(10) << book.getAuthor() << "  " << setw(14) << book.getPublisher() << "  " << setw(14) << book.getInDate() << "  " << setw(8) << book.getCopies() << "  " << setw(3) << book.getRemaining() << endl;

			//询问是否删除
			char comfirm = 'a';
			cout << "Confirming to delete this book? (n/y): ";
			cin.get();
			cin >> comfirm;
			while (true) {
				if (comfirm == 'y' || comfirm == 'Y') {
					m_dbUtility.deleteBookById(bookId);
					break;
				}
				else if (comfirm == 'n' || comfirm == 'N') {
					cout << "Deny to delete!";
					break;
				}
				else {
					cout << "Invalid Entry! Only (Y)es or (N)o are acceptable : ";
					cin.get();
					cin >> comfirm;
				}
			}
		}
		else {
			cout << "Can not find the book that ID is " << bookId << "!" << endl;
		}
		cin.get();
		cin.get();
	}

	void LibraryApp::diaplayAllRecord() {
		vector<Record> records;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}

		m_dbUtility.selectAllRecord(records);
		User user;
		Book book;
		vector<Record>::iterator vecIter;
		cout << "Number       Title        UserName    LoanDate       ExpiryDate     ReturnDate   Renew" << endl;
		for (vecIter = records.begin(); vecIter != records.end(); vecIter++) {
			user = m_dbUtility.selectUserById(vecIter->getUserID());
			m_dbUtility.selectBookById(vecIter->getBookID(), book);
			cout << setiosflags(ios::left) << setw(4) << vecIter->getRecordNum() << "  " << setw(14) << book.getTitle() << "  " << setw(6) << user.getUserName() << "  " << setw(13) << vecIter->getLoanDate() << "  " << setw(13) << vecIter->getExpiryDate() << "  " << setw(13) << vecIter->getReturnDate() << "  " << setw(3) << vecIter->getRenew() << endl;
		}
		cin.get();
		cin.get();
	}

	//增加用户
	void LibraryApp::addUser() {
		string userName = "";
		string password = "";
		int userType = 0;

		cout << "Please enter user's information: " << endl;
		cout << "UserName   Password   UserType" << endl;
		User user;

		cin >> userName;
		cin >> password;
		cin >> userType;

		user.setUserName(userName);
		user.setUserPassword(password);
		user.setUserType(userType);

		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}

		m_dbUtility.addUser(user);
		cout << "A new user is added." << endl;
		cin.get();
		cin.get();
	}

	//展示所有用户
	void LibraryApp::displayAllUser() {
		vector<User> users;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}

		m_dbUtility.selectAllUser(users);
		User user;
		Book book;
		vector<User>::iterator vecIter;
		cout << "UserID     UserName      UserTpye" << endl;
		for (vecIter = users.begin(); vecIter != users.end(); vecIter++) {
			cout << setiosflags(ios::left) << setw(6) << vecIter->getUserID() << "  " << setw(8) << vecIter->getUserName() << "  " << (vecIter->getUserType() == 1 ? "Manager" : "Customer") << endl;
		}
		cin.get();
		cin.get();
	}


	void LibraryApp::loanBook(int bookId, User& user) {
		Book book;
		book.setBookID(-1);
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}
		m_dbUtility.selectBookById(bookId, book);
		if (book.getBookID() != -1) {
			cout << "ID     Title            Author           Publisher       InDate     Copies   Remianing" << endl;
			cout << setiosflags(ios::left) << setw(4) << book.getBookID() << "  " << setw(14) << book.getTitle() << "  " << setw(10) << book.getAuthor() << "  " << setw(14) << book.getPublisher() << "  " << setw(14) << book.getInDate() << "  " << setw(8) << book.getCopies() << "  " << setw(3) << book.getRemaining() << endl;
			if (book.getRemaining() == 0) {
				cout << "There are no available copies now!" << endl;
				cin.get();
				cin.get();
			}
			else {
				//询问是否借阅
				char confirm = 'a';
				cout << "Confirming to loan this book? (n/y): " << endl;
				cin.get();
				cin >> confirm;
				while (true) {
					if (confirm == 'y' || confirm == 'Y') {
						//借阅
						Record record;
						record.setBookID(book.getBookID());
						record.setUserID(user.getUserID());
						time_t tTemp = time(NULL);
						char szTime[16] = { 0 };
						m_timeUtility.timeToString(tTemp, szTime);
						record.setLoanDate(szTime);
						record.setExpiryDate(m_timeUtility.addMonth(tTemp));
						record.setReturnDate("");
						record.setRenew(0);
						m_dbUtility.addRecord(record);
						break;
					}
					else if (confirm == 'n' || confirm == 'N') {
						cout << "Cancel loaning a book!";
						break;
					}
					else {
						cout << "Invalid Entry! Only (Y)es or (N)o are acceptable : ";
						cin.get();
						cin >> confirm;
					}
				}
			}
		}
		else {
			cout << "Can not find the book that ID is " << bookId << "!" << endl;
		}
		cin.get();
		cin.get();
	}

	void LibraryApp::returnBook(User& user) {
		Book book;
		book.setBookID(-1);
		vector<Record> records;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}
		//展示还未归还的图书记录
		m_dbUtility.selectRecordByUserId(records, user.getUserID(), 1);
		cout << "Loaned books are shown below" << endl;
		vector<Record>::iterator vecIter;
		cout << "Number       Title        UserName    LoanDate       ExpiryDate     ReturnDate   Renew" << endl;
		for (vecIter = records.begin(); vecIter != records.end(); vecIter++) {
			user = m_dbUtility.selectUserById(vecIter->getUserID());
			m_dbUtility.selectBookById(vecIter->getBookID(), book);
			cout << setiosflags(ios::left) << setw(4) << vecIter->getRecordNum() << "  " << setw(14) << book.getTitle() << "  " << setw(6) << user.getUserName() << "  " << setw(13) << vecIter->getLoanDate() << "  " << setw(13) << vecIter->getExpiryDate() << "  " << setw(13) << vecIter->getReturnDate() << "  " << setw(3) << vecIter->getRenew() << endl;
		}
		cout << "Please select a record number to return a book: " << endl;

		//选择要还哪本书
		int recordNum;
		cin >> recordNum;
		bool isFound = true;
		while (isFound) {
			for (vecIter = records.begin(); vecIter != records.end(); vecIter++) {
				if (recordNum == vecIter->getRecordNum()) {
					isFound = false;
					break;
				}
			}
			if (vecIter == records.end()) {
				cout << "The selected record number is not in your record, please try again: ";//~增加不退还选项
				cin >> recordNum;
			}
		}

		m_dbUtility.completeRecord(vecIter->getRecordNum(), vecIter->getBookID());
		cout << "Book is returned successfully!" << endl;
		cin.get();
		cin.get();
	}

	void LibraryApp::showMyRecord(User user) {
		vector<Record> records;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}

		m_dbUtility.selectRecordByUserId(records, user.getUserID(), 2);
		Book book;
		cout << "Your records are shown below: " << endl;
		vector<Record>::iterator vecIter;
		cout << "Number       Title        UserName    LoanDate       ExpiryDate     ReturnDate   Renew" << endl;
		for (vecIter = records.begin(); vecIter != records.end(); vecIter++) {
			m_dbUtility.selectBookById(vecIter->getBookID(), book);
			cout << setiosflags(ios::left) << setw(4) << vecIter->getRecordNum() << "  " << setw(14) << book.getTitle() << "  " << setw(6) << user.getUserName() << "  " << setw(13) << vecIter->getLoanDate() << "  " << setw(13) << vecIter->getExpiryDate() << "  " << setw(13) << vecIter->getReturnDate() << "  " << setw(3) << vecIter->getRenew() << endl;
		}
		cin.get();
		cin.get();
	}

	//续借图书
	void LibraryApp::renewBook(User& user) {
		Book book;
		book.setBookID(-1);
		vector<Record> records;
		if (!m_dbUtility.db_isOpen) {
			m_dbUtility.openDB();
		}
		//展示还未归还的图书记录
		m_dbUtility.selectRecordByUserId(records, user.getUserID(), 1);
		cout << "Records are shown below" << endl;
		vector<Record>::iterator vecIter;
		cout << "Number       Title        UserName    LoanDate       ExpiryDate     ReturnDate   Renew" << endl;
		for (vecIter = records.begin(); vecIter != records.end(); vecIter++) {
			user = m_dbUtility.selectUserById(vecIter->getUserID());
			m_dbUtility.selectBookById(vecIter->getBookID(), book);
			cout << setiosflags(ios::left) << setw(4) << vecIter->getRecordNum() << "  " << setw(14) << book.getTitle() << "  " << setw(6) << user.getUserName() << "  " << setw(13) << vecIter->getLoanDate() << "  " << setw(13) << vecIter->getExpiryDate() << "  " << setw(13) << vecIter->getReturnDate() << "  " << setw(3) << vecIter->getRenew() << endl;
		}
		cout << "Please select a record number to renew a book: " << endl;

		//选择要续借哪本书
		int recordNum;
		cin >> recordNum;
		bool isFound = false;
		bool canBeRenewed = false;
		while (!isFound) {
			for (vecIter = records.begin(); vecIter != records.end(); vecIter++) {
				if (recordNum == vecIter->getRecordNum()) {
					isFound = true;
					if (vecIter->getRenew() > 0) {
						canBeRenewed = false;
					}
					else {
						canBeRenewed = true;
					}
					break;
				}
			}
			if (vecIter == records.end()) {
				cout << "The selected record number is not in your record, please try again: ";
				cin >> recordNum;
			}
		}

		if (true == canBeRenewed) {
			m_dbUtility.extendRecord(recordNum);
			cout << "Book is renewed successfully!!" << endl;
		}
		else {
			cout << "Books can not be renewed more than once." << endl;
		}

		cin.get();
		cin.get();
	}






}