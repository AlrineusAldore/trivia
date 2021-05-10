#pragma once
#include "IDatabase.h"
class SqliteDatabase : public IDatabase
{
private:
	sqlite3* _db;


	void checkResult(int res, string subject);

public:
	SqliteDatabase();
	~SqliteDatabase();

	virtual void addNewUser(string username, string password, string email);

	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);
};

