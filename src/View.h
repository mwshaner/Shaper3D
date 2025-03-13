#pragma once
#include "UI.h"
#include "Controller.h"

namespace 
{
	void login()
	{
		static char username[128] = "";
		static char password[128] = "";

		ImGui::Begin("Login");

		ImGui::InputText("Username", username, IM_ARRAYSIZE(username));

		// Input field for the password with hidden text
		ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

		if (ImGui::Button("Login"))
		{

		}
		if (ImGui::Button("Create Account"))
		{

		}

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
	LoginView(GLFWwindow* window, ImGuiIO& io);
	void render();

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
};

class MeshView : public IView
{
public:
	MeshView(GLFWwindow* window, ImGuiIO& io);
	void render();

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
};