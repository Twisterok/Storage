#pragma once

// Own includes
#include <Network/Packet/Packet.h>

// std includes
#include <string>


using namespace std;

class  ErrorHappend : public Packet
{

public:
    void                    SetErrorCode( ErrorType errCode );
    void                    SetDescription( const string& description);
    std::string			    GetTag()	override;
    void				    Pack(std::string& data)	override;
    void				    Unpack( json& jsonObj ) override;
    std::unique_ptr<Packet> Exec() override;
protected:
    ErrorType               errorCode;
    string                  description;
};

