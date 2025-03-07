#include "../thirdparty/imgui-docking/imgui/imgui.h"
#include "../thirdparty/imgui-docking/imgui/backends/imgui_impl_opengl3.h"
#include "../thirdparty/imgui-docking/imgui/backends/imgui_impl_glfw.h"
#include <../thirdparty/glfw-3.3.2/include/GLFW/glfw3.h>


class UI
{
public:
	UI(GLFWwindow* window, ImGuiIO& io);
	void initUIContext(GLFWwindow* window);
	void newUIFrame();
	void renderUI(GLFWwindow* window);
	void terminateUI();

private:
	ImGuiIO& m_io;
	const char* m_glslVersion;
};