#pragma once

#include <exception>
#include <string>
#include <Utils/Definitions.h>

using namespace std;
class Exception: public exception
{
	string			errDescription;
    ErrorType	    errCode;
public:
	Exception(ErrorType err, const string& description) : exception(), errCode(err), errDescription(description) {}
	virtual const char* what() const throw() override
	{
	    return errDescription.c_str();
	}

	ErrorType GetErrCode()	{ return errCode; }
};
