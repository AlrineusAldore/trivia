#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{

}
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
