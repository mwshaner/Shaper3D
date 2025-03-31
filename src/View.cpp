#include "View.h"

/*
*		   File: View.cpp
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description:
*		   This file contains the implementations for the methods of the LoginView and MeshView classes
*/


/*
---------------------------------------------------------------------------------------------------------
                                         LoginView
---------------------------------------------------------------------------------------------------------
*/

LoginView::LoginView(GuiBackend backend, CRUDController controller)
    : m_controller{ controller },
	  m_guiBackend{ backend },
      m_loginStatus{ false }
{

}

void LoginView::render()
{
	m_guiBackend.newUIFrame();
	m_guiBackend.prepareDockspace();
    m_loginStatus = loginWindow();
	m_guiBackend.renderUI();
}

bool LoginView::loginWindow()
{
	static std::string username(128, '\0');
	static std::string password(128, '\0');
	static std::string storedUsername;
	static std::string storedPassword;
	static std::string pass = "1";
	static bool needsAccount = false;
	bool result = false;
	static bool showErr = false;


	ImGui::Begin("##Login", nullptr, ImGuiWindowFlags_NoTitleBar);


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

		m_loginStatus = m_controller.read(storedPassword.c_str(), storedUsername.c_str());
		showErr = m_loginStatus ? 0 : 1;
	}

	if (ButtonCenteredOnLine("Create Account"))
	{
		needsAccount = true;
	}

	if (needsAccount)
	{
		result = createAccountWindow();

		// Temporary to simulate behavior of sucessful account creation in the DB
		needsAccount = !result;
	}

	if (showErr)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::SetCursorPosX(posX - 250);
		ImGui::Text("Sorry, We Have No Account Associated With That Username/Password");
		ImGui::PopStyleColor();
	}

	if (m_loginStatus)
	{
		ImGui::End();
		return true;
	}

	ImGui::End();
	return false;
}

bool LoginView::createAccountWindow()
{
	static std::string CAusername(128, '\0');
	static std::string CApassword(128, '\0');
	static std::string CAstoredUsername;
	static std::string CAstoredPassword;

	ImGui::Begin("Create Account");
	ImGui::Dummy(ImVec2(0, 400));

	// Widget width may need some experimentation depending on the your use case
	float widgetWidth = 800.0f;
	float posX = (ImGui::GetWindowContentRegionWidth() - widgetWidth) * 0.5f;


	// Center and draw the label
	ImGui::SetCursorPosX(posX);
	ImGui::Text("Please Enter a Username");
	ImGui::Dummy(ImVec2(0, 5));
	ImGui::SetCursorPosX(posX);
	ImGui::PushItemWidth(widgetWidth);
	ImGui::InputText("##Username", &CAusername[0], CAusername.size());
	ImGui::PopItemWidth();

	ImGui::Dummy(ImVec2(0, 25));

	ImGui::SetCursorPosX(posX);
	ImGui::Text("Please Enter a Password");
	ImGui::Dummy(ImVec2(0, 5));
	ImGui::SetCursorPosX(posX);
	ImGui::PushItemWidth(widgetWidth);
	ImGui::InputText("##Password", &CApassword[0], CApassword.size(), ImGuiInputTextFlags_Password);

	ImGui::NewLine();
	ImGui::NewLine();

	ImGui::SetCursorPosX(posX);
	ImGui::Text("Press Submit to Create Your Account");
	if (ButtonCenteredOnLine("Submit"))
	{
		ImGui::End();
		return true;
	}
	ImGui::End();
	return false;
}



/*
---------------------------------------------------------------------------------------------------------
										 MeshView
---------------------------------------------------------------------------------------------------------
*/

MeshView::MeshView(GuiBackend backend, std::vector<std::shared_ptr<MeshObject>> meshes)
    : m_guiBackend{ backend },
      m_meshes{ meshes }
{

}

/*
    render() uses the ImGui backend to draw whatever class methods
	are called between prepareDockspace() and renderUI().
*/
void MeshView::render()
{
	// See GuiBackend constructor for the available fonts and their IDs
    m_guiBackend.setFont(std::string("RudaBold25"));
    m_guiBackend.newUIFrame();
    m_guiBackend.prepareDockspace();

	// The view methods should always be called after prepareDockspace()
    sceneHierarchyWindow();
    materialEditorWindow();
	// and before renderUI()

	m_guiBackend.renderUI();
}


