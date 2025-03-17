#pragma once
#include "UI.h"
#include <iostream>
//#include "Controller.h"

namespace 
{

	typedef std::tuple<std::string, std::string, std::string> userRecord;
	

	bool login()
	{
		static std::string username(128, '\0');
		static std::string password(128, '\0');
		static std::string storedUsername;
		static std::string storedPassword;
		std::string pass = "12345";

		ImGui::Begin("Login");

		ImGui::InputText("Username", &username[0], username.size());

		ImGui::InputText("Password", &password[0], password.size(), ImGuiInputTextFlags_Password);

		if (ImGui::Button("Login"))
		{
			storedUsername = username;
			storedPassword = password;

			storedPassword = storedPassword.c_str();

			if (storedPassword == pass)
			{
				//std::cout << "SUCESS\n";
				ImGui::End();
				return true;
			}
		}

		if (ImGui::Button("Create Account"))
		{
			storedUsername = username;
			storedPassword = password;
		}

		ImGui::End();
		return false;
	}

	void meshProperties()
	{
		ImGui::ShowDemoWindow();
	}
}

//class IView
//{
//public:
//	IView() = default;
//	virtual ~IView() = default;
//	virtual void render();
//};

class LoginView 
{
public:
	LoginView(GLFWwindow* window, UI backend);
	void render();
	void loginWindow();
	bool getLoginStatus() { return m_loginStatus; }

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
	bool m_loginStatus;
};

class MeshView
{
public:
	MeshView(GLFWwindow* window, UI backend);
	void render();

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
};