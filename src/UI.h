#pragma once
#include <iostream>
#include <unordered_map>
#include "../thirdparty/imgui-docking/imgui/imgui.h"
#include "../thirdparty/imgui-docking/imgui/imgui_internal.h"
#include "../thirdparty/imgui-docking/imgui/backends/imgui_impl_opengl3.h"
#include "../thirdparty/imgui-docking/imgui/backends/imgui_impl_glfw.h"
#include <../thirdparty/glfw-3.3.2/include/GLFW/glfw3.h>


class UI
{
public:
	UI(GLFWwindow* window);
	void prepareDockspace();
	void newUIFrame();
	void renderUI();
	void setFont(std::string& fontName);
	//void renderUI(GLFWwindow* window, void (*funcPtr)());
	void loginUI();
	void terminateUI();
	ImGuiIO& getIO() { return m_io; }

private:
	GLFWwindow* m_window;
	ImGuiIO& m_io;
	const char* m_glslVersion;
	std::unordered_map<std::string, ImFont*> m_fonts;
	ImFont* m_currFont;
	//ImFont* m_loginFont;
	//ImFont* m_uiFont;
};