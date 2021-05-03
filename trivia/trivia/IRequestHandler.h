#pragma once
#include "pch.h"

class IRequestHandler 
{
public:
	virtual bool isRequstRelevent(RequestInfo RI) = 0;
	virtual RequestResult handleRequst(RequestInfo RI) = 0;

private:

};

