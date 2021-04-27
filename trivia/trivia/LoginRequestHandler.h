#include "pch.h"
#include "HandlersStructs.h"
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequstRelevent(RequestInfo RI);
	RequestResult handleRequst(RequestInfo RI);
private:

};