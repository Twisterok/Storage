// Own includes
#include <Network/Packet/Factory/PacketFactory.h>

// std includes
#include <stdexcept>
#include <algorithm>


std::unique_ptr<Packet> PacketFactory::CreatePacket( string& name)
{
	std::unique_ptr<Packet> result;
    auto it = generators.find(name);
    if (it == generators.end())	throw std::runtime_error("Packet [ "+name+" ] isn't supported");

	auto MakeNewPacket = it->second;
	result.reset(MakeNewPacket());
	return std::move(result);
}
//----------------------------------------------------------
void	PacketFactory::AddGenerator( const string& key, std::function<Packet*()> generator)
{
    auto insertResult = generators.insert(std::make_pair( key , generator));
    if (!insertResult.second)	throw runtime_error("Generator tag ["+ key +"] already exists. Adding is unavailable");
}
//----------------------------------------------------------
void	PacketFactory::RemoveGenerator( const string& key)
{
    auto it = generators.find( key );
    if (it == generators.end())	return;

    generators.erase(it);
}
