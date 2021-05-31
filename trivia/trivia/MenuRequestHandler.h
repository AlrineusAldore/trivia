#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statsManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(RequestInfo reqInfo);
	RequestResult getRooms(RequestInfo reqInfo);
	RequestResult getPlayesrInRoom(RequestInfo reqInfo);
	RequestResult getPersonalStats(RequestInfo reqInfo);
	RequestResult getHighScore(RequestInfo reqInfo);
	RequestResult joinRoom(RequestInfo reqInfo);
	RequestResult createRoom(RequestInfo reqInfo);
public:
	MenuRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, StatisticsManager& SM, LoggedUser user);

	virtual bool isRequestRelevant(RequestInfo RI);
	virtual RequestResult handleRequest(RequestInfo RI);
};

