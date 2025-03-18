#include "View.h"

/*
----------------------------------------------------------------
                       LOGIN VIEW
----------------------------------------------------------------
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
    m_loginStatus = login();
    m_uiBackend.renderUI();

}



/*
----------------------------------------------------------------
                       MESH VIEW
----------------------------------------------------------------
*/

MeshView::MeshView(GLFWwindow* window, UI backend, std::vector<meshObject>& meshes)
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
    sceneHierarchy(m_meshes);
    MaterialEditor(m_meshes);
    m_uiBackend.renderUI();
}

//bool MeshView::meshProperties()
//{
//    ImGui::Begin("Mesh Properties");
//
//    // Arrow buttons with Repeater
//    static int counter = 0;
//    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
//    ImGui::PushButtonRepeat(true);
//    if (ImGui::ArrowButton("##left", ImGuiDir_Left) && counter >= 0) { counter--; }
//    ImGui::SameLine(0.0f, spacing);
//    if (ImGui::ArrowButton("##right", ImGuiDir_Right) && counter < 10) { counter++; }
//    ImGui::PopButtonRepeat();
//    ImGui::SameLine();
//    ImGui::Text("%d", counter);
//
//    ImGui::End();
//}

//void MeshView::addObject(Mesh& obj)
//{
//    m_meshObjects.emplace_back(obj);
//}
