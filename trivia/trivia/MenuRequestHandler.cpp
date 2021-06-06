#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, StatisticsManager& SM, LoggedUser user) : m_handlerFactory(RHF), m_roomManager(RM), m_statsManager(SM), m_user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	int id = reqInfo.id;
	return (id == GET_ROOMS_CODE || id == CREATE_ROOM_CODE || id == LOGOUT_CODE || id == JOIN_ROOM_CODE ||
		id == GET_PERSONAL_STATS_CODE || id == GET_HIGH_SCORE_CODE || id == GET_PLAYERS_IN_ROOM_CODE);
}
RequestResult MenuRequestHandler::handleRequest(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	int id = reqInfo.id;

	if (!isRequestRelevant(reqInfo))
	{
		ErrorResponse errResp;
		errResp.message = "the request is not relevent";
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
	}
	else if (id == GET_ROOMS_CODE)
		reqRes = getRooms(reqInfo);
	else if(id == CREATE_ROOM_CODE)
		reqRes = createRoom(reqInfo);
	else if(id == LOGOUT_CODE)
		reqRes = logout(reqInfo);
	else if(id == JOIN_ROOM_CODE)
		reqRes = joinRoom(reqInfo);
	else if(id == GET_PERSONAL_STATS_CODE)
		reqRes = getPersonalStats(reqInfo);
	else if(id == GET_HIGH_SCORE_CODE)
		reqRes = getHighScore(reqInfo);
	else if (id == GET_PLAYERS_IN_ROOM_CODE)
		reqRes = getPlayesrInRoom(reqInfo);

	return reqRes;
}

HandlerType MenuRequestHandler::getHandlerType()
{
	return HandlerType::Menu;
}

/*
Function logs out user out of the system with the request info
Input: reqInfo
Output: reqResu
*/
RequestResult MenuRequestHandler::logout(RequestInfo reqInfo)
{
	RequestResult reqResu;
	reqResu.newHandler = nullptr;
	if (reqInfo.id != LOGOUT_CODE)
		return reqResu;

	try
	{
		//Log out of the system
		m_handlerFactory.getLoginManager().logout(m_user.getUsername());
		
		//Serialize logout buffer
		LogoutResponse logoutResp = { LOGOUT_CODE };
		reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(logoutResp);
		reqResu.newHandler = nullptr;
	}
	catch (exception& e)
	{
		//Make a logout error result
		ErrorResponse errResp = { e.what() };
		reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqResu.newHandler = nullptr;
	}

	return reqResu;
}

/*
Function gets all the rooms in the system and returns them
Input: reqInfo
Output: reqResu
*/
RequestResult MenuRequestHandler::getRooms(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != GET_ROOMS_CODE)
		return reqRes;

	try
	{
		//Serialize response buffer
		GetRoomsResponse getRoomsResp;
		getRoomsResp.status = GET_ROOMS_CODE;
		getRoomsResp.rooms = m_roomManager.getRooms();

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(getRoomsResp);
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

/*
Function returns a result containing all the players in the room
Input: reqInfo containing room id
Output: reqResu containing all players in room
*/
RequestResult MenuRequestHandler::getPlayesrInRoom(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != GET_PLAYERS_IN_ROOM_CODE)
		return reqRes;

	try
	{
		unsigned int roomId = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(reqInfo.buffer).roomId;
		
		//Serialize response buffer
		GetPlayersInRoomResponse getPlayersInRoomResp;
		getPlayersInRoomResp.players = m_roomManager.getRoom(roomId).getAllUsers();
		
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResp);
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

/*
Function returns a result containing the stats of the user
Input: reqInfo
Output: reqRes containing user stats
*/
RequestResult MenuRequestHandler::getPersonalStats(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != GET_PERSONAL_STATS_CODE)
		return reqRes;

	try
	{
		//Serialize response buffer
		GetPersonalStatsResponse getPersonalStatsResp;
		getPersonalStatsResp.status = GET_PERSONAL_STATS_CODE;
		getPersonalStatsResp.stats = m_statsManager.getUserStatistics(m_user.getUsername());

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(getPersonalStatsResp);
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

/*
Function returns a result containing the top 5 high scores
Input: reqInfo
Output: reqRes containing top 5 highscores
*/
RequestResult MenuRequestHandler::getHighScore(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != GET_HIGH_SCORE_CODE)
		return reqRes;

	try
	{
		//Serialize response buffer
		GetHighScoreResponse getHighScoreResp;
		getHighScoreResp.status = GET_HIGH_SCORE_CODE;
		getHighScoreResp.highScores = m_statsManager.getHighScores();

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(getHighScoreResp);
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

/*
Function adds the user to the requested room
Input: reqInfo containing room id
Output: reqRes
*/
RequestResult MenuRequestHandler::joinRoom(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != JOIN_ROOM_CODE)
		return reqRes;

	try
	{
		//Add user to room
		unsigned int roomId = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(reqInfo.buffer).roomId;
		m_roomManager.getRoom(roomId).addUser(m_user);

		//Serialize response buffer
		JoinRoomResponse joinRoomRes;
		joinRoomRes.status = JOIN_ROOM_CODE;

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(joinRoomRes);
		reqRes.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user, m_roomManager.getRoom(roomId));
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

/*
Function creates a room
Input: reqInfo containing all of the room's properties
Output: reqRes
*/
RequestResult MenuRequestHandler::createRoom(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;
	if (reqInfo.id != CREATE_ROOM_CODE)
		return reqRes;

	try
	{
		//Creates a room
		CreateRoomRequest createRoomReq = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(reqInfo.buffer);
		RoomData roomData;
		roomData.id = 0; //proper id is created when creating room
		roomData.isActive = false; //Room starts in waiting state
		roomData.maxPlayers = createRoomReq.maxUsers;
		roomData.name = createRoomReq.roomName;
		roomData.numOfQuestionsInGame = createRoomReq.questionCount;
		roomData.timePerQuestion = createRoomReq.answerTimeout;

		unsigned int id = m_roomManager.createRoom(m_user, roomData);

		//Serialize response buffer
		CreateRoomResponse createRoomRes;
		createRoomRes.status = CREATE_ROOM_CODE;

		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(createRoomRes);
		reqRes.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_roomManager.getRoom(id));
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