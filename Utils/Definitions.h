#pragma once

#include <string>
#include <stdint.h>

#define STRINGIFY(str)			#str

using namespace std;

enum class ErrorType
{
	OK,
    ExternalError,
    //  MySQL ErrorType
    MySQLError,
    UserExists,
    UserDoesntExist,
	UidExists,
    UidIsEmpty,
	MacAdressExists,

    // User Input ErrorType
    PaswordsNotMatch,

    // Other ErrorType
    InternalError,
    LoadDllError,
    UnloadDllError,
    NetworkError,
    InvalidParameter,
    EmptyData,
    BadResponse,
    ActionNotAllowed,
    ConnectionLost,
    SettingsNotFound,
	SessionObjectNotFound
};

enum class EndianType : uint32_t {
    LittleEndian   = 0x00000001,
    BigEndian      = 0x01000000,
    Unknown        = 0xFFFFFFFF
};

enum class ELoggingType
{
    Off,
	On,
	Advanced,
	Full
};

enum class EUserStatus
{
    Offline,
    Online
};

namespace Constants
{
    static const int            BYTE_BITS_COUNT = 8;
    static const int            MAX_THREADS     = 150;
    static const std::string    kUsersTable = "users";
	static const std::string    kUidsTable = "uids";
    static const std::string    kPacketNameKey = "PacketName";
    static const std::string    kParamsKey = "Params";
}

struct ODBCParameters
{
    string	host;
    int   	port;
    string 	database;
    string 	uid;
    string 	pwd;

    void operator=(const ODBCParameters& param)
    {
        this->host        	= param.host;
        this->port        	= param.port;
        this->database    	= param.database;
        this->uid         	= param.uid;
        this->pwd         	= param.pwd;
    }

    bool CheckParams()  {return !pwd.empty()&&
                                !host.empty()  &&
                                port > 0    &&
                                !uid.empty()    &&
                                !database.empty();}
};

struct ServerParams
{
    std::string	host;
    int         port;   

    void operator=(const ODBCParameters& param)
    {
        this->host        = param.host;
        this->port        = param.port;
    }

    bool CheckParams()  {return !host.empty()  && port > 0;  }
};

