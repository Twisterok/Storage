#pragma once

// Own includes
#include <Network/Packet/Packet.h>
#include <Objects/User.h>

// std includes
#include <string>
#include <stdint.h>


using namespace std;

class  GetUserInfoResponse : public Packet
{
public:
    GetUserInfoResponse()
    {}

    /*  setters */
    void                    SetUid( const string& uid )             { user.uid = uid; }
    void                    SetNickname( const string& nickname )   { user.nickname = nickname; }
    void                    SetWins(int winsCount )                 { user.wins = winsCount; }
    void                    SetLoses(int losesCount )               { user.loses = losesCount; }
    
    /*  getters */
    const User&             GetUser()                               { return user; }

    std::string			    GetTag()	override;
    void				    Pack( std::string& data ) override;
    void				    Unpack( json& objectTree ) override;

protected:
    User user;
};

