#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "ResponseStructs.h"

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
		RR.newHandler = new LoginRequestHandler();
	}
	else if (RI.id == LOGIN_CODE)
	{
		LoginResponse LR;
		LR.status = LOGIN_CODE;
		//call login manager needed
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(LR);
		RR.newHandler = new MenuRequestHandler();
	}
	else
	{
		SignupResponse SR;
		SR.status = SIGNUP_CODE;
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(SR);
		RR.newHandler = new MenuRequestHandler();
	}
	RR.newHandler = NULL;
	return RR;
}