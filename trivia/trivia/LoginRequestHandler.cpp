#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "ResponseStructs.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& RHF, LoginManager& LM) : m_handlerFactory(RHF), m_loginManager(LM)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	return reqInfo.id == LOGIN_CODE || reqInfo.id == SIGNUP_CODE;
}

/*
Function handles a new request by checking if its login/signup and proceeding accordingly
Input: reqInfo
Output: reqRes
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	RequestResult reqRes;
	reqRes.newHandler = nullptr;

	if (!isRequestRelevant(reqInfo))
	{
		ErrorResponse errResp;
		errResp.message = "the request is not relevent";
		reqRes.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqRes.newHandler = nullptr;
	}
	else if (reqInfo.id == LOGIN_CODE)
	{
		reqRes = login(reqInfo);
	}
	else if (reqInfo.id == SIGNUP_CODE)
	{
		reqRes = signup(reqInfo);
	}

	return reqRes;
}

/*
Function gets info of a request with login code, logs in the person, and returns the result of the request
Input: reqInfo
Output: reqResu
*/
RequestResult LoginRequestHandler::login(RequestInfo reqInfo)
{
	RequestResult reqResu;
	if (reqInfo.id != LOGIN_CODE)
		return reqResu;

	try
	{
		//Make a login-request to log in with
		LoginRequest loginReq = JsonRequestPacketDeserializer::deserializerLoginRequest(reqInfo.buffer);
		checkLoginForNull(loginReq);
		m_loginManager.login(loginReq.username, loginReq.password);

		//Serialize login buffer with next handler
		LoginResponse loginResp = { LOGIN_CODE };
		reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(loginResp);
		reqResu.newHandler = new MenuRequestHandler();
	}
	catch (exception& e)
	{
		//Make a login error result
		ErrorResponse errResp = { e.what() };
		reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqResu.newHandler = nullptr;
	}

	return reqResu;
}

/*
Function gets info of a request with signup code, signs up the person, and returns the result of the request
Input: reqInfo
Output: reqResu
*/
RequestResult LoginRequestHandler::signup(RequestInfo reqInfo)
{
	RequestResult reqResu;
	if (reqInfo.id != SIGNUP_CODE)
		return reqResu;

	try
	{
		//Make a signup-request to sign up with
		SignupRequest signupReq = JsonRequestPacketDeserializer::deserializerSingupRequest(reqInfo.buffer);
		checkSignupForNull(signupReq);
		m_loginManager.signup(signupReq.username, signupReq.password, signupReq.email);

		//Serialize signup buffer with next handler
		SignupResponse signupResp = { SIGNUP_CODE };
		reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(signupResp);
		reqResu.newHandler = new MenuRequestHandler();
	}
	catch (exception& e)
	{
		//Make a signup error result
		ErrorResponse errResp = { e.what() };
		reqResu.buffer = JsonResponsePacketSerializer::serializeResponse(errResp);
		reqResu.newHandler = nullptr;
	}

	return reqResu;
}

void LoginRequestHandler::checkLoginForNull(LoginRequest loginReq)
{
	if (loginReq.username == "")
		throw NullUsernameException();
	if (loginReq.password == "")
		throw NullPasswordException();
}

void LoginRequestHandler::checkSignupForNull(SignupRequest signupReq)
{
	if (signupReq.username == "")
		throw NullUsernameException();
	if (signupReq.password == "")
		throw NullPasswordException();
	if (signupReq.email == "")
		throw NullEmailException();
}