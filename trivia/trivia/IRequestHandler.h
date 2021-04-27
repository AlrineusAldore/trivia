#pragma once
#include "LoginRequestHandler.h"
#include "HandlersStructs.h"

class IRequestHandler : public LoginRequestHandler
{
public:
	bool isRequstRelevent(RequestInfo RI);
	RequestResult handleRequst(RequestInfo RI);

private:

};

