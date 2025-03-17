#pragma once
#include <iostream>
#include "Object.h"
#include "UI.h"
//#include "Controller.h"

namespace 
{
	
	typedef std::tuple<std::string, std::string, std::string> userRecord;
	
	bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
		float avail = ImGui::GetContentRegionAvail().x;

		float off = (avail - size) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

		return ImGui::Button(label);
	}


	bool login()
	{
		static std::string username(128, '\0');
		static std::string password(128, '\0');
		static std::string storedUsername;
		static std::string storedPassword;
		std::string pass = "1";


		ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoTitleBar);
		

		ImGui::Dummy(ImVec2(0, 400));


		// Choose the widget width (adjust as needed)
		float widgetWidth = 800.0f;
		float posX = (ImGui::GetWindowContentRegionWidth() - widgetWidth) * 0.5f;


		// Center and draw the label
		ImGui::SetCursorPosX(posX);
		ImGui::Text("Username");
		ImGui::Dummy(ImVec2(0, 5));
		ImGui::SetCursorPosX(posX);
		ImGui::PushItemWidth(widgetWidth);
		ImGui::InputText("##Username", &username[0], username.size());
		ImGui::PopItemWidth();

		ImGui::Dummy(ImVec2(0, 25));

		ImGui::SetCursorPosX(posX);
		ImGui::Text("Password");
		ImGui::Dummy(ImVec2(0, 5));
		ImGui::SetCursorPosX(posX);
		ImGui::PushItemWidth(widgetWidth);
		ImGui::InputText("##Password", &password[0], password.size(), ImGuiInputTextFlags_Password);
		
		
		
		ImGui::NewLine();
		ImGui::NewLine();

		if (ButtonCenteredOnLine("Login"))
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

		if (ButtonCenteredOnLine("Create Account"))
		{
			storedUsername = username;
			storedPassword = password;
		}

		ImGui::End();
		return false;
	}

	void meshProperties(std::vector<Object>& meshes)
	{
		ImGui::Begin("Mesh Properties");

		// Arrow buttons with Repeater
		static int counter = 0;
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left) && counter > 0) 
		{ 
			counter--; 
		}

		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right) && counter < meshes.size()) 
		{ 
			counter++; 
		}
		ImGui::PopButtonRepeat();
		ImGui::SameLine();
		ImGui::Text("%d", counter);


		ImGui::End();
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
	//bool meshProperties();
	//void addObject(Mesh& obj);

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
	std::vector<Object> m_meshes;
};