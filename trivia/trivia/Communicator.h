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
	void handleNewClient(SOCKET sock);

	SOCKET m_serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
	Helper helper;
};

