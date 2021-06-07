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

	cout << "Client accepted. Server and client can speak" << endl;

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
	try
	{
		m_clients.insert({ clientSock, m_handlerFactory.createLoginRequestHandler() });

		pair<RequestInfo, RequestResult> requestPair;
		RequestInfo reqInfo;
		RequestResult reqResu;

		if (reqInfo.id == CLOSE_ROOM_CODE)
		{
			
		}
		
		//Until client closes program
		while (true)
		{
			handleGeneralRequest(clientSock);
		}
	}
	catch (const exception& e)
	{
		//If client already logged in and crashed/left somewhen after
		if (m_clients[clientSock] == nullptr || m_clients[clientSock]->getHandlerType() != HandlerType::Login)
		{
			//Remove his user from communicator
			m_socketByUser.erase(m_userBySocket[clientSock]);
			m_userBySocket.erase(clientSock);
		}
		
		closesocket(clientSock);
		cerr << "error: " << e.what() << endl;
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
Function handles a client and calls the appropriate RequestHandler
Input: clientSock, handlerType
Output: pair of RequestInfo from client & RequestResult from server
*/
pair<RequestInfo, RequestResult> Communicator::handleGeneralRequest(SOCKET clientSock)
{
	RequestResult reqResu;
	RequestInfo reqInfo;
	string clientMsg = "";
	Buffer buffer;

	//waiting to get client's request
	clientMsg = Helper::getPartFromSocket(clientSock, MAX_BYTE_NUM);

	//Turn client's msg to buffer and make RequestInfo struct from it
	buffer = Helper::binStrToBuffer(clientMsg);
	reqInfo.id = buffer[0];
	time(&reqInfo.receivalTime);
	reqInfo.buffer = buffer;

	//If request is relevant, handle it. Otherwise throw the appropriate exception
	if (m_clients[clientSock]->isRequestRelevant(reqInfo))
		reqResu = m_clients[clientSock]->handleRequest(reqInfo);
	else
		throw getIrrelevantException(getClientHandlerType(clientSock));

	handleSpecialCodes(clientSock, reqInfo, reqResu);

	//Send the server's response to the client
	Helper::sendData(clientSock, Helper::bufferToBinStr(reqResu.buffer));

	//change client's handler to the new one
	m_clients[clientSock] = reqResu.newHandler;

	return make_pair(reqInfo, reqResu);
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

/*
Handles special codes that use communicator's LoggedUsers
Input: clientSock, reqInfo, reqResu
Output: none
*/
void Communicator::handleSpecialCodes(SOCKET clientSock, RequestInfo reqInfo, RequestResult reqResu)
{
	Buffer buffer = reqInfo.buffer;

	switch (reqInfo.id)
	{
		//Print the cilent's message details & add them to users if succeeded
		case LOGIN_CODE:
		{
			LoginRequest lr = JsonRequestPacketDeserializer::deserializeLoginRequest(buffer);
			cout << "username: " << lr.username << "\t\tpassword: " << lr.password << endl;
			if (reqResu.newHandler != nullptr) //successfully logged in or signed up
			{
				m_socketByUser.insert({ lr.username, clientSock }); //insert user to communicator
				m_userBySocket.insert({ clientSock, lr.username });
			}
			break;
		}

		//Print the cilent's message details & add them to users if succeeded
		case SIGNUP_CODE:
		{
			SignupRequest sr = JsonRequestPacketDeserializer::deserializeSingupRequest(buffer);
			cout << "username: " << sr.username << "\t\tpassword: " << sr.password << "\t\temail: " << sr.email << endl;
			if (reqResu.newHandler != nullptr) //successfully logged in or signed up
			{
				m_socketByUser.insert({ sr.username, clientSock }); //insert user to communicator
				m_userBySocket.insert({ clientSock, sr.username });
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
		}
	}
}


//For when 1 user needs to notify others
void Communicator::sendUserLeaveRoomResponse(LoggedUser user)
{
	RequestResult reqResu;
	SOCKET clientSock = m_socketByUser[user];

	//Serialize response buffer
	LeaveRoomResponse leaveRoomRes;
	leaveRoomRes.status = LEAVE_ROOM_CODE;

	reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(leaveRoomRes);
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
	startGameRes.status = LEAVE_ROOM_CODE;

	reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(startGameRes);
	reqResu.newHandler = m_clients[clientSock]; //Should be correct handler

	//Send the server's response to the client
	Helper::sendData(clientSock, Helper::bufferToBinStr(reqResu.buffer));

	//change client's handler to the new one
	m_clients[clientSock] = reqResu.newHandler;
}