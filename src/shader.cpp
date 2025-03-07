#include "shader.h"

/*
	Shader.cpp
	Author: Mason Shaner
	Date: 1/26/2024
	Course: CS-330
	Description: The shader class loads in source code for the vertex and fragment shaders and creates, binds and destroys the shader program
*/

using namespace std;

Shader::Shader()
{

}

Shader::~Shader()
{
	glDeleteProgram(programId);
}

void Shader::load(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	// Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexShaderSource);
		fShaderFile.open(fragmentShaderSource);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cout << e.what() << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();



	// Compile the shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// similiar for Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};


	// shader Program
	programId = glCreateProgram();
	glAttachShader(programId, vertex);
	glAttachShader(programId, fragment);
	glLinkProgram(programId);

	// print linking errors if any
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::bind()
{
	glUseProgram(programId); // Use the shader program
}

void Shader::unbind()
{
	glUseProgram(0); // Use the shader program
}

/*
	setters for all of the different types of unifroms that a shader might use
*/
void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat2(const std::string& name, float value1, float value2) const
{
	glUniform2f(glGetUniformLocation(programId, name.c_str()), value1, value2);
}

void Shader::setFloat3(const std::string& name, float value1, float value2, float value3) const
{
	glUniform3f(glGetUniformLocation(programId, name.c_str()), value1, value2, value3);
}

void Shader::setVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::destroyShaderProgram()
{
	glDeleteProgram(programId);
}
