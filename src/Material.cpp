#include "Material.h"

/*
	File Name: Material.cpp
	Author: Mason Shaner
	Date: 2/21/2024
	Course: CS-330
	Description: A simple class for storing the ambient, diffuse, specular, and shininess values for a Phong shading model
*/

Material::Material(glm::vec3 a, glm::vec3 d, glm::vec3 s, GLfloat shine)
{
	ambient = a, diffuse = d, specular = s, shininess = shine;
}