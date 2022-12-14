#pragma once
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestHandlerFactory& m_handlerFactory;
	LoginManager& m_loginManager;

	RequestResult login(RequestInfo reqInfo);
	RequestResult signup(RequestInfo reqInfo);

	void checkLoginForNull(LoginRequest loginReq);
	void checkSignupForNull(SignupRequest signupReq);

public:
	LoginRequestHandler(RequestHandlerFactory& RHF, LoginManager& LM);

	virtual bool isRequestRelevant(RequestInfo reqInfo);
	virtual RequestResult handleRequest(RequestInfo reqInfo);

	virtual HandlerType getHandlerType();
};