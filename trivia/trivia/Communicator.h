#pragma once

#include "IRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

class Communicator
{
public:
	Communicator();
	~Communicator();

	void startHandleRequests();

private:

	void bindAndRequests();
	void handleNewClient(SOCKET clientSock);

	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	Helper helper;
};

