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
		struct ErrorResponse ER;
		ER.message = "the request is not relevent";
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(ER);
	}
	else if (RI.id == LOGIN_CODE)
	{
		struct LoginResponse LR;
		LR.status = LOGIN_CODE;
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(LR);
	}
	else
	{
		struct SignupResponse SR;
		SR.status = LOGIN_CODE;
		RR.buffer = JsonResponsePacketSerializer::serializeResponse(SR);
	}
	RR.newHandler = NULL;
	return RR;
}