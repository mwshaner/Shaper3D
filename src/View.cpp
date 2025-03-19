#include "View.h"

/*
-------------------------------------------------------------------------------------------------------------
                       LOGIN VIEW
-------------------------------------------------------------------------------------------------------------
*/


LoginView::LoginView(GLFWwindow* window, UI backend)
    : m_uiBackend{ backend },
      //m_controller{},
      m_window{ window },
      m_io{ m_uiBackend.getIO() },
      m_loginStatus{ false }
{

}

void LoginView::render()
{
    /*bool (*funcPtr)() = &login;

    m_uiBackend.newUIFrame();
    m_loginStatus = m_uiBackend.renderUI(m_window, funcPtr);*/

    m_uiBackend.newUIFrame();
    m_uiBackend.prepareDockspace();
    m_loginStatus = loginWindow();
    m_uiBackend.renderUI();

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

		storedPassword = storedPassword.c_str();
		//showErr = storedPassword == pass ? true : false;
		if (storedPassword != pass)
		{
			showErr = true;
		}
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

	// Temporary until DB queries are fully incoroprated
	if (storedPassword == pass)
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
---------------------------------------------------------------------------------------------------------------------
                       MESH VIEW
---------------------------------------------------------------------------------------------------------------------
*/

MeshView::MeshView(GLFWwindow* window, UI backend, std::vector<std::shared_ptr<meshObject>> meshes)
    : m_uiBackend{ backend },
      //  m_controller{},
      m_window{ window },
      m_io{ m_uiBackend.getIO() },
      m_meshes{ meshes }
{

}

void MeshView::render()
{
    m_uiBackend.setFont(std::string("RudaBold25"));
    m_uiBackend.newUIFrame();
    m_uiBackend.prepareDockspace();
    sceneHierarchyWindow();
    materialEditorWindow();
    m_uiBackend.renderUI();
}

void MeshView::sceneHierarchyWindow()
{
	static glm::vec3 translation;
	static glm::vec3 rotation;
	static glm::vec3 scale;

	ImGui::Begin("Scene Hierarchy");
	ImGui::SeparatorText("Objects");

	ImVec2 availSize = ImGui::GetContentRegionAvail();

	float topHeight = availSize.y * 0.5f;

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

	ImGui::BeginChild("Object Properties", ImVec2(0, 0), true);
	ImGui::SeparatorText("Mesh Properties");
	if (m_selectedIndex >= 0)
	{
		translation = m_meshes.at(m_selectedIndex)->m_mesh.m_translation;
		rotation = m_meshes.at(m_selectedIndex)->m_mesh.m_rotation;
		scale = m_meshes.at(m_selectedIndex)->m_mesh.m_scale;

		// Mesh Controls
		drawVec3Control("Translation", &translation, 0.0, 120);
		drawVec3Control("Rotation", &rotation, 1.0, 120);
		drawVec3Control("Scale", &scale, 1.0, 120);

		// Manipulates the mesh based on the controllers
		m_meshes.at(m_selectedIndex)->m_mesh.translateMesh(translation);
		m_meshes.at(m_selectedIndex)->m_mesh.rotateMesh(rotation);
		m_meshes.at(m_selectedIndex)->m_mesh.scaleMesh(scale);
	}

	ImGui::EndChild();
	ImGui::End();
}

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
		ambient = m_meshes.at(m_selectedIndex)->m_mat.ambient;
		specular = m_meshes.at(m_selectedIndex)->m_mat.specular;
		diffuse = m_meshes.at(m_selectedIndex)->m_mat.diffuse;
		shininess = m_meshes.at(m_selectedIndex)->m_mat.shininess;
		uvScale = m_meshes.at(m_selectedIndex)->m_mesh.m_UVScale;

		ImGui::SeparatorText("Material Properties");

		// Mesh Controls
		drawVec3Control("Ambient", &ambient, 0.0, 120);
		drawVec3Control("Specular", &specular, 0.0, 120);
		drawVec3Control("Diffuse", &diffuse, 0.0, 120);

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, 120.0f);
		ImGui::Text("Shininess");
		ImGui::NextColumn();
		ImGui::DragFloat("##Shininess", &shininess, 0.05);
		ImGui::Columns(1);

		ImGui::NewLine();
		ImGui::SeparatorText("Textures");

		/*for (int i = 0; i < 2; i++)
		{
			ImGui::NewLine();
			ImGui::Image((ImTextureID)(intptr_t)meshes.at(i).m_mesh.texture.getTextures()[i], ImVec2(250, 250));
		}*/
		ImGui::Image((ImTextureID)(intptr_t)m_meshes.at(m_selectedIndex)->m_mesh.m_texture.getTextures()[0], ImVec2(512, 512));

		ImGui::NewLine();
		drawVec2Control("UV Scale", &uvScale, 1.0f, 100.0f);

		m_meshes.at(m_selectedIndex)->m_mat.ambient = ambient;
		m_meshes.at(m_selectedIndex)->m_mat.specular = specular;
		m_meshes.at(m_selectedIndex)->m_mat.diffuse = diffuse;
		m_meshes.at(m_selectedIndex)->m_mat.shininess = shininess;
		m_meshes.at(m_selectedIndex)->m_mesh.m_UVScale = uvScale;

	}
	ImGui::End();
}
