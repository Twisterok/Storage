#include <Network/Session/ServerSession/ServerSession.h>
#include <Network/Packet/PacketProcessor.h>
#include <Context/CBServerContext.h>

using boost::asio::ip::tcp;

ServerSession::ServerSession( boostIoService &io_service) :
        Session(io_service)
{
}
ServerSession::~ServerSession()
{
}

void ServerSession::HandleReadContent(const boostError& error)
{
    try
    {
        if (!error)
        {
            /*  Receiving packet body   */
            auto receivedPacket = PacketProcessor::DecodePacket(CBServerContext::Singleton()->GetPacketFactory(),data);
            emit NewMessage("Received packet ["+receivedPacket->GetTag()+"]");

            /*  Process packet  */
            emit NewMessage("Processing packet ["+receivedPacket->GetTag()+"]");
            receivedPacket->SetSessionObject(shared_from_this());
            auto responsePacket = receivedPacket->Exec();


            if ( responsePacket )
            {
                /*  Serialize packet    */
                PacketProcessor::FillMessage(responsePacket,data);

                emit NewMessage("Sending response packet ["+responsePacket->GetTag()+"]");
                boost::asio::async_write(socket,
                    boost::asio::buffer(data),
                    boost::bind(&ServerSession::HandleWrite, shared_from_this(),
                      boost::asio::placeholders::error));
            }
            else
            {
                ReadHeader();
            }
        }
    }
    catch(...)  { /* Connection will be closed    */}
}

void ServerSession::SetDB(command* _dbCon)
{
    dbCon.reset(_dbCon);
}
