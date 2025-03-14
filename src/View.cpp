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
    bool (*funcPtr)() = &login;

    m_uiBackend.newUIFrame();
    m_loginStatus = m_uiBackend.renderUI(m_window, funcPtr);
}


/*
----------------------------------------------------------------
                       MESH VIEW
----------------------------------------------------------------
*/

MeshView::MeshView(GLFWwindow* window, UI backend)
    : m_uiBackend{ backend },
      //  m_controller{},
      m_window{ window },
      m_io{ m_uiBackend.getIO() }
{

}

void MeshView::render()
{
    void (*funcPtr)() = &meshProperties;

    m_uiBackend.newUIFrame();
    m_uiBackend.renderUI(m_window, funcPtr);
}
