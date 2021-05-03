#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequstRelevent(RequestInfo RI)
{
	int id = RI.id;
	if (id == LOGIN_CODE || id == SIGNUP_CODE)
		return true;
	return false;
}
RequestResult LoginRequestHandler::handleRequst(RequestInfo RI)
{
}