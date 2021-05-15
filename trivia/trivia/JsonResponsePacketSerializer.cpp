#include "JsonResponsePacketSerializer.h"

vector<byte> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes)
{
    return unpackJsonResponse(ERROR_CODE, errorRes.message);
}

vector<byte> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes)
{
    return unpackJsonResponse(loginRes.status, "The login was successful!");
}

vector<byte> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes)
{

    return unpackJsonResponse(signupRes.status, "You signed up successfuly!");
}


/*
Gets a string and returns it as binary buffer
Input: string str, int code
Output: buffer
*/
vector<byte> JsonResponsePacketSerializer::unpackJsonResponse(int code, string str)
{
    try
    {
        vector<byte> buffer;
        buffer.push_back(code);
        int len = str.length();

        //push the len to buffer as 4 bytes
        buffer.push_back((len >> 24) & 0xFF);
        buffer.push_back((len >> 16) & 0xFF);
        buffer.push_back((len >> 8) & 0xFF);
        buffer.push_back((len >> 0) & 0xFF);

        for (int i = 0; i < len; i++)
        {
            buffer.push_back(str[i]);
        }

        return buffer;
    }
    catch (const exception& e)
    {
        cerr << "Error at " << (__FUNCTION__) << ".\tError: " << e.what() << endl;
    }

    return vector<byte>();
}