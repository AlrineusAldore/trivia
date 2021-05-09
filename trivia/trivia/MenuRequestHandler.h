#pragma once
#include "IRequestHandler.h"
class MenuRequestHandler : public IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo RI) {};
	virtual RequestResult handleRequest(RequestInfo RI) {};
};

