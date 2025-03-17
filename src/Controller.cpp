#include "Controller.h"


/*
----------------------------------------------------------------
					   LOGIN CONTROLLER
----------------------------------------------------------------
*/

LoginController::LoginController(LoginView& view, DB& model)
	: m_view{ view },
	  m_model{ model }
{
	m_model.connect();
	m_model.initialize_database();

	std::vector<userRecord> records;
	std::string sql = "SELECT * FROM USERS";

	bool result = m_model.run_query(sql, records);


	for (auto record : records)
	{
		std::cout << "User: " << std::get<1>(record) << " ID = " << std::get<0>(record) << " PASSWORD = " << std::get<2>(record) << " " << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool LoginController::query()
{
	std::vector<userRecord> records;
	std::string sql = "SELECT * FROM USERS WHERE USERNAME = 'Mason' AND PASSWORD = '12345'";

	bool result = m_model.run_query(sql, records);

	
	for (auto record : records)
	{
		std::cout << "User: " << std::get<1>(record) << " ID = " << std::get<0>(record) << " PASSWORD = " << std::get<2>(record) << " " << std::endl;
	}

	return result;
}

void LoginController::shutdown()
{
	m_model.closeDB();
}