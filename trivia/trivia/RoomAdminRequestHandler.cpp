#include "RoomAdminRequestHandler.h"
#include "Communicator.h"

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
		//Send every other user a leaveRoomResponse
		for (auto& it : m_room.getAllUsers())
		{
			if (it != m_user)
				m_handlerFactory.getCommunicator().sendUserLeaveRoomResponse(it);
		}
		//Remove room from roomManager and delete it
		m_roomManager.deleteRoom(m_room.getRoomData().id);

		//Serialize response buffer
		CloseRoomResponse closeRoomRes;
		closeRoomRes.status = CLOSE_ROOM_CODE;

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(closeRoomRes);
		reqRes.newHandler = this;
	}
	catch (exception& e)
	{
		//Make an error response
		ErrorResponse errResp = { e.what() };
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
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
		//Start game for every other player in room
		for (auto& it : m_room.getAllUsers())
		{
			if (it != m_user)
				m_handlerFactory.getCommunicator().sendUserStartGameResponse(it);
		}

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
	}

	return reqRes;
}