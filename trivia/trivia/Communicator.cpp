#include "Communicator.h"

Communicator::Communicator()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw exception(__FUNCTION__ " - socket");
	
	cout << "nice socket bro. not too large and is the perfect length. the girth is just right too. with this nice angle, it's a 9/10" << endl;
	cout << "\nwhen the socket is sus imgur.com/a/hVABhCu" << endl << endl;
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
void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		m_clients.insert({ clientSocket, new LoginRequestHandler() });

		RequestInfo RI;
		RequestResult RR;
		vector<byte> buffer;

		Helper::sendData(clientSocket, "hello");

		string clientMsg = Helper::getPartFromSocket(clientSocket, MAX_BYTE_NUM);
		
		//Turn client's msg to buffer and then make RequestInfo struct from it
		buffer = Helper::binStrToBuffer(clientMsg);
		RI.id = buffer[0];
		time(&RI.receivalTime);
		RI.buffer = buffer;

		//Handle the request
		RR = m_clients[clientSocket]->handleRequest(RI);

		//Print the cilent's message details
		if (RI.id == LOGIN_CODE)
		{
			LoginRequest lr = JsonRequestPacketDeserializer::deserializerLoginRequest(buffer);
			cout << "username: " << lr.username << "\tpassword: " << lr.password << endl;
		}
		else if (RI.id == SIGNUP_CODE)
		{
			SignupRequest sr = JsonRequestPacketDeserializer::deserializerSingupRequest(buffer);
			cout << "username: " << sr.username << "\tpassword: " << sr.password << "\temail: " << sr.email << endl;
		}
		else
			cout << "Not login nor signup" << endl;
		

		//Turn RR.buffer to bin string and send it to client
		//Helper::sendData(clientSocket, (string ver of RR.buffer));
		//Supposedly the end of 1.0.2
	}
	catch (const exception& e)
	{
		closesocket(clientSocket);
	}
}