/*
    sceneHierarchyWindow() displays a list of all current 3d meshes in the scene.
	These meshes can be selected which will then activate the mesh properties panel 
	for that object, allowing the user to control the translation, rotation, and scale 
	using the vec3 controls.
*/
void MeshView::sceneHierarchyWindow()
{
	static glm::vec3 translation;
	static glm::vec3 rotation;
	static glm::vec3 scale;

	ImGui::Begin("Scene Hierarchy");
	ImGui::SeparatorText("Objects");

	ImVec2 availSize = ImGui::GetContentRegionAvail();
	float topHeight = availSize.y * 0.5f;

	// The selectable mesh object list
	ImGui::BeginChild("TopChild", ImVec2(0, topHeight), true);

	for (size_t i = 0; i < m_meshes.size(); i++)
	{
		bool isSelected = (m_selectedIndex == i);
		if (ImGui::Selectable(m_meshes.at(i)->m_mesh.m_meshName.c_str(), isSelected))
		{
			m_selectedIndex = (m_selectedIndex == i) ? -1 : i;
		}
	}
	ImGui::EndChild();

	// The mesh properties panel
	ImGui::BeginChild("Object Properties", ImVec2(0, 0), true);
	ImGui::SeparatorText("Mesh Properties");
	if (m_selectedIndex >= 0)
	{
		// get the selected objects TRS vec3s
		translation = m_meshes.at(m_selectedIndex)->m_mesh.m_translation;
		rotation = m_meshes.at(m_selectedIndex)->m_mesh.m_rotation;
		scale = m_meshes.at(m_selectedIndex)->m_mesh.m_scale;

		// Mesh Controls
		drawVec3Control("Translation", translation, 0.0, 120);
		drawVec3Control("Rotation", rotation, 1.0, 120);
		drawVec3Control("Scale", scale, 1.0, 120);

		// Update the selected objects properties
		m_meshes.at(m_selectedIndex)->m_mesh.translateMesh(translation);
		m_meshes.at(m_selectedIndex)->m_mesh.rotateMesh(rotation);
		m_meshes.at(m_selectedIndex)->m_mesh.scaleMesh(scale);
	}
	ImGui::EndChild();
	ImGui::End();
}

/*
    materialEditorWindow() displays the material and texture properties of the selected object.
	The specular, diffuse, ambient, shininess, and UV scale can be controlled via the vec3 and
	vec2 controls.
*/
void MeshView::materialEditorWindow()
{
	static glm::vec3 ambient;
	static glm::vec3 specular;
	static glm::vec3 diffuse;
	static float shininess;
	static glm::vec2 uvScale;

	
	ImGui::Begin("Material Editor");
	ImGui::NewLine();

	if (m_selectedIndex >= 0)
	{
		// get the selected objects material vec3's
		ambient = m_meshes.at(m_selectedIndex)->m_mat.ambient;
		specular = m_meshes.at(m_selectedIndex)->m_mat.specular;
		diffuse = m_meshes.at(m_selectedIndex)->m_mat.diffuse;
		shininess = m_meshes.at(m_selectedIndex)->m_mat.shininess;
		uvScale = m_meshes.at(m_selectedIndex)->m_mesh.m_UVScale;

		ImGui::SeparatorText("Material Properties");

		// Mesh Controls
		drawVec3Control("Ambient", ambient, 0.0, 120);
		drawVec3Control("Specular", specular, 0.0, 120);
		drawVec3Control("Diffuse", diffuse, 0.0, 120);

		// Shininess dragFloat
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 120.0f);
		ImGui::Text("Shininess");
		ImGui::NextColumn();
		ImGui::DragFloat("##Shininess", &shininess, 0.05);
		ImGui::Columns(1);

		ImGui::NewLine();
		ImGui::SeparatorText("Textures");

		// Display the texture of the selected object
		ImGui::Image((ImTextureID)(intptr_t)m_meshes.at(m_selectedIndex)->m_mesh.m_texture.getTextures()[0], ImVec2(512, 512));

		// UV scale controls
		ImGui::NewLine();
		drawVec2Control("UV Scale", uvScale, 1.0f, 100.0f);

		// Update the selected objects properties
		m_meshes.at(m_selectedIndex)->m_mat.ambient = ambient;
		m_meshes.at(m_selectedIndex)->m_mat.specular = specular;
		m_meshes.at(m_selectedIndex)->m_mat.diffuse = diffuse;
		m_meshes.at(m_selectedIndex)->m_mat.shininess = shininess;
		m_meshes.at(m_selectedIndex)->m_mesh.m_UVScale = uvScale;

	}
	ImGui::End();
}
