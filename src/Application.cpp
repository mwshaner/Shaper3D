#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <../thirdparty/glad/include/glad/glad.h>
#include <../thirdparty/glfw-3.3.2/include/GLFW/glfw3.h>
#include <../thirdparty/glm/glm/glm.hpp>
#include <../thirdparty/glm/glm/ext/matrix_transform.hpp>
#include "../thirdparty/imgui-docking/imgui/imgui.h"
#include "../thirdparty/imgui-docking/imgui/backends/imgui_impl_opengl3.h"
#include "../thirdparty/imgui-docking/imgui/backends/imgui_impl_glfw.h"
#include "camera.h" // Camera class
#include "shader.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderer.h"
#include "DB.h"
//#include "UI.h"
#include "View.h"

/*
	Application.cpp
	Author: Mason Shaner
	Date: 1/26/2024
	Course: CS-330
	Description: Main application for creating an OpenGL window and rendering different mesh objects
*/

using namespace std;

// Unnamed namespace
namespace
{
	// Window title
	const char* const WINDOW_TITLE = "CS-499 Capstone";

	// Window height and width
	const int WINDOW_WIDTH = 1600;
	const int WINDOW_HEIGHT = 1200;

	// Camera vectors
	Camera camera(glm::vec3(0.0f, 4.0f, 20.0f));
	float lastX = WINDOW_WIDTH / 2.0f;
	float lastY = WINDOW_HEIGHT / 2.0f;
	bool firstMouse = true;
	bool SHIFT = false;
	bool PAN = false;

	enum CameraModes
	{
		PERSPECTIVE,
		ORTHOGRAPHIC
	};


	CameraModes mode = PERSPECTIVE;

	// Frame time
	float deltaTime = 0.0f; // Time between current frame and last frame
	float lastFrame = 0.0f;

	// Main GLFW window
	GLFWwindow* gWindow = nullptr;

	// Shader program
	Shader lightShader;
	Shader shaderProgram;

	// light shader source code
	const char* lampVertexShaderSource = "../../../resources/lampVertex.vs";
	const char* lampFragmentShaderSource = "../../../resources/lampFrag.fs";

	// cube shader program source code
	const char* cubeVertexShaderSource = "../../../resources/cubeVertex.vs";
	const char* cubeFragmentShaderSource = "../../../resources/cubeFrag.fs";

	bool keyState = false;
}


