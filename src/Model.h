#pragma once
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include "sqlite3.h"

/*
*		   File: DB.h
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description: The Model interface and class implements the connection to and communication with
*          a database. Currently, only in-memory sqlite3 databases are implemented, however
*          derived classes can be created to support different database systems as needed.
*/


class IModel
{
public:
	virtual ~IModel() = default;
	virtual int connect() = 0;
	virtual int disconnect() = 0;
};

class sqlModel : public IModel
{
public:
	typedef std::tuple<std::string, std::string, std::string> userRecord;
	sqlModel();
	int connect() override;
	bool initialize_database();
	int disconnect() override;
	static int callback(void* possible_vector, int argc, char** argv, char** azColName);
	bool runQuery(std::string& sql, std::vector<userRecord>& records);

private:
	sqlite3* m_db;
};

