#include "VAO.h"

/*
	File Name: VAO.cpp
	Author: Mason Shaner
	Date: 2/20/2024
	Course: CS-330
	Description: A class for creating and using vertex array objects
*/

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
	
}

void VAO::linkVBO(VBO bufferObject, GLuint floatPerVert, GLuint floatPerNorm, GLuint floatPerUV, GLuint stride)
{
	bufferObject.bind();

	// Create Vertex Attribute Pointers
	glVertexAttribPointer(0, floatPerVert, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatPerNorm, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatPerVert)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatPerVert + floatPerNorm)));
	glEnableVertexAttribArray(2);
}

void VAO::bind()
{
	glBindVertexArray(ID);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}