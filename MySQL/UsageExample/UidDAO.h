#pragma once

// Own includes
#include <database/mysql/command.h>
#include <objects/User.h>

// std includes
#include <memory>
#include <string>

using namespace std;

class UidDAO
{
public:
	static bool			UidExists(shared_ptr<command> dbCon, const string& uid);
	static bool			MacAdressExists(shared_ptr<command> dbCon, const string& macAdress );
	static std::string	GetUid(shared_ptr<command> dbCon, const string& macAdress);
    static int64_t		AddUid(shared_ptr<command> dbCon, const string& macAdress);
};
