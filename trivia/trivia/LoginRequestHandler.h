#pragma once

#include "pch.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "LoginManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequestStructs.h"

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;

	RequestResult login(RequestInfo RI);
	RequestResult signup(RequestInfo RI);

public:
	//LoginRequestHandler(IDatabase* db);

	virtual bool isRequestRelevant(RequestInfo RI);
	virtual RequestResult handleRequest(RequestInfo RI);
};