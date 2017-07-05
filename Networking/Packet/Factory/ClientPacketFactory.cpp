#include <network/packet/factory/ClientPacketFactory.h>
#include <network/packet/clientpackets/ErrorHappend.h>
#include <network/packet/clientpackets/GetUserInfoResponse.h>

//----------------------------------------------------------
ClientPacketFactory::ClientPacketFactory()
{
    /*  add some packets here   */
    this->AddGenerator("ErrorHappend",      [](){return new ErrorHappend();});
    this->AddGenerator("GetUserInfoResponse",[](){return new GetUserInfoResponse();});
}
