#pragma once

// own includes
#include <Network/Packet/Packet.h>
#include <Network/Packet/Factory/PacketFactory.h>
#include <Network/Packet/PacketProcessor.h>
#include <Utils/Definitions.h>
#include <Utils/Exception.h>

// std includes
#include <string>
#include <sstream>
#include <memory>

// Qt includes

using namespace std;

namespace PacketProcessor
{

    //-------------------------------------------------------------------
    void                FillMessage( unique_ptr<Packet>& packet, vector<unsigned char>& message );
    short               DecodeHeader( const std::vector<unsigned char>& message );
    unique_ptr<Packet>  DecodePacket( shared_ptr<PacketFactory>& packetFactory,const std::vector<unsigned char>& message );
    //-------------------------------------------------------------------
    template <class ConnectionType>
    void Write( shared_ptr<ConnectionType>& con, unique_ptr<Packet> packet )
    {
        vector<unsigned char> message;
        FillMessage( std::move(packet), message );
        con->write(message);
    }
    //-------------------------------------------------------------------
    template <class ConnectionType>
    unique_ptr<Packet> Read( shared_ptr<ConnectionType>& con, shared_ptr<PacketFactory>& packetFactory )
    {
        string				    response;
        vector<unsigned char>   message;
        unique_ptr<Packet>      result;        

        /*	read length */
        message.resize(2);
        con->read(message);

        short   cmdLen = DecodeHeader(message);

        /*	Read message	*/
        message.resize(cmdLen);
        con->read(message);

        auto packet = DecodePacket(packetFactory,message);
        return std::move(packet);
    }
}

