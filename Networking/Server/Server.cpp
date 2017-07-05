#include <network/server/Server.h>
#include <Context/CBServerContext.h>
#include <Database/MySQL/command.h>

Server::Server(boost::asio::io_service& service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
      io_service(service)
{
        do_accept();
}

void    Server::do_accept()
{
    std::shared_ptr<ServerSession> newSession(new ServerSession(io_service));
    acceptor_.async_accept(newSession->GetSocket(),
        boost::bind(&Server::handle_accept, this, newSession,
          boost::asio::placeholders::error));
}

void Server::handle_accept(std::shared_ptr<ServerSession> session,
      const boost::system::error_code& error)
{
    if (!error)
    {
        auto pContext = CBServerContext::Singleton();
        std::unique_ptr<command>    dbCon;
        try
        {
            dbCon.reset(new command(pContext->GetDBParams().host,
                                    pContext->GetDBParams().port,
                                    pContext->GetDBParams().database,
                                    pContext->GetDBParams().uid,
                                    pContext->GetDBParams().pwd));
            session->SetDB( dbCon.release() );
            emit NewMessage("New connection");
            QObject::connect(session.get(),SIGNAL(NewMessage(std::string)),
                             this, SLOT(slotNewThreadMessage(std::string)));
            session->Start();
        }
        catch (...)   { return;}
    }

    do_accept();
}


void    Server::slotNewThreadMessage(std::string msg)
{
    emit NewMessage(msg);
}
