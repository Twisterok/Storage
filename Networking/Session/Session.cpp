#include <Network/Session/Session.h>
#include <Network/Packet/PacketProcessor.h>

using boost::asio::ip::tcp;

Session::Session( boostIoService& io_service)
    : socket(io_service)
{
}
 
Session::~Session()
{
}

void Session::Start()
{
    ReadHeader();
}

void Session::HandleReadHeader( const boostError& error )
{
    try
    {
        if (!error)
        {
            short   cmdLen = PacketProcessor::DecodeHeader(data);

            data.clear();
            data.resize(cmdLen);

            boost::asio::async_read(socket,
                boost::asio::buffer(data),
                boost::bind(&Session::HandleReadContent, shared_from_this(),
                boost::asio::placeholders::error));
        }
    }
    catch(...)  { /* Connection will be closed    */}
}

void Session::HandleWrite(const boostError& error)
{
    if (!error)
        ReadHeader();
}

void Session::ReadHeader()
{
    data.clear();
    data.resize(2);
    boost::asio::async_read(socket,
        boost::asio::buffer(data),
        boost::bind(
          &Session::HandleReadHeader, shared_from_this(),
          boost::asio::placeholders::error));
}
