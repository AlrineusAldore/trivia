#pragma once

#include "pch.h"
#include "Communicator.h"

class Server
{
public:
	
	void run();

private:

	Communicator m_communlcator;
};

