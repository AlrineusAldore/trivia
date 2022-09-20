#include "Server.h"

Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(RequestHandlerFactory(m_database)), m_communicator(Communicator(m_handlerFactory))
{
}

void Server::run()
{
	m_communicator.startHandleRequests();
}