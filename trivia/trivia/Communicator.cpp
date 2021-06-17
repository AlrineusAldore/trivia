#include "Communicator.h"

Communicator::Communicator(RequestHandlerFactory& RHF) : m_handlerFactory(RHF)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw exception(__FUNCTION__ " - socket");
	
	cout << "\nwhen the socket is sus" << endl;
	Helper::sus();
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
	{
		cout << "error: " << WSAGetLastError() << endl;
		throw exception(__FUNCTION__ " - bind");
	}

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw exception(__FUNCTION__ " - listen");
	cout << "Listening on port " << PORT << endl;



	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		cout << "Waiting for client connection request" << endl << endl;

		bindAndRequests();
	}
}


void Communicator::bindAndRequests()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(m_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw exception(__FUNCTION__);

	cout << "\nClient accepted. Server and client can speak" << endl;

	// the function that handle the conversation with the client

	thread thr(&Communicator::handleNewClient, this, client_socket);
	thr.detach();
}


/*
The method that handles a new client that connects and is called 1 time per client connected
Input: clientSocket
Output: none
*/
void Communicator::handleNewClient(SOCKET clientSock)
{
	RequestInfo reqInfo;
	RequestResult reqResu;
	Buffer buffer;

	try
	{
		m_clients.insert({ clientSock, m_handlerFactory.createLoginRequestHandler() });
		
		//Until client closes program
		while (true)
		{
			//waiting to get client's request
			buffer = Helper::getBufferFromClient(clientSock);

			cout << "client msg len: " << buffer.size() - 5 << endl;
			cout << "client msg: " << Helper::bufferToStr(buffer) << endl;
			//Turn client's msg to buffer and make RequestInfo struct from it
			reqInfo.id = buffer[0];
			time(&reqInfo.receivalTime);
			reqInfo.buffer = buffer;

			//If request is relevant, handle it. Otherwise throw the appropriate exception
			if (m_clients[clientSock]->isRequestRelevant(reqInfo))
				reqResu = m_clients[clientSock]->handleRequest(reqInfo);
			else
				throw getIrrelevantException(getClientHandlerType(clientSock));

			handleSpecialCodes(clientSock, reqInfo, reqResu);

			cout << "server msg len: " << reqResu.buffer.size()-5 << endl;
			Buffer binLenBuf (reqResu.buffer.begin() + 1, reqResu.buffer.begin() + 5);
			cout << "server msg len bin: " << Helper::bufferToBinStr(binLenBuf) << endl;
			cout << "\nserver msg: " << Helper::bufferToStr(reqResu.buffer) << endl << endl;
			//Send the server's response to the client
			Helper::sendData(clientSock, Helper::bufferToBinStr(reqResu.buffer));

			//change client's handler to the new one
			if (m_clients[clientSock] != reqResu.newHandler)
				delete m_clients[clientSock];
			m_clients[clientSock] = reqResu.newHandler;
		}
	}
	catch (const exception& e)
	{
		try
		{
			if (m_clients[clientSock] != nullptr)
			{
				switch (m_clients[clientSock]->getHandlerType())
				{
				case HandlerType::RoomAdmin:
				{
					//close room admin's room
					reqInfo.id = CLOSE_ROOM_CODE;
					handleSpecialCodes(clientSock, reqInfo, reqResu);
					break;
				}
				case HandlerType::RoomMember:
				{
					//remove room member from room
					Room* room = ((RoomMemberRequestHandler*)m_clients[clientSock])->getRoom();
					room->removeUser(m_userBySocket[clientSock]);
					break;
				}
				}
			}
			m_handlerFactory.getLoginManager().logout(m_userBySocket[clientSock].getUsername());

			//If client already logged in and crashed/left somewhen after
			if (m_clients[clientSock] == nullptr || m_clients[clientSock]->getHandlerType() != HandlerType::Login)
			{
				//Remove his user from communicator
				m_socketByUser.erase(m_userBySocket[clientSock]);
				m_userBySocket.erase(clientSock);
			}

			m_clients.erase(clientSock);

			closesocket(clientSock);
			cerr << __FUNCTION__ << " - error: " << e.what() << endl;
		}
		catch (exception e)
		{
			cerr << __FUNCTION__ << "- nested catch, error: " << e.what() << endl;
		}
	}
}

/*
Function returns the current handler type
Input: clientSock
Output: HandlerType
*/
HandlerType Communicator::getClientHandlerType(SOCKET clientSock)
{
	//if null then return null
	if (m_clients[clientSock] == nullptr)
		return HandlerType::Null;
	
	//otherwise, return its type
	return m_clients[clientSock]->getHandlerType();
}


