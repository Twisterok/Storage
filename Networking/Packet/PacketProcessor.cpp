// Own includes
#include <network/packet/PacketProcessor.h>
#include <Utils/Definitions.h>
#include <Utils/Exception.h>

// std includes
#include <string>
#include <sstream>
#include <Utils/json.hpp>
#include <Utils/Utils.h>
// Qt includes

using json = nlohmann::json;
namespace PacketProcessor
{
    void FillMessage( unique_ptr<Packet>& packet, vector<unsigned char>& message)
    {
        message.clear();
        std::string zipPacket;
        packet->Pack(zipPacket);

        short   cmdLen = static_cast<short>( zipPacket.size() );

        if ( utils::GetEndianOrder() == EndianType::LittleEndian )
        {
            message.push_back((reinterpret_cast<unsigned char*>(&cmdLen))[1]);
            message.push_back((reinterpret_cast<unsigned char*>(&cmdLen))[0]);
        }
        else if ( utils::GetEndianOrder() == EndianType::BigEndian )
        {
            message.push_back((reinterpret_cast<unsigned char*>(&cmdLen))[0]);
            message.push_back((reinterpret_cast<unsigned char*>(&cmdLen))[1]);
        }
        else
            throw Exception( ErrorType::InternalError,"Unknown byte order");

        message.insert(message.end(),zipPacket.begin(),zipPacket.end());
    }

    short DecodeHeader(const std::vector<unsigned char>& message)
    {
        short   cmdLen = 0;

        if ( utils::GetEndianOrder() == EndianType::LittleEndian )
        {
            reinterpret_cast<unsigned char*>(&cmdLen)[0] = message[1];
            reinterpret_cast<unsigned char*>(&cmdLen)[1] = message[0];
        }
        else if ( utils::GetEndianOrder() == EndianType::BigEndian )
        {
            reinterpret_cast<unsigned char*>(&cmdLen)[0] = message[0];
            reinterpret_cast<unsigned char*>(&cmdLen)[1] = message[1];
        }
        else
            throw Exception( ErrorType::InternalError,"Unknown byte order");

        return cmdLen;
    }


    unique_ptr<Packet> DecodePacket(shared_ptr<PacketFactory>& packetFactory,const std::vector<unsigned char>& message)
    {
        string				    response;
        response.assign(message.begin(),message.end());

        json responseJson = json::parse( response );
        string packetName = responseJson.value(Constants::kPacketNameKey,"");
        auto receivedPacket = packetFactory->CreatePacket( packetName );
        receivedPacket->Unpack(responseJson[Constants::kParamsKey]);

        return std::move(receivedPacket);
    }
}
