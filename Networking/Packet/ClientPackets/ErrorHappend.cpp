// Own includes
#include <network/packet/clientpackets/ErrorHappend.h>
#include <utils/definitions.h>
#include <utils/Exception.h>
#include <utils/Definitions.h>

using json = nlohmann::json;
std::string	ErrorHappend::GetTag()
{
    return "ErrorHappend";
}
void ErrorHappend::Pack(std::string& data)
{
    json            jsonObj;

    jsonObj[ Constants::kPacketNameKey ] = GetTag();
    jsonObj[ Constants::kParamsKey ]["errorCode"] = (int) errorCode;
    jsonObj[ Constants::kParamsKey ]["description"] = description;

    data = jsonObj.dump();
}
void ErrorHappend::Unpack( json& jsonObj )
{
    if ( jsonObj.is_null() )
        return;

    errorCode = (ErrorType) jsonObj.value( "errorCode", 0 );
    description = jsonObj.value( "description", "" );
}

void ErrorHappend::SetErrorCode( ErrorType errCode )
{
    errorCode = errCode;
}

void ErrorHappend::SetDescription( const string& _description )
{
    description = _description;
}

std::unique_ptr<Packet> ErrorHappend::Exec()
{
    throw Exception( errorCode, description );
}
