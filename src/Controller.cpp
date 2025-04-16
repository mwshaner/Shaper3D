#include "Controller.h"

/*
*		   File: Controller.cpp
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description:
*		   This file contains the implementation of the different types of controllers. 
*          Currently only a CRUD controller is implemented.
*/


/*
-------------------------------------------------------------------------------------------------------
					   CRUDController
-------------------------------------------------------------------------------------------------------
*/

CRUDController::CRUDController(sqlModel& model)
	: m_model{ model }
{
	m_model.connect();

	// loads dummy data to an in memory sqlite3 db
	m_model.initialize_database();

	/*std::vector<userRecord> records;
	std::string sql = "SELECT * FROM USERS";

	bool result = m_model.runQuery(sql, records);

	
	for (auto record : records)
	{
		std::cout << "User: " << std::get<1>(record) << " ID = " << std::get<0>(record) << " PASSWORD = " << std::get<2>(record) << " " << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;*/
}


bool CRUDController::create(const std::string& pass, const std::string& name)
{
	std::vector<userRecord> records;
	std::string preparedQuery = "INSERT INTO USERS(USERNAME, PASSWORD)" \
        "VALUES(?, ?); ";

	sqlite3_stmt* sqlStatement;

	/*
		Create the prepared statement using the prepared query
	*/
	sqlite3_prepare_v2(
		m_model.m_db,
		preparedQuery.c_str(),
		(int)preparedQuery.length(),
		&sqlStatement,
		nullptr
	);

	/*
	   Bind the user input text into the prepared query.The user input may or may not contain an SQL injection
	   but it will fail either way because the user input is treated as a text variable and is not part of the SQL statement
	*/
	sqlite3_bind_text(
		sqlStatement,
		1,
		name.c_str(),
		(int)preparedQuery.length(),
		SQLITE_STATIC
	);

	sqlite3_bind_text(
		sqlStatement,
		2,
		pass.c_str(),
		(int)preparedQuery.length(),
		SQLITE_STATIC
	);

	// the final query value
	std::string query = sqlite3_expanded_sql(sqlStatement);

	// A sucessful query means no DB errors, which means the user record was created
	bool result = m_model.runQuery(query, records);

	// Destroy statement
	sqlite3_finalize(sqlStatement);

	return result;
}


bool CRUDController::read(const std::string& pass, const std::string& name)
{
	std::vector<userRecord> records;
	std::string preparedQuery = "SELECT * FROM USERS WHERE USERNAME = ? AND PASSWORD = ?";

	sqlite3_stmt* sqlStatement;

	/*
         Create the prepared statement using the prepared query         
     */
    sqlite3_prepare_v2(
        m_model.m_db,
        preparedQuery.c_str(),
        (int)preparedQuery.length(),
        &sqlStatement,
        nullptr
    );

    /*
       Bind the user input text into the prepared query.The user input may or may not contain an SQL injection
       but it will fail either way because the user input is treated as a text variable and is not part of the SQL statement
    */         
    sqlite3_bind_text(
        sqlStatement,
        1,
        name.c_str(),
        (int)preparedQuery.length(),
        SQLITE_STATIC
    );

	sqlite3_bind_text(
		sqlStatement,
		2,
		pass.c_str(),
		(int)preparedQuery.length(),
		SQLITE_STATIC
	);

	// the final query value
	std::string query = sqlite3_expanded_sql(sqlStatement);

	// A sucessful query means no DB errors, not a sucessful login
	bool result = m_model.runQuery(query, records);

	// Unsuccessful login
	if (records.empty())
	{
		result = false;
	}

	// Destroy statement
	sqlite3_finalize(sqlStatement);

	return result;
}

bool CRUDController::update()
{
	// TODO: create update user query
	return false;
}

bool CRUDController::deleteUser()
{
	// TODO: create delete user query
	return false;
}

void CRUDController::closeConnection()
{
	m_model.disconnect();
}