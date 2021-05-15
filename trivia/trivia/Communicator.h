#pragma once

#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Helper.h"

class Communicator
{
private:
	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	void bindAndRequests();
	void handleNewClient(SOCKET clientSock);

public:
	Communicator(RequestHandlerFactory RHF);
	~Communicator();

	void startHandleRequests();
};

