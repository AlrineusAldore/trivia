#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_loginManager(LoginManager(db)), m_roomManager(RoomManager()), m_statsManager(StatisticsManager(db))
{
	m_database = db;
}
RequestHandlerFactory::~RequestHandlerFactory()
{
}

//Creating request handlers
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this, m_loginManager);
}
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(*this, m_roomManager, m_statsManager, user);
}
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser user, Room room)
{
	return new RoomAdminRequestHandler(*this, m_roomManager, user, room);
}
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser user, Room room)
{
	return new RoomMemberRequestHandler(*this, m_roomManager, user, room);
}

//Getters (references)
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}
StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return m_statsManager;
}
RoomManager& RequestHandlerFactory::getRoomManager()
{
	return m_roomManager;
}