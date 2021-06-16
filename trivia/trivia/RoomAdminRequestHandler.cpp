#include "RoomAdminRequestHandler.h"
#include "MenuRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, LoggedUser user, Room room) : m_handlerFactory(RHF), m_roomManager(RM), m_user(user), m_room(room)
{ }

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	int id = reqInfo.id;
	return (id == CLOSE_ROOM_CODE || id == START_GAME_CODE || id == GET_ROOM_STATE_CODE);
}

HandlerType RoomAdminRequestHandler::getHandlerType()
{
	return HandlerType::RoomAdmin;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;

	switch (reqInfo.id)
	{
	case CLOSE_ROOM_CODE:
		reqRes = closeRoom(reqInfo);
		break;
	case START_GAME_CODE:
		reqRes = startGame(reqInfo);
		break;
	case GET_ROOM_STATE_CODE:
		reqRes = getRoomState(reqInfo);
		break;

	default:
		ErrorResponse errResp;
		errResp.message = "The request is not relevent";
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
		throw(IrrelevantRoomAdminException());
		break;
	}

	return reqRes;
}


RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != CLOSE_ROOM_CODE)
		return reqRes;

	try
	{
		//Sends leave room responses in communicator

		//Serialize response buffer
		CloseRoomResponse closeRoomRes;
		closeRoomRes.status = CLOSE_ROOM_CODE;

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(closeRoomRes);
		reqRes.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	}
	catch (exception& e)
	{
		//Make an error response
		ErrorResponse errResp = { e.what() };
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
		cerr << __FUNCTION__ << " - error: " << e.what() << endl;
	}

	return reqRes;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != START_GAME_CODE)
		return reqRes;

	try
	{
		//Sends responses to room members in communicator

		//Serialize response buffer
		StartGameResponse startGameRes;
		startGameRes.status = START_GAME_CODE;

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(startGameRes);
		reqRes.newHandler = this;
	}
	catch (exception& e)
	{
		//Make an error response
		ErrorResponse errResp = { e.what() };
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
		cerr << __FUNCTION__ << " - error: " << e.what() << endl;
	}

	return reqRes;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != GET_ROOM_STATE_CODE)
		return reqRes;

	try
	{
		//Serialize response buffer
		GetRoomStateResponse getRoomStateRes = Helper::putRoomDataInRoomState(m_room.getRoomData(), m_room.getAllUsers());

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(getRoomStateRes);
		reqRes.newHandler = this;
	}
	catch (exception& e)
	{
		//Make an error response
		ErrorResponse errResp = { e.what() };
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
		cerr << __FUNCTION__ << " - error: " << e.what() << endl;
	}

	return reqRes;
}


//returns a reference to the admin's room
Room& RoomAdminRequestHandler::getRoom()
{
	return m_room;
}