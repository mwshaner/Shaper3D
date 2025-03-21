#pragma once
#include "View.h"
#include "DB.h"
#include <iostream>

/*
*		   File: Controller.h
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description:
*		   The controller classes define the different types of controllers used in conjuction
*          with the model and view classes. Currently only a CRUD controller is implemented.
*/

namespace
{
	typedef std::tuple<std::string, std::string, std::string> userRecord;
}

class CRUDController 
{
public:
	CRUDController(LoginView& view, sqlModel& model);
	bool create();
	bool read();
	bool update();
	bool deleteUser(); // delete is a keyword
	void closeConnection();

private:
	LoginView m_view;
	sqlModel m_model;
};