/* User-defined Function prototypes tos:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * and render graphics on the screen
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
glm::mat4 UGetProjectionMatrix();




// Main
int main(int argc, char* argv[])
{
	typedef std::tuple<std::string, std::string, std::string> userRecord;

	if (!UInitialize(argc, argv, &gWindow))
	{
		return EXIT_FAILURE;
	}

	DB database;

	database.connect();

	std::string sql = "SELECT * from USERS";
	std::vector< userRecord > records;

	database.initialize_database();
	database.run_query(sql, records);

	for (auto record : records)
	{
		std::cout << "User: " << std::get<1>(record) << " ID = " << std::get<0>(record) << " PASSWORD = " << std::get<2>(record) << " " << std::endl;
	}

	Renderer renderer;

	// Cube and cylinder mesh objects
	Mesh lightCube;
	Mesh soda;
	//Mesh coaster;
	//Mesh kiss;
	//Mesh table;
	//Mesh chapstick;
	//Mesh rubikscube;
	//Mesh wall1;
	//Mesh wall2;

	// Create the different meshes
	soda.createCylinder(36, 3.0f, 1.0f);
	//coaster.createCube(0.5f, 0.5f, 0.05f);
	//kiss.createPyramid(0.5, 0.5, 0.5);
	//table.createPlane(30.0, 30.0);
	//chapstick.createCylinder(36, 5.0f, 1.0f);
	//rubikscube.createCube(0.5f, 0.5f, 0.5f);
	lightCube.createCube(0.5f, 0.5f, 0.5f);
	//wall1.createPlane(30.0, 30.0);
	//wall2.createPlane(30.0, 30.0);


	// Send the textures to the mesh objects
	//const char* tex1FileName = "../../../Textures/hersheyKiss.png";
	//kiss.createTexture(1, tex1FileName);
	//const char* tex2FileName = "../../../Textures/coastertop.png";
	//coaster.createTexture(1, tex2FileName);
	//const char* tex3FileName = "../../../Textures/table.jpg";
	//table.createTexture(1, tex3FileName);
	const char* tex4FileName = "../../../Textures/coke.png";
	const char* tex5FileName = "../../../Textures/sodacaps.png";
	soda.createTexture(2, tex4FileName, tex5FileName);
	//const char* tex6FileName = "../../../Textures/chapstick.png";
	//const char* tex7FileName = "../../../Textures/chapstickcap.png";
	//chapstick.createTexture(2, tex6FileName, tex7FileName);
	//const char* tex8FileName = "../../../Textures/rubikscube.jpg";
	//rubikscube.createTexture(1, tex8FileName);
	//const char* tex9FileName = "../../../Textures/walls.png";
	//wall1.createTexture(1, tex9FileName);
	//const char* tex10FileName = "../../../Textures/walls2.png";
	//wall2.createTexture(1, tex10FileName);

	// Create the shader program
	shaderProgram.load(cubeVertexShaderSource, cubeFragmentShaderSource);
	lightShader.load(lampVertexShaderSource, lampFragmentShaderSource);

	// Set backgroundcolor of the window to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	const char* glsl_version = "#version 100";
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// Setup Dear ImGui context
	//IMGUI_CHECKVERSION();
   //ImGui::CreateContext();
   //ImGuiIO& io = ImGui::GetIO(); (void)io;

	static UI guiBackend{ gWindow };
    
	//UI gui{ gWindow, io };
	LoginView loginView{ gWindow, guiBackend };
	MeshView meshView{ gWindow, guiBackend };
	

	//gui.renderUI(gWindow);

	// RENDER LOOP START
	while (!glfwWindowShouldClose(gWindow))
	{
		// Calculate frame times
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;	

			// Process user input
			UProcessInput(gWindow);

			// Enable z-depth
			glEnable(GL_DEPTH_TEST);

			// Clear the frame and Z buffers.
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		if (loginView.getLoginStatus())
		{
			// Apply all transformations
			//table.translateMesh(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -2.0f, 0.0f)));
			//coaster.scaleMesh(glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)));
			//coaster.translateMesh(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -1.9f, 0.0f)));
			soda.rotateMesh(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0f, 0.0f)));
			soda.translateMesh(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -0.2f, 0.0f)));
			//chapstick.scaleMesh(glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.4f, 0.4f)));
			//chapstick.rotateMesh(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			//chapstick.translateMesh(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.6f, -2.0f)));
			//kiss.translateMesh(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, -1.5f, 0.0f)));
			//rubikscube.translateMesh(glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, -1.5f, 0.0f)));
			//wall1.rotateMesh(glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			//wall1.translateMesh(glm::translate(glm::vec3(-30.0f, 28.0f, 0.0f)));

			//wall2.rotateMesh(glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
			//wall2.rotateMesh(glm::rotate(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
			//wall2.rotateMesh(glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
			//wall2.translateMesh(glm::translate(glm::vec3(0.0f, 28.0f, -30.0f)));

			// Send the view and projection matrices to the shader
			shaderProgram.setMat4("view", camera.GetViewMatrix());
			shaderProgram.setMat4("projection", UGetProjectionMatrix());

			// draw the lights
			renderer.drawLights(shaderProgram, camera);

			// Draw all of the mesh objects
			//Material coasterMat(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 1.5f);
			//renderer.drawMesh(coaster, shaderProgram, camera, coasterMat);

			Material sodaMat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f), 0.25f);
			renderer.drawMesh(soda, shaderProgram, camera, sodaMat);

			//Material kissMat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.25f);
			//renderer.drawMesh(kiss, shaderProgram, camera, kissMat);

			//Material tableMat(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f);
			//renderer.drawMesh(table, shaderProgram, camera, tableMat);

			//Material chapstickMat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), 0.25f);
			//renderer.drawMesh(chapstick, shaderProgram, camera, chapstickMat);

			//Material rubikscubeMat(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 0.25f);
			//renderer.drawMesh(rubikscube, shaderProgram, camera, rubikscubeMat);

			/*Material wall1Mat(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f);
			renderer.drawMesh(wall1, shaderProgram, camera, wall1Mat);

			Material wall2Mat(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(1.0f, 1.0f, 1.0f), 2.0f);
			renderer.drawMesh(wall2, shaderProgram, camera, wall2Mat);*/

			meshView.render();
		}
		else
		{
			loginView.render();
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(gWindow);

		// Poll input
		glfwPollEvents();

	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(gWindow);
	glfwTerminate();
	database.closeDB();
	exit(EXIT_SUCCESS); // Sucessful program termination
}


// UInitialize() configures GLFW, GLEW, and creates a new window
// @param window -- double pointer to a GLFW window object
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	// GLFW: initialize and configure (specify desired OpenGL version)
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// tell GLFW to capture our mouse
	//glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Initialze GLEW
	
	// Note: if using GLEW version 1.13 or earlier
	/*glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}*/

	// Displays GPU OpenGL version
	cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

	return true;

}

/*
  UProcessInput() queries GLFW whether relevant keys are pressed/released this frame and react accordingly
  @param: window -- pointer to GLFW window object
*/
void UProcessInput(GLFWwindow* window)
{
	static const float cameraSpeed = 2.5f;

	// Close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// Keyboard input commands
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		// keyState is only false when the key has been released so this ensures that it only switches modes once per key stroke (prevents multiple callbacks)
		if (keyState == false)
		{
			if (mode == PERSPECTIVE)
			{
				mode = ORTHOGRAPHIC;
			}
			else
			{
				mode = PERSPECTIVE;
			}
		}

	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
	{
		if (SHIFT == false)
		{
			if (PAN == 0)
			{
				PAN = 1;
			}
			else
			{
				PAN = 0;
			}
		}
	}
	// set the P key to prevent multiple callbacks
	keyState = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
	SHIFT = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
}

/*
	UMousePositionCallback() is a callback function that collects mouse positions and sends them to the camera object
*/
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (PAN)
	{
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	
}

/*
	UMouseScrollCallback() sends scrollwheel input to the camera object
*/
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// glfw: Handle mouse button events.
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "Left mouse button pressed" << endl;
		else
			cout << "Left mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "Middle mouse button pressed" << endl;
		else
			cout << "Middle mouse button released" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "Right mouse button pressed" << endl;
		else
			cout << "Right mouse button released" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}

// UResizeWindow(): whenever the window size changed (by OS or user resize) this callback function executes
// @params: window -- pointer to GLFW window object. width -- desired width of window. height -- desired height of window
void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

glm::mat4 UGetProjectionMatrix()
{
	glm::mat4 projection;

	if (mode == ORTHOGRAPHIC)
	{
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	}
	else
	{
		projection = glm::perspective(glm::radians(camera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

	}
	return projection;
}
