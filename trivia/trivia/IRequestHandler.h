#pragma once
#include "LoginRequestHandler.h"

class IRequestHandler 
{
public:
	bool isRequstRelevent(RequestInfo RI);
	RequestResult handleRequst(RequestInfo RI);

private:

};

