#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
private:
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statsManager;

public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();	
	LoginManager& getLoginManager();

	MenuRequestHandler* createMenuRequestHandler();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
};