/*
Handles special codes that use communicator's LoggedUsers
Input: clientSock, reqInfo, reqResu
Output: none
*/
void Communicator::handleSpecialCodes(SOCKET clientSock, RequestInfo reqInfo, RequestResult reqResu)
{
	Buffer buffer = reqInfo.buffer;

	try
	{
		switch (reqInfo.id)
		{
			//Print the cilent's message details & add them to users if succeeded
		case LOGIN_CODE:
		{
			LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(buffer);
			if (reqResu.newHandler != nullptr) //successfully logged in or signed up
			{
				LoggedUser user = LoggedUser(lr.username);
				m_socketByUser.insert({ user, clientSock }); //insert user to communicator
				m_userBySocket.insert({ clientSock, user });
			}
			break;
		}

		//Print the cilent's message details & add them to users if succeeded
		case SIGNUP_CODE:
		{
			SignupRequest sr = JsonRequestPacketDeserializer::deserializeSingupRequest(buffer);
			if (reqResu.newHandler != nullptr) //successfully logged in or signed up
			{
				LoggedUser user = LoggedUser(sr.username);
				m_socketByUser.insert({ user, clientSock }); //insert user to communicator
				m_userBySocket.insert({ clientSock, user });
			}
			break;
		}

		//If user logged out, log him out of communicator
		case LOGOUT_CODE:
		{
			//Makes sure the logout was successful by confirming the result's parameters
			if (reqResu.newHandler != nullptr && reqResu.newHandler->getHandlerType() == HandlerType::Login)
			{
				m_socketByUser.erase(m_userBySocket[clientSock]);
				m_userBySocket.erase(clientSock);
			}
			break;
		}

		case CLOSE_ROOM_CODE:
		{
			if (m_clients[clientSock]->getHandlerType() != HandlerType::RoomAdmin)
				throw exception(__FUNCTION__" - unexpected incorrect handler at close room");

			//get room & all the users in it
			Room* room = ((RoomAdminRequestHandler*)m_clients[clientSock])->getRoom();
			vector<string> roomMembers = room->getAllUsers();

			//Send it to all users in room
			for (auto it : roomMembers)
			{
				LoggedUser currUser = LoggedUser(it);
				//if user exists in communicator & isn't room admin, send close game resp
				if (m_socketByUser.count(currUser) > 0 && currUser != m_userBySocket[clientSock])
					sendUserCloseRoomResponse(currUser);
			}

			//Remove room from roomManager and delete it
			m_handlerFactory.getRoomManager().deleteRoom(room->getRoomData().id);

			break;
		}

		case START_GAME_CODE:
		{
			if (m_clients[clientSock]->getHandlerType() != HandlerType::RoomAdmin)
				throw exception(__FUNCTION__" - unexpected incorrect handler at start game");

			//get room & all the users in it
			Room* room = ((RoomAdminRequestHandler*)m_clients[clientSock])->getRoom();
			vector<string> roomMembers = room->getAllUsers();

			//Start game for every other player in room
			for (auto& it : room->getAllUsers())
			{
				LoggedUser currUser = LoggedUser(it);
				//if user exists in communicator & isn't the admin, send start game resp
				if (m_socketByUser.count(currUser) > 0 && currUser != m_userBySocket[clientSock])
					sendUserStartGameResponse(currUser);
			}

			break;
		}
		}
	}
	catch (exception e)
	{
		cerr << __FUNCTION__ << " - error: " << e.what() << endl;
	}
}


//For when 1 user needs to notify others
void Communicator::sendUserCloseRoomResponse(LoggedUser user)
{
	RequestResult reqResu;
	SOCKET clientSock = m_socketByUser[user];

	//Serialize response buffer
	CloseRoomResponse closeRoomResp;
	closeRoomResp.status = CLOSE_ROOM_CODE;

	reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(closeRoomResp);
	reqResu.newHandler = m_clients[clientSock]; //Should be correct handler

	//Send the server's response to the client
	Helper::sendData(clientSock, Helper::bufferToBinStr(reqResu.buffer));

	//change client's handler to the new one
	m_clients[clientSock] = reqResu.newHandler;
}

//For when 1 user needs to notify others
void Communicator::sendUserStartGameResponse(LoggedUser user)
{
	RequestResult reqResu;
	SOCKET clientSock = m_socketByUser[user];

	//Serialize response buffer
	StartGameResponse startGameRes;
	startGameRes.status = START_GAME_CODE;

	reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(startGameRes);
	reqResu.newHandler = m_clients[clientSock]; //Should be correct handler

	//Send the server's response to the client
	Helper::sendData(clientSock, Helper::bufferToBinStr(reqResu.buffer));

	//change client's handler to the new one
	m_clients[clientSock] = reqResu.newHandler;
}


//Returns the relevant irrelevant exception based on the handler type
exception Communicator::getIrrelevantException(HandlerType handlerType)
{
	switch (handlerType)
	{
	case HandlerType::Login:
		return IrrelevantLoginException();
		break;

	case HandlerType::Menu:
		return IrrelevantMenuException();
		break;

	case HandlerType::RoomAdmin:
		return IrrelevantRoomAdminException();
		break;

	case HandlerType::RoomMember:
		return IrrelevantRoomMemberException();
		break;

	case HandlerType::Null:
		return exception(__FUNCTION__" - unexpected nullptr exception");
		break;

	default:
		return exception(__FUNCTION__" - unexpected exception");
	}
}

void Communicator::handleCloseGameRequest()
{
	
}

void Communicator::handleStartGameRequest()
{

}