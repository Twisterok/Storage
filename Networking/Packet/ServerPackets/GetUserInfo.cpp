// Own includes
#include <stdint.h>
#include <Network/Packet/ServerPackets/GetUserInfo.h>

#include <Utils/Exception.h>
#include <Utils/Definitions.h>
#include <Utils/json.hpp>

using json = nlohmann::json;
std::string	GetUserInfo::GetTag()
{
    return "GetUserInfo";
}
void GetUserInfo::Pack(std::string& data)
{
    json            jsonObj;

    jsonObj[ Constants::kPacketNameKey ] = GetTag();
    jsonObj[ Constants::kParamsKey ]["macAdress"] = macAdress;

    data = jsonObj.dump();
}
void GetUserInfo::Unpack( json& jsonObj )
{
    if ( jsonObj.is_null() )
        return;

    macAdress = jsonObj.value("macAdress","");
}

void GetUserInfo::SetMacAdress( const std::string& _macAdress )
{
    macAdress = _macAdress;
}
