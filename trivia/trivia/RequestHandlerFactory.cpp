#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db)
{
	m_loginManager = new LoginManager(db);
	m_database = db;
}
RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_loginManager;
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler();
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return *m_loginManager;
}
