#include "Server.h"

Server::Server() : m_database(new SqliteDatabase()), m_handlerFactory(RequestHandlerFactory(m_database)), m_communicator(Communicator(m_handlerFactory))
{
}

void Server::run()
{
	//poof the m_handlerFactory database is boom boom capot and gone, like a wind by the air,
	//like your dad when you were 3 years old, just gone vanish and disapear.
	//news tell us that we do not have any clues and its one of the greatest measterys of the trivia univers,
	//in the next summer the new movie "database gone gone" i will be the fastes movie that all of you going to forget.
	//youtube: "a DaTaBaSe IS GONE!!! you not gunna belive in this, 99% of you will not know anything"
	//in the streats: "omg nice socket broooo, YOU ARE RECORDING THAT STOP IT"
	//bibi: there isnt a database because there wasent a database
	//palestine: DaTaBaSe go boom boom LOL.
	//m_communicator.setFactory(m_handlerFactory);
	m_communicator.startHandleRequests();
}