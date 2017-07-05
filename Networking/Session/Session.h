#pragma once

// std includes
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/detail/endian.hpp>

// Qt incldues
#include <QObject>

using boost::asio::ip::tcp;

using boostError = boost::system::error_code;
using boostIoService = boost::asio::io_service;

class Session   : public QObject,
        public std::enable_shared_from_this<Session>
{
    Q_OBJECT
public:
    Session( boostIoService& io_service );
    virtual ~Session();
    void         Start();

    tcp::socket& GetSocket()   { return socket; }
protected:

    void            ReadHeader();
    void            HandleReadHeader( const boostError& error );
    virtual void    HandleReadContent( const boostError& error ) = 0;
    void            HandleWrite( const boostError& error );

    tcp::socket                 socket;
    std::vector<unsigned char>  data;
};

