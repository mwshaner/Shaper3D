#ifndef VAO_H
#define VAO_H

#include <../thirdparty/glad/include/glad/glad.h>
#include"VBO.h"

/*
	File Name: VAO.h
	Author: Mason Shaner
	Date: 2/20/2024
	Course: CS-330
	Description: A class for creating and using vertex array objects
*/

class VAO
{
public:
	GLuint ID;
	VAO();
	~VAO();
	void linkVBO(VBO bufferObject, GLuint floatPerVert, GLuint floatPerNorm, GLuint floatPerUV, GLuint stride);
	void bind();
	void unbind();
	void Delete();
};

#endif
