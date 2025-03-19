#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <cstdlib>
#include <../thirdparty/glad/include/glad/glad.h>
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
	void scaleMesh(glm::vec3 scale);
	void rotateMesh(glm::vec3 rotation);
	void translateMesh(glm::vec3 translation);
	void scaleTexture(glm::vec2 scale);
	glm::vec3 getScale() { return m_scale; }
	glm::vec3 getRotation() { return m_rotation; }
	glm::vec3 getTranslation() { return m_translation; }
	glm::mat4 getModelMatrix();
	glm::vec2 getUVscale() { return m_UVScale; }
	void destroyMesh();
	void destroyTexture();

	VAO m_vao;
	VBO m_vbo;
	Texture m_texture;
	SHAPES m_shapeType;
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_translation;
	glm::vec2 m_UVScale;
	std::vector<GLfloat> m_verts;
	GLuint m_numVerts;
	float m_numSlices;
	float m_numVerticesSide;
	float m_numVerticesTopAndBottom;
	float m_numVerticesTotal;
	std::string m_meshName;

};



#endif
