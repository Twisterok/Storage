#include "UidDAO.h"
#include <iomanip>
#include <sstream>

bool UidDAO::UidExists(shared_ptr<command> dbCon, const string& uid)
{
	string sql = "select uid from " + Constants::kUidsTable + " where uid = ?";

	std::vector<db_variant> params;
	std::vector<db_variant> row;
	params.push_back(uid);
	dbCon->exec(sql, params);
	if (dbCon->fetch(row))  return true;
	return false;
}

bool UidDAO::MacAdressExists(shared_ptr<command> dbCon, const string& macAdress)
{
	string sql = "select uid from " + Constants::kUidsTable + " where macadress = ?";

	std::vector<db_variant> params;
	std::vector<db_variant> row;
	params.push_back(macAdress);
	dbCon->exec(sql, params);
	if (dbCon->fetch(row))  return true;
	return false;
}

std::string UidDAO::GetUid(shared_ptr<command> dbCon, const string& macAdress)
{
	string uid;
	string sql = "select uid from " + Constants::kUidsTable + " where macadress = ?";

	std::vector<db_variant> params;
	std::vector<db_variant> row;
	params.push_back(macAdress);
	dbCon->exec(sql, params);
	if (!dbCon->fetch(row))
		return uid;
		
	uid = boost::get<string>(row[0]);
	return uid;
}

int64_t UidDAO::AddUid(shared_ptr<command> dbCon, const string& macAdress)
{
	if (MacAdressExists(dbCon, macAdress))
		throw Exception(ErrorType::MacAdressExists, "mac [" + macAdress + "] already exists");

    string sqlInsert = "insert into " + Constants::kUidsTable + " (macadress) values(?);";
	std::vector<db_variant> params;
    std::vector<db_variant> row;

	params.push_back(macAdress);
	dbCon->exec(sqlInsert, params);

    /*  Last Insert ID return unsigned long long    */
    dbCon->exec("SELECT LAST_INSERT_ID();");
    if (!dbCon->fetch(row))
        throw Exception(ErrorType::MySQLError,"Uid wasn't added");

    int64_t id = boost::get<int64_t>(row[0]);

    std::stringstream ss;
    ss << std::hex << std::setw(6) << std::setfill('0') << id;

    string sqlUpdate = "update " + Constants::kUidsTable + " set uid = ? where id = ?;";
    params.clear();
    params.push_back( ss.str() );
    params.push_back(id);
	dbCon->exec(sqlUpdate, params);
    return id;
}
