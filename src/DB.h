#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include "sqlite3.h"

class DB
{
public:
	DB();
	int connect();
	bool initialize_database();
	int closeDB();
	static int callback(void* possible_vector, int argc, char** argv, char** azColName);
	typedef std::tuple<std::string, std::string, std::string> userRecord;
	bool run_query(std::string& sql, std::vector< userRecord >& records);

private:
	sqlite3* m_db;
};

