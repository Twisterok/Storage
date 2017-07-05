#include <Network/Packet/Factory/ServerPacketFactory.h>
#include <Network/Packet/ServerPackets/Executor/GetUserInfoExecutor.h>
//----------------------------------------------------------
ServerPacketFactory::ServerPacketFactory()
{
    /*  add some packets here   */
    AddGenerator( "GetUserInfo", []() { return new GetUserInfoExecutor(); } );
}
