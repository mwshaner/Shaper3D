#pragma once
#include "UI.h"
#include <iostream>
#include "Controller.h"

namespace 
{
	bool login()
	{
		static std::string username(128, '\0');
		static std::string password(128, '\0');
		static std::string storedUsername;
		static std::string storedPassword;
		std::string pass = "123";

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
				std::cout << "SUCESS\n";
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
		ImGui::Begin("Demo");
		ImGui::ShowDemoWindow();
		ImGui::End();
	}
}

class IView
{
public:
	IView() = default;
	virtual ~IView() = default;
	virtual void render() = 0;
};

class LoginView : IView
{
public:
	LoginView(GLFWwindow* window, UI backend);
	void render() override;
	bool getLoginStatus() { return m_loginStatus; }

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
	bool m_loginStatus;
};

class MeshView : public IView
{
public:
	MeshView(GLFWwindow* window, UI backend);
	void render() override;

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
};