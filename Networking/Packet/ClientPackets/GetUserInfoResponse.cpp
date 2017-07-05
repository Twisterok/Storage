// Own includes
#include <Network/Packet/ClientPackets/GetUserInfoResponse.h>
#include <utils/Definitions.h>
#include <utils/Exception.h>

std::string	GetUserInfoResponse::GetTag()
{
    return "GetUserInfoResponse";
}
void GetUserInfoResponse::Pack( std::string& data)
{
    json            jsonObj;

    jsonObj[ Constants::kPacketNameKey ] = GetTag();
    jsonObj[ Constants::kParamsKey ]["uid"] = user.uid;
    jsonObj[ Constants::kParamsKey ]["nickname"] = user.nickname;
    jsonObj[ Constants::kParamsKey ]["wins"] = user.wins;
    jsonObj[ Constants::kParamsKey ]["loses"] = user.loses;

    data = jsonObj.dump();
}
void GetUserInfoResponse::Unpack( json& jsonObj )
{
    if ( jsonObj.is_null() )
        return;

    user.uid        = jsonObj.value( "uid","" );
    user.nickname   = jsonObj.value( "nickname","" );
    user.wins       = jsonObj.value( "wins",0 );
    user.loses      = jsonObj.value( "loses",0 );
}
