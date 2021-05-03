#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo RI)
{
	int id = RI.id;
	if (id == LOGIN_CODE || id == SIGNUP_CODE)
		return true;
	return false;
}
RequestResult LoginRequestHandler::handleRequest(RequestInfo RI)
{
	
}