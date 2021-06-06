#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RoomMemberRequestHandler : public IRequestHandler
{
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult leaveRoom(RequestInfo reqInfo);
	RequestResult getRoomState(RequestInfo reqInfo);

public:
	RoomMemberRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, LoggedUser user, Room room);

	virtual bool isRequestRelevant(RequestInfo reqInfo);
	virtual RequestResult handleRequest(RequestInfo reqInfo);
};

