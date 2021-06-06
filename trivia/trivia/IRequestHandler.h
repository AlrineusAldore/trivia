#pragma once
#include "HandlerStructs.h"
#include "RequestStructs.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

enum class HandlerType { Login, Menu, RoomAdmin, RoomMember, Null };

class IRequestHandler 
{
public:
	virtual bool isRequestRelevant(RequestInfo reqInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo reqInfo) = 0;

	virtual HandlerType getHandlerType() = 0;
private:

};


