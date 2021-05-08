#pragma once

#include "pch.h"
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo RI);
	virtual RequestResult handleRequest(RequestInfo RI);
private:

};