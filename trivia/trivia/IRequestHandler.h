#pragma once
#include "HandlerStructs.h"
#include "RequestStructs.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

enum class RequestHandlerType { Login, Menu, RoomAdmin, RoomMember };

class IRequestHandler 
{
public:
	virtual bool isRequestRelevant(RequestInfo reqInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo reqInfo) = 0;

	virtual RequestHandlerType getHandlerType() = 0;
private:

};


