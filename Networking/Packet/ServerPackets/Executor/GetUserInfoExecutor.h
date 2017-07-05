#pragma once

// Own includes
#include <Network/Packet/Packet.h>
#include <Network/Packet/ServerPackets/GetUserInfo.h>
#include <Network/Session/ServerSession/ServerSession.h>

// std includes
#include <string>


using namespace std;

class  GetUserInfoExecutor : public GetUserInfo
{
public:
    virtual std::unique_ptr<Packet> Exec() override;
    virtual void                    SetSessionObject(std::shared_ptr<Session>) override;

private:
    std::shared_ptr<ServerSession> sessionObject;
};
