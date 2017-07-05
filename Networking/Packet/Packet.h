#pragma once

//#include <Network/Session/Session.h>

// std includes
#include <string>
#include <sstream>
#include <Utils/json.hpp>
#include "Utils/Definitions.h"

// qt includes

using json = nlohmann::json;
class Session;
class Packet
{
public:
	virtual ~Packet() {}
    virtual std::string			GetTag() = 0;
    virtual void				Pack( std::string& data ) = 0;
    virtual void				Unpack( json& jsonObj ) = 0;
    virtual unique_ptr<Packet>  Exec() { return nullptr; }
    virtual void                SetSessionObject(std::shared_ptr<Session>) {}
protected:
    virtual void                VerifyArgs() {}

};

