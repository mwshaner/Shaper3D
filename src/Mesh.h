#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <cstdlib>
#include <../thirdparty/glad/include/glad/glad.h>
#include <../thirdparty/glfw-3.3.2/include/GLFW/glfw3.h>
#include <../thirdparty/glm/glm/glm.hpp>
#include <../thirdparty/glm/glm/ext/matrix_transform.hpp>
#include <vector>
#include "VBO.h"
#include "VAO.h"
#include "Texture.h"


/*
	Mesh.h
	Author: Mason Shaner
	Date: 1/26/2024
	Course: CS-330
	Description: The Mesh class allows a user to create differenct primitve meshes including cylinders, cubes, pyramids etc..
*/

// Shape flag used to select a drawing method based on the primtive mesh type
enum SHAPES
{
	PLANE,
	CUBE,
	CYLINDER,
	PYRAMID,
	CIRCLE,
	COASTER,
	CONE,
	LIGHT
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	void createCylinder(float numSides, float height, float radius);
	void createCube(float length, float width, float height);
	void createPyramid(float width, float length, float height);
	void createPlane(float width, float length);
	void createTexture(int count, const char* tex1Name, const char* tex2Name = "0", const char* tex3Name = "0", const char* tex4Name = "0", const char* tex5Name = "0");
	void scaleMesh(glm::mat4 t_scale);
	void rotateMesh(glm::mat4 t_rotation);
	void translateMesh(glm::mat4 t_translate);
	void scaleTexture(glm::vec2 scale);
	glm::mat4 getModelMatrix();
	glm::vec2 getUVscale() { return UVScale; }
	void destroyMesh();
	void destroyTexture();

	VAO vao;
	VBO vbo;
	Texture texture;
	SHAPES shapeType;
	glm::mat4 scale;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::vec2 UVScale;
	std::vector<GLfloat> verts;
	GLuint numVerts;
	float numSlices;
	float numVerticesSide;
	float numVerticesTopAndBottom;
	float numVerticesTotal;
};



#endif
