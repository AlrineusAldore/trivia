#include "JsonResponsePacketSerializer.h"

vector<byte> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorRes)
{
    return unpackJsonResponse(errorRes.message);
}

vector<byte> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginRes)
{
    return unpackJsonResponse(to_string(loginRes.status));
}

vector<byte> JsonResponsePacketSerializer::serializeResponse(SignupResponse signupRes)
{
    return unpackJsonResponse(to_string(signupRes.status));
}


/*
Gets a string representing a binary sequence of our buffer and turn it into vector<byte>
Input: string strBin
Output: buffer
*/
vector<byte> JsonResponsePacketSerializer::unpackJsonResponse(string strBin)
{
    vector<byte> buffer = vector<byte>();
    byte currByte = '\0';
    unsigned int currInt = 0;
    unsigned int lenSum = 0;

    for (int i = 0; i < strBin.length() - BITS_IN_CHAR; i += BITS_IN_CHAR)
    {
        currByte = static_cast<byte>(bitset<BITS_IN_CHAR>(strBin.substr(i, i + BITS_IN_CHAR)).to_ulong());
        buffer.push_back(currByte);

        cout << "curr is: " << currByte << endl;
        if (i < CODE_PART)
        {
            if (currByte != OK_CODE)
                throw("WRONG CODE ERROR");
        }
        else if (i < LEN_PART)
        {
            lenSum += static_cast<unsigned int>(bitset<BITS_IN_CHAR>(strBin.substr(i, i + BITS_IN_CHAR)).to_ulong());
        }
        else
        {
            //?
        }
    }
}