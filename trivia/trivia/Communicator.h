#pragma once

#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Helper.h"

class Communicator
{
public:
	Communicator(RequestHandlerFactory RHF);
	~Communicator();

	void startHandleRequests();

private:

	void bindAndRequests();
	void handleNewClient(SOCKET clientSock);

	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
};

