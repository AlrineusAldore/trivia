#pragma once
#include "pch.h"
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;
public:
	RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();	
	LoginManager& getLoginManager();
};

