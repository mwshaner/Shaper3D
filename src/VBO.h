#ifndef VBO_H
#define VBO_H

#include <../thirdparty/glad/include/glad/glad.h>
#include <vector>

/*
	File Name: VBO.h
	Author: Mason Shaner
	Date: 2/20/2024
	Course: CS-330
	Description: A class for creating and using vertex buffer objects
*/

class VBO
{
public:
	GLuint ID;
	VBO();
	~VBO();
	void createVBO(std::vector<GLfloat> vertices, GLsizeiptr size);
	void bind();
	void unbind();
	void Delete();
};

#endif
