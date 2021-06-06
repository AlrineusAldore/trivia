#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, LoggedUser user, Room room) : m_handlerFactory(RHF), m_roomManager(RM), m_user(user), m_room(room)
{ }

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	int id = reqInfo.id;
	return (id == LEAVE_ROOM_CODE || id == GET_ROOM_STATE_CODE);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;

	switch (reqInfo.id)
	{
	case LEAVE_ROOM_CODE:
		reqRes = leaveRoom(reqInfo);
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != LEAVE_ROOM_CODE)
		return reqRes;

	try
	{
		//Leaves the room
		m_room.removeUser(m_user);

		//Serialize response buffer
		LeaveRoomResponse leaveRoomRes;
		leaveRoomRes.status = LEAVE_ROOM_CODE;

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(leaveRoomRes);
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

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo reqInfo)
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