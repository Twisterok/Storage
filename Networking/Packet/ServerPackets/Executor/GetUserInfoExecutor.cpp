// Own includes
#include <stdint.h>
#include <Network/Packet/Packet.h>
#include <Network/Packet/ServerPackets/Executor/GetUserInfoExecutor.h>
#include <Network/Packet/ClientPackets/ErrorHappend.h>
#include <Network/Packet/ClientPackets/GetUserInfoResponse.h>
#include <Objects/User.h>
#include <Utils/Exception.h>
#include <Utils/Definitions.h>
#include <Database/DAO/UserDAO.h>
#include <Database/DAO/UidDAO.h>
#include <Database/MySQL/command.h>

std::unique_ptr<Packet> GetUserInfoExecutor::Exec()
{    
    std::unique_ptr<Packet> respPacket;
    string                  description;
    exception_ptr           expr;
    try
    {
        if ( !sessionObject )
            throw Exception( ErrorType::SessionObjectNotFound, "Session object not found" );

        std::shared_ptr<command> dbCon = sessionObject->GetDB();

        if ( !UidDAO::MacAdressExists( dbCon, macAdress ) )
            UidDAO::AddUid( dbCon, macAdress );

        string uid = UidDAO::GetUid( dbCon,macAdress);
        if ( uid.empty() )
            throw Exception(ErrorType::UidIsEmpty, "Empty uid" );

        User usr(uid);
        if ( !UserDAO::UserExists(dbCon, uid) )
            UserDAO::AddUser( dbCon, usr );
        else
            UserDAO::GetUser( dbCon, usr );

        unique_ptr<GetUserInfoResponse> response( new GetUserInfoResponse() );
        response->SetUid( usr.uid );
        response->SetNickname( usr.nickname );
        response->SetWins( usr.wins );
        response->SetLoses( usr.loses );
        respPacket = std::move(response);
    }
    catch(Exception& ex)
    {        
        unique_ptr<ErrorHappend> errorPacket(new ErrorHappend );
        errorPacket->SetErrorCode( ex.GetErrCode() );
        errorPacket->SetDescription("["+GetTag()+"] error: "+string( ex.what()));
        respPacket = std::move(errorPacket);
    }
    catch (...)
    {
        /*  get exception pointer   */
        expr = current_exception();
        
        /*  rethrow */
        try                             
        {
            std::rethrow_exception(expr);   
        }
        catch(const std::exception& e) 
        {
            description = "["+GetTag()+"] error: " + std::string(e.what());
        }

        unique_ptr<ErrorHappend> errorPacket(new ErrorHappend);
        errorPacket->SetErrorCode( ErrorType::BadResponse );
        errorPacket->SetDescription(description);
        respPacket = std::move(errorPacket);
    }
    return std::move(respPacket);
}

void GetUserInfoExecutor::SetSessionObject(std::shared_ptr<Session> sessionObj )
{
    sessionObject = dynamic_pointer_cast<ServerSession>(sessionObj);
}
