#pragma once

#include "pch.h"
#include "Communicator.h"

class Server
{
public:
	
	Server();
	void run();

private:

	Communicator m_communicator;
};

