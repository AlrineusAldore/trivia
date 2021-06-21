#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class Communicator
{
private:
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	map<LoggedUser, SOCKET> m_socketByUser;
	map<SOCKET, LoggedUser> m_userBySocket;

	void bindAndRequests();
	void handleNewClient(SOCKET clientSock);

	HandlerType getClientHandlerType(SOCKET clientSock);
	void handleSpecialCodes(SOCKET clientSock, RequestInfo reqInfo, RequestResult reqResu);
	exception getIrrelevantException(HandlerType handlerType);

	void handleCloseGameRequest();
	void handleStartGameRequest();
public:
	Communicator(RequestHandlerFactory& RHF);
	~Communicator();

	void startHandleRequests();

	void sendUserCloseRoomResponse(LoggedUser user);
	void sendUserStartGameResponse(LoggedUser user);

};