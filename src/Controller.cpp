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

CRUDController::CRUDController(LoginView& view, sqlModel& model)
	: m_view{ view },
	  m_model{ model }
{
	m_model.connect();

	// loads dummy data to an in memory sqlite3 db
	m_model.initialize_database();

	std::vector<userRecord> records;
	std::string sql = "SELECT * FROM USERS";

	bool result = m_model.runQuery(sql, records);

	
	for (auto record : records)
	{
		std::cout << "User: " << std::get<1>(record) << " ID = " << std::get<0>(record) << " PASSWORD = " << std::get<2>(record) << " " << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}


bool CRUDController::create()
{
	// TODO: implement create user query
	return false;
}


bool CRUDController::read()
{
	//TODO: implement login query

	std::vector<userRecord> records;
	std::string sql = "SELECT * FROM USERS WHERE USERNAME = 'Mason' AND PASSWORD = '12345'";

	bool result = m_model.runQuery(sql, records);

	
	for (auto record : records)
	{
		std::cout << "User: " << std::get<1>(record) << " ID = " << std::get<0>(record) << " PASSWORD = " << std::get<2>(record) << " " << std::endl;
	}

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