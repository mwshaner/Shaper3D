#pragma once
#include <iostream>
#include "Object.h"
#include "GuiBackend.h"

/*
*		   File: View.h
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description:
*		   The view interface defines the api for an ImGui frontend window. The derived classes 
*		   LoginView and Meshview each implement different UI's which can be associated with different 
*          controllers and models. 
*/


/*
    The view interface
*/
class IView
{
public:
	virtual ~IView() = default;
	virtual void render() = 0;
};


/*
	LoginView is responsible for implementing the view component of the login UI.
	A LoginView object will be used by a CRUDController object to interact with
	the database in the model class.
*/
class LoginView : public IView
{
public:
	LoginView(GuiBackend backend);
	void render() override;
	bool loginWindow();
	bool createAccountWindow();
	bool getLoginStatus() { return m_loginStatus; }

private:
	GuiBackend m_guiBackend;
	bool m_loginStatus;
};

/*
	MeshView is responsible for implementing the main UI of the application including the 
	scene hierarchy panel and material editor. 
*/
class MeshView : public IView
{
public:
	MeshView(GuiBackend backend, std::vector<std::shared_ptr<meshObject>> meshes);
	void render() override;
	void sceneHierarchyWindow();
	void materialEditorWindow();

private:
	GuiBackend m_guiBackend;
	std::vector<std::shared_ptr<meshObject>> m_meshes;
	int16_t m_selectedIndex = -1;
};

// ImGui Utility functions for centering buttons and drawing widgets
namespace
{
	// draws a button centered in the current window
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

	/*
		   Draws a drag float vec3 control of the form:

		   [X][0.0000][Y][0.0000][Z][0.0000]

		   which controls the XYZ axes with dragFloats, and where the XYZ buttons
		   reset each axes to a default value of 0. A custom reset value can be
		   passed to the resetValue paramter if needed.
	*/
	static void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());

		// Column width may take a little tweaking to get right depending on the size of your windows
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };


		// X reset button
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}

		// X drag float
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);


		// Y reset button
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}

		// Y drag float
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		// Z reset button
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		if (ImGui::Button("Z", buttonSize))
		{
			values.z = resetValue;
		}

		// Y drag float
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	/*
		   Draws a drag float vec2 control of the form:

		   [X][0.0000][Y][0.0000]

		   which controls the XY axes with dragFloats, and where the XY buttons
		   reset each axes to a default value of 0. A custom reset value can be
		   passed to the resetValue paramter if needed.
	*/
	static void drawVec2Control(const std::string& label, glm::vec2& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		/*
			NOTE: always use a unique label when calling this function or the dragfloats will overwrite each other when this
			function is called multiple times
		*/
		ImGui::PushID(label.c_str());

		// Column width may take a little tweaking to get right depending on the size of your windows
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		// X reset value
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
		{
			values.x = resetValue;
		}

		// X drag float
		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		// Y reset value
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
		{
			values.y = resetValue;
		}

		// Y drag float
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.07f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::PopStyleColor(3);

		ImGui::PopStyleVar();
		ImGui::Columns(1);
		ImGui::PopID();
	}
}
