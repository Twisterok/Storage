#pragma once

// Own includes
#include <database/mysql/command.h>
#include <objects/User.h>

// std includes
#include <memory>
#include <string>

using namespace std;

class UserDAO
{    
public:
    static bool UserExists( shared_ptr<command> dbCon, const string& uid );
    static void GetUser( shared_ptr<command> dbCon, User& user);
    static void AddUser( shared_ptr<command> dbCon, User& user, bool replace = false );
    static void UpdateUser( shared_ptr<command> dbCon, const User& user);
    static void DeleteUser( shared_ptr<command> dbCon, const User& user);
};
