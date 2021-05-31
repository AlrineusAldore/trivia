#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& RHF, RoomManager& RM, StatisticsManager& SM, LoggedUser user) : m_handlerFactory(RHF), m_roomManager(RM), m_statsManager(SM), m_user(user)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo RI)
{
	return true;
}
RequestResult MenuRequestHandler::handleRequest(RequestInfo RI)
{
	return RequestResult();
}