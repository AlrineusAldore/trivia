#pragma comment (lib, "ws2_32.lib")

#include "Server.h"
#include "WSAInitializer.h"

int main()
{
	try
	{
		srand(time(0));

		WSAInitializer wsaInit;
		Server myServer;

		myServer.run();
	}
	catch (exception& e)
	{
		cout << "Error occured: " << e.what() << endl;
	}
	system("PAUSE");
	return 0;
}