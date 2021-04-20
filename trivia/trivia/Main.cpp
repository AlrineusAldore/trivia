#include "Server.h"

int main()
{
	try
	{
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