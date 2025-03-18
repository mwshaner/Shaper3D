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

	static void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		if (ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
		}
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	bool createAccount()
	{
		//ImGui::Begin("Create Account");
		ImGui::Text("Make an account!");

		//ImGui::End();
		return true;
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
			bool res = createAccount();
		}

		ImGui::End();
		return false;
	}

	void meshProperties(std::vector<meshObject>& meshes)
	{
		static glm::vec3 translation(0.0f, 0.0f, 0.0f);
		static glm::vec3 rotation(1.0f, 1.0f, 1.0f);
		static glm::vec3 scale(1.0f, 1.0f, 1.0f);

		static int selectedIndex = -1;

		ImGui::Begin("Scene Hierarchy");

		ImVec2 availSize = ImGui::GetContentRegionAvail();

		float topHeight = availSize.y * 0.5f;

		ImGui::BeginChild("TopChild", ImVec2(0, topHeight), true);
		
		for (size_t i = 0; i < meshes.size(); i++)
		{
			bool isSelected = (selectedIndex == i);
			if (ImGui::Selectable(meshes.at(i).m_mesh.meshName.c_str(), isSelected))
			{
				selectedIndex = (selectedIndex == i) ? -1 : i;
			}
		}
		ImGui::EndChild();

		ImGui::BeginChild("Object Properties", ImVec2(0, 0), true);
		
		drawVec3Control("Translation", translation, 0.0, 120);
		drawVec3Control("Rotation", rotation, 0.0, 120);
		drawVec3Control("Scale", scale, 1.0, 120);

		meshes.at(0).m_mesh.translateMesh(glm::translate(glm::mat4(1.0f), translation));
		meshes.at(0).m_mesh.rotateMesh(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), rotation));
		meshes.at(0).m_mesh.scaleMesh(glm::scale(glm::mat4(1.0f), scale));

		ImGui::EndChild();

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
	MeshView(GLFWwindow* window, UI backend, std::vector<meshObject>& meshes);
	void render();
	//bool meshProperties();
	//void addObject(Mesh& obj);

private:
	UI m_uiBackend;
	//Controller m_controller;
	GLFWwindow* m_window;
	ImGuiIO& m_io;
	std::vector<meshObject>& m_meshes;
};