#pragma once
#include "IRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statsManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult logout(RequestInfo reqInfo);
	RequestResult getRooms(RequestInfo reqInfo);
	RequestResult getPlayesrInRoom(RequestInfo reqInfo);
	RequestResult getPersonalStats(RequestInfo reqInfo);
	RequestResult getHighScore(RequestInfo reqInfo);
	RequestResult joinRoom(RequestInfo reqInfo);
	RequestResult createRoom(RequestInfo reqInfo);
public:
	MenuRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, StatisticsManager& SM, LoggedUser user);

	virtual bool isRequestRelevant(RequestInfo reqInfo);
	virtual RequestResult handleRequest(RequestInfo reqInfo);

	virtual HandlerType getHandlerType();
};

