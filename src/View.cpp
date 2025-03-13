#include "View.h"


LoginView::LoginView(GLFWwindow* window, ImGuiIO& io)
    : m_uiBackend{ window, io },
    //  m_controller{},
      m_window{ window },
      m_io{ io }
{

}

void LoginView::render()
{
    void (*loginPtr)() = &login;

    m_uiBackend.newUIFrame();
    m_uiBackend.renderUI(m_window, loginPtr);
}
