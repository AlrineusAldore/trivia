#pragma once
#include "pch.h"
#include "IDatabase.h"
#include "LoginManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();	
	LoginManager& getLoginManager();
};

