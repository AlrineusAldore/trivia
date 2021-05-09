#pragma once

#include "pch.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;

public:
	virtual bool isRequestRelevant(RequestInfo RI);
	virtual RequestResult handleRequest(RequestInfo RI);
private:
	RequestResult login(RequestInfo RI);
	RequestResult signup(RequestInfo RI);

};