#pragma once
#include "View.h"
#include "DB.h"
#include <iostream>


namespace
{
	typedef std::tuple<std::string, std::string, std::string> userRecord;
}

class LoginController 
{
public:
	LoginController(LoginView& view, DB& model);
	bool query();
	void shutdown();

private:
	LoginView m_view;
	DB m_model;
};