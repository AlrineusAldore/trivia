#include "pch.h"
#include "IRequestHandler.h"

#pragma once
class Communicator
{
public:
	Communicator();
	~Communicator();

	void startHandleRequests();

private:

	void bindAndRequests();
	void handleNewClient(SOCKET Sock);

	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	Helper func;
};

