#pragma once

// Own includes
#include <Network/Packet/Packet.h>

// std includes
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

// Qt includes

using namespace std;

class PacketFactory
{	
public:
	PacketFactory() {}
	virtual ~PacketFactory() {}

    unique_ptr<Packet>      CreatePacket( string& packetName);
protected:
    void                    AddGenerator( const string& key, std::function<Packet*()> generator);
    void                    RemoveGenerator( const string& key);

    std::unordered_map< string, std::function<Packet*()> >   generators;
};
