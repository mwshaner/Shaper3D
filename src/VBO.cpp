#include "VBO.h"

/*
	File Name: VBO.cpp
	Author: Mason Shaner
	Date: 2/20/2024
	Course: CS-330
	Description: A class for creating and using vertex buffer objects
*/

VBO::VBO()
{

}

VBO::~VBO()
{
	
}

void VBO::createVBO(std::vector<GLfloat> vertices, GLsizeiptr size)
{
	// Create VBO
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID); // Activates the buffer
	glBufferData(GL_ARRAY_BUFFER,  size, &vertices[0], GL_STATIC_DRAW); // Sends vertex or coordinate data to the GPU
}

void VBO::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
