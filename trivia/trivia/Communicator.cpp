#include "Communicator.h"

Communicator::Communicator()
{

	helper = Helper();

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
		cout << "Waiting for client connection request" << endl;

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


void Communicator::handleNewClient(SOCKET clientSocket)
{
	try
	{
		helper.sendData(clientSocket, "hello");

		string hallo = helper.getPartFromSocket(clientSocket, MAX_BYTE_NUM);
		cout << "this is hello --> " << hallo << "." << endl;
	}
	catch (const exception& e)
	{
		closesocket(clientSocket);
	}


}

