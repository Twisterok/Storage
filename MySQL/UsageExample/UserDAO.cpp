#include <Database/DAO/UserDAO.h>
#include <Utils/Definitions.h>
#include <Objects/User.h>
#include <Utils/Exception.h>

bool UserDAO::UserExists(shared_ptr<command> dbCon, const string& uid)
{
    string sql = "select id from "+ Constants::kUsersTable +" where uid = ?";

    std::vector<db_variant> params;
    std::vector<db_variant> row;
    params.push_back(uid);
    dbCon->exec(sql,params);
    if (dbCon->fetch(row))  return true;
    return false;
}

void UserDAO::GetUser(shared_ptr<command> dbCon,User& user)
{
    string sql = "select id, uid,nickname,wins,loses from "+Constants::kUsersTable+" where ";
    sql += user.id > 0 ? " id = ?" : " uid = ?";

    std::vector<db_variant> params;
    std::vector<db_variant> row;
    if (user.id > 0)    params.push_back(user.id);
    else                params.push_back(user.uid);

    dbCon->exec(sql,params);
    if (!dbCon->fetch(row))  throw Exception( ErrorType::UserDoesntExist,"User ["+user.uid+"] doesnt exist");

    user.id       = boost::get<int>(row[0]);
    user.uid      = boost::get<string>(row[1]);
    user.nickname = boost::get<string>(row[2]);
    user.wins     = boost::get<int>(row[3]);
    user.loses    = boost::get<int>(row[4]);
}

void UserDAO::AddUser(shared_ptr<command> dbCon,User& user, bool replace)
{
    if (UserExists(dbCon,user.uid)) throw Exception(ErrorType::UserExists,"User ["+user.uid+"] already exists");
	string sqlInsert = replace ? "replace" : "insert";
	sqlInsert += " into "+Constants::kUsersTable+" (uid, nickname, wins, loses )"
                 "values(?,?,?,?);";
    std::vector<db_variant> params;
    std::vector<db_variant> row;
    params.push_back(user.uid);
    params.push_back(user.nickname);
    params.push_back(user.wins);
    params.push_back(user.loses);
    dbCon->exec(sqlInsert,params);

    /*  Last Insert ID return unsigned long long    */
    dbCon->exec("SELECT LAST_INSERT_ID();");
    if (!dbCon->fetch(row)) throw Exception(ErrorType::MySQLError,"User wasn't added");

    user.id = boost::get<int64_t>(row[0]);
}

void UserDAO::UpdateUser(shared_ptr<command> dbCon,const User& user)
{
    if (!UserExists(dbCon,user.uid)) throw Exception(ErrorType::UserDoesntExist,"User ["+user.uid+"] doesn't exist");
    string sqlInsert = "update "+Constants::kUsersTable+" set "
                       " uid = ?, "
                       " nickname = ?, "
                       " wins = ?, "
                       " loses = ? "
                       " where id = ?";
    std::vector<db_variant> params;
    params.push_back(user.uid);
    params.push_back(user.nickname);
    params.push_back(user.wins);
    params.push_back(user.loses);
    params.push_back(user.id);
    dbCon->exec(sqlInsert,params);
}

void UserDAO::DeleteUser(shared_ptr<command> dbCon, const User& user)
{
	std::vector<db_variant> params;
	string sqlDelete = "delete from " + Constants::kUsersTable + " where ";

	if (user.id > 0)
	{
		sqlDelete += " id = ?";
		params.push_back(user.id);
	}
	else
	{	
		sqlDelete += " uid = ?";
		params.push_back(user.uid);
	}

	dbCon->exec(sqlDelete, params);
}
