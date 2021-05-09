#pragma once
#include "pch.h"
#include "HandlerStructs.h"

class IRequestHandler 
{
public:
	virtual bool isRequestRelevant(RequestInfo RI) = 0;
	virtual RequestResult handleRequest(RequestInfo RI) = 0;

private:

};

