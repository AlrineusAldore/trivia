#include "SqliteDatabase.h"

int usersCallback(void* data, int argc, char** argv, char** azColName);

//Constructor
SqliteDatabase::SqliteDatabase()
{
	string err = "no error";
	bool doesFileExist = !_access(DB_FILE_NAME, 0);
	int res = sqlite3_open(DB_FILE_NAME, &_db);
	if (res != SQLITE_OK)
	{
		_db = nullptr;
		err = "Failed to open DB. Error code: " + to_string(res) + ENDL;
		throw(exception(err.c_str()));
	}

	if (!doesFileExist)
	{
		err = "Error, DB file didn't exist. Created empty one\n\n";
		throw(exception(err.c_str()));
	}
}

//Destructor
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
	_db = nullptr;
}

/*
Adds a new user to the sqlite database
Input: username, password, email
Output: none
*/
void SqliteDatabase::addNewUser(string username, string password, string email)
{
	char** errMsg = nullptr;
	int res;

	string statement = "INSERT INTO users VALUES (\"" +username+ "\", \"" +password+ "\", \"" +email+ "\");";
	res = sqlite3_exec(_db, statement.c_str(), nullptr, nullptr, errMsg);
	if (res == SQLITE_CONSTRAINT)
	{
		cerr << "username already taken or something is null" << endl;
	}
	else
		checkResult(res, "insert user");
}

/*
Function checks if user exists in the database
Input: username
Output: doesExist
*/
bool SqliteDatabase::doesUserExist(string username)
{
	char** errMsg = nullptr;
	int res;
	list<User> users;

	//Get the user
	string statement = "SELECT * FROM users WHERE username=\"" + username + "\";";
	res = sqlite3_exec(_db, statement.c_str(), usersCallback, &users, errMsg);
	checkResult(res, "check user's existance");

	if (users.empty())
		return false;

	users.clear();
	return true;
}

/*
Function checks if the password match this username's password
Input: username, password
Output: doesMatch
*/
bool SqliteDatabase::doesPasswordMatch(string username, string password)
{
	char** errMsg = nullptr;
	int res;
	list<User> users;
	bool doesMatch = false;

	//Get the user
	string statement = "SELECT * FROM users WHERE username=\"" + username + "\";";
	res = sqlite3_exec(_db, statement.c_str(), usersCallback, &users, errMsg);
	checkResult(res, "check if password matches");

	if (!users.empty())
	{
		doesMatch = users.front().password == password; //becomes true if passwords match
		users.clear();
	}

	return doesMatch;
}

///////////////////////////////////////////////////////////////////////
////////////////////////// Helper functions ///////////////////////////
/////////////////////////////////////////////////////////////////////// 

//Function checks the result after executing an sql statement
void SqliteDatabase::checkResult(int res, string subject)
{
	if (res != SQLITE_OK)
	{
		if (subject == "" || nullptr)
			subject = "something";
		cerr << "Error at \"" << subject << "\", err code: " << res << endl;
	}
}

//callback function for users
int usersCallback(void* data, int argc, char** argv, char** azColName)
{
	User user;
	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "username") {
			user.username = argv[i];
		}
		else if (string(azColName[i]) == "password") {
			user.password = argv[i];
		}
		else if (string(azColName[i]) == "email") {
			user.email = argv[i];
		}
	}
	((list<User>*)data)->push_back(user);
	return 0;
}