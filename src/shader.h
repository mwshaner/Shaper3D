#ifndef SHADER_H
#define SHADER_H
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <../thirdparty/glad/include/glad/glad.h>
#include <../thirdparty/glm/glm/glm.hpp>
#include <../thirdparty/glm/glm/gtc/type_ptr.hpp>

/*
	Shader.cpp
	Author: Mason Shaner
	Date: 1/26/2024
	Course: CS-330
	Description: The shader class loads in source code for the vertex and fragment shaders and creates, binds and destroys the shader program
*/



class Shader
{
public:
	Shader();
	~Shader();
	//Shader(const char* vertexShaderSource, const char* fragmentSource);
	void load(const char* vertexShaderSource, const char* fragmentSource);
	void bind();
	void unbind();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat2(const std::string& name, float value1, float value2) const;
	void setFloat3(const std::string& name, float value, float value2, float value3) const;
	void setVec2(const std::string& name, glm::vec2 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec4(const std::string& name, glm::vec4 value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void destroyShaderProgram();
private:
	//GLuint shaderProgram;
	GLuint programId;
};
#endif