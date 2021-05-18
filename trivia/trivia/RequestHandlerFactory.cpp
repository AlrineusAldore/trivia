#include "RequestHandlerFactory.h"
#include "LoginRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_loginManager(LoginManager(db))
{
	m_database = db;
}
RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this, m_loginManager);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}
