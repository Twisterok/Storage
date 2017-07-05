#pragma once

// std includes
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <iostream>
#include <boost/detail/endian.hpp>

// Own includes
//#include <context/CBServerContext.h>
#include <Utils/json.hpp>
#include <Utils/Exception.h>
#include <Utils/Definitions.h>
#include <Network/Session/Session.h>
#include <Database/MySQL/command.h>

// Qt incldues
#include <QObject>

using boost::asio::ip::tcp;

class ServerSession   : public Session
{
    Q_OBJECT
public:
    ServerSession( boostIoService& io_service);
    ~ServerSession();

    std::shared_ptr<command>    GetDB()   {return dbCon;}
    void                        SetDB( command* dbCon );
protected:

    void HandleReadContent(const boostError& error) override;
    std::shared_ptr<command>    dbCon;

signals:
    void    NewMessage(std::string);
};

