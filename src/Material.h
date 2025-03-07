#ifndef MATERIAL_H
#define MATERIAL_H
#include <../thirdparty/glm/glm/glm.hpp>
#include <../thirdparty/glad/include/glad/glad.h>

/*
	File Name: Material.h
	Author: Mason Shaner
	Date: 2/21/2024
	Course: CS-330
	Description: A simple class for storing the ambient, diffuse, specular, and shininess values for a Phong shading model
*/

class Material
{
public:
	Material(glm::vec3 a, glm::vec3 d, glm::vec3 s, GLfloat shine);
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat shininess;
};

#endif

