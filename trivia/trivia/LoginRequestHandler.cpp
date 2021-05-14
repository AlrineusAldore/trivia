#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "ResponseStructs.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory RHF, LoginManager LM) : m_handlerFactory(RHF), m_loginManager(LM)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo RI)
{
	int id = RI.id;
	if (id == LOGIN_CODE || id == SIGNUP_CODE)
		return true;
	return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo RI)
{
	RequestResult RR;

	if (!isRequestRelevant(RI))
	{
		ErrorResponse ER;
		ER.message = "the request is not relevent";
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(ER);
		RR.newHandler = nullptr;
	}
	else if (RI.id == LOGIN_CODE)
	{
		LoginResponse LR;
		LR.status = LOGIN_CODE;

		//Serialize login buffer with next handler
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(LR);
		RR.newHandler = new MenuRequestHandler();

		//login request 
		LoginRequest lr = JsonRequestPacketDeserializer::deserializerLoginRequest(RR.buffer);
		m_loginManager.login(lr.username, lr.password);
	}
	else
	{
		SignupResponse SR;
		SR.status = SIGNUP_CODE;

		//serialize signup buffer with next handler
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(SR);
		RR.newHandler = new MenuRequestHandler();

		SignupRequest sr = JsonRequestPacketDeserializer::deserializerSingupRequest(RR.buffer);
		m_loginManager.signup(sr.username, sr.password, sr.email);
	}
	RR.newHandler = NULL;
	return RR;
}