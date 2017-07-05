#pragma once

// Own includes
#include <Network/Packet/Packet.h>

// std includes
#include <string>


using namespace std;

class  GetUserInfo : public Packet
{    
public:
    void                    SetMacAdress( const std::string& _macAdress );
    std::string			    GetTag()	override;
    void				    Pack( std::string& data )	override;
    void				    Unpack( json& jsonObj ) override;
protected:
    std::string macAdress;
};
