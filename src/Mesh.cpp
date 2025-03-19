#include "Mesh.h"
#include <vector>

/*
	Mesh.cpp
	Author: Mason Shaner
	Date: 1/26/2024
	Course: CS-330
	Description: The Mesh class allows a user to create differenct primitve meshes including cylinders, cubes, pyramids etc..
*/


/*
	Default constructor applies no scaling, rotation, or translation to the mesh
*/
Mesh::Mesh()
{
	glm::mat4 identityMatrix = glm::mat4(1.0f);  // Create an identity matrix.
	//m_scale = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
	//m_rotation = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//m_translation = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
	
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_rotation = glm::vec3(1.0f, 1.0f, 1.0f);
	m_translation = glm::vec3(0.0f, 0.0f, 0.0f);


	//scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	//rotation = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	m_UVScale = glm::vec2(1.0f, 1.0f);
}

Mesh::~Mesh()
{
	m_vao.Delete();
}


// Creates a plane of a particular width and height
void Mesh::createPlane(float width, float length)
{
	m_shapeType = PLANE;

	std::vector<GLfloat> vertices =
	{
		// Vertex Positions			// Normals			// Texture coords	// Index
		width, 0.0f, length,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,			//0
		width, 0.0f, -length,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,			//1
		-width,  0.0f, -length,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			//2

		width, 0.0f, length,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,			//0
		-width, 0.0f, length,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,			//3
		-width,  0.0f, -length,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			//2
	};

	// total float values per each type
	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);
	m_numVerts = vertices.size() / (floatsPerVertex + floatsPerNormal + floatsPerUV);

	// create the VAO and VBO
	m_vao.bind();
	m_vbo.createVBO(vertices, vertices.size() * sizeof(float));
	m_vao.linkVBO(m_vbo, 3, 3, 2, stride);
	m_vao.unbind();
}

/*
	createCylinder() generates a cylinder with user specified criteria
*/
void Mesh::createCylinder(float numSides, float height, float radius)
{
	m_shapeType = CYLINDER;

	// useful counts for drawing
	m_numSlices = numSides;
	m_numVerticesSide = (m_numSlices + 1) * 2;
	m_numVerticesTopAndBottom = m_numSlices + 2;
	m_numVerticesTotal = m_numVerticesSide + m_numVerticesTopAndBottom * 2;
	float angleStep = 2.0f * glm::pi<float>() / m_numSlices;

	// unit circle vertices
	std::vector<GLfloat> circleXcoords;
	std::vector<GLfloat> circleZcoords;

	// actual cylinder verts
	std::vector<GLfloat> top;
	std::vector<GLfloat> bottom;
	std::vector<GLfloat> tube;

	// Calculate 2d circle vertex positions in x and z axis
	float currAngle = 0.0f;
	for (int i = 0; i <= m_numSlices; i++)
	{
		circleXcoords.push_back(cos(currAngle)); // X
		circleZcoords.push_back(sin(currAngle)); // Z

		currAngle += angleStep;
	}

	// Create cylinder tube vertices
	for (int i = 0; i <= m_numSlices; i++)
	{
		float x = circleXcoords.at(i);
		float y = height / 2.0f;
		float z = circleZcoords.at(i);

		// Top point
		tube.push_back(x * radius);
		tube.push_back(y);
		tube.push_back(z * radius);

		// Normals
		tube.push_back(x);
		tube.push_back(0.0f);
		tube.push_back(z);

		// Texture coords
		tube.push_back((float)i / m_numSlices);
		tube.push_back(0.0f);

		// bottom point
		tube.push_back(x * radius);
		tube.push_back(-y);
		tube.push_back(z * radius);

		// Normals
		tube.push_back(x);
		tube.push_back(0.0f);
		tube.push_back(z);

		// Texture coords
		tube.push_back((float)i / m_numSlices);
		tube.push_back(1.0f);
	}

	// Top cap center point
	top.push_back(0.0f);
	top.push_back(height / 2.0f);
	top.push_back(0.0f);

	// Normals
	top.push_back(0.0f);
	top.push_back(0.0f);
	top.push_back(1.0f);

	// Texture coords
	top.push_back(0.5f);
	top.push_back(0.5f);

	// Create top cylinder cap
	for (int i = 0; i <= m_numSlices; i++)
	{
		float x = circleXcoords.at(i);
		float y = height / 2.0f;
		float z = circleZcoords.at(i);

		// Top point
		top.push_back(x * radius);
		top.push_back(y);
		top.push_back(z * radius);

		// Normals
		top.push_back(0.0f);
		top.push_back(0.0f);
		top.push_back(1.0f);

		// Texture coords
		top.push_back(-x * 0.5f + 0.5f);
		top.push_back(-z * 0.5f + 0.5f);
	}

	// Bottom cap center point
	bottom.push_back(0.0f);
	bottom.push_back(-height / 2.0f);
	bottom.push_back(0.0f);

	// Normals
	bottom.push_back(0.0f);
	bottom.push_back(0.0f);
	bottom.push_back(-1.0f);

	// Texture coords
	bottom.push_back(0.5f);
	bottom.push_back(0.5f);

	// Create bottom cylinder cap
	for (int i = 0; i <= m_numSlices; i++)
	{
		float x = circleXcoords.at(i);
		float y = -height / 2.0f;
		float z = circleZcoords.at(i);

		// Top point
		bottom.push_back(x * radius);
		bottom.push_back(y);
		bottom.push_back(z * radius);

		// Normals
		bottom.push_back(0.0f);
		bottom.push_back(0.0f);
		bottom.push_back(-1.0f);

		// Texture coords
		bottom.push_back(-x * 0.5f + 0.5f);
		bottom.push_back(-z * 0.5f + 0.5f);
	}

	// add the top and bottom caps to the end of the tube array
	tube.insert(tube.end(), top.begin(), top.end());
	tube.insert(tube.end(), bottom.begin(), bottom.end());

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;

	// store vertex and index count
	m_numVerts = sizeof(tube) / (sizeof(tube[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

	// Strides between vertex coordinates
	GLuint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

	// create the VAO and VBO
	m_vao.bind();	
	m_vbo.createVBO(tube, tube.size() * sizeof(float));
	m_vao.linkVBO(m_vbo, 3, 3, 2, stride);
	m_vao.unbind();
}

/*
	createCube() generates a cube mesh with user specified length width and height
*/
void Mesh::createCube(float length, float width, float height)
{
	m_shapeType = CUBE;

	// Create basic box verts
	std::vector<GLfloat> vertices =
	{
		-width, -height, -length,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 width, -height, -length,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 width,  height, -length,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 width,  height, -length,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-width,  height, -length,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-width, -height, -length,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-width, -height,  length,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 width, -height,  length,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 width,  height,  length,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 width,  height,  length,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-width,  height,  length,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-width, -height,  length,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-width,  height,  length, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-width,  height, -length, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-width, -height, -length, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-width, -height, -length, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-width, -height,  length, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-width,  height,  length, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 width,  height,  length,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 width,  height, -length,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 width, -height, -length,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 width, -height, -length,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 width, -height,  length,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 width,  height,  length,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-width, -height, -length,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 width, -height, -length,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 width, -height,  length,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 width, -height,  length,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-width, -height,  length,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-width, -height, -length,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-width,  height, -length,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 width,  height, -length,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 width,  height,  length,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 width,  height,  length,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-width,  height,  length,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-width,  height, -length,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;

	m_numVerts = vertices.size() / (floatsPerVertex + floatsPerNormal + floatsPerUV);

	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);// The number of floats before each

	// create the VAO and VBO
	m_vao.bind();
	m_vbo.createVBO(vertices, vertices.size() * sizeof(float));
	m_vao.linkVBO(m_vbo, 3, 3, 2, stride);
	m_vao.unbind();
}

/*
	createPyramid() generates a pyramid with user length and width
*/
void Mesh::createPyramid(float width, float length, float height)
{
	m_shapeType = PYRAMID;

	std::vector<GLfloat> vertices
	{
		// Vertex Positions		// Normals			// Texture coords
		//bottom side
		-width, -height, length,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		-width, -height, -length,	0.0f, -1.0f, 0.0f,	0.0f, 0.0f,		//back bottom left
		width, -height, -length,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
		-width, -height, length,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		-width, -height, length,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		width, -height, length,		0.0f, -1.0f, 0.0f,	1.0f, 1.0f,     //front bottom right
		width, -height, -length,		0.0f, -1.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
		-width, -height, length,		0.0f, -1.0f, 0.0f,	0.0f, 1.0f,     //front bottom left
		//back side
		0.0f, height, 0.0f,		0.0f, 0.0f, -1.0f,	0.5f, 1.0f,		//top point	
		width, -height, -length,		0.0f, 0.0f, -1.0f,	0.0f, 0.0f,		//back bottom right	
		-width, -height, -length,	0.0f, 0.0f, -1.0f,	1.0f, 0.0f,		//back bottom left
		0.0f, height, 0.0f,		0.0f, 0.0f, -1.0f,	0.5f, 1.0f,		//top point	
		//left side
		0.0f, height, 0.0f,		-1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		-width, -height, -length,	-1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		//back bottom left	
		-width, -height, length,		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f,     //front bottom left
		0.0f, height, 0.0f,		-1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		//right side
		0.0f, height, 0.0f,		1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		width, -height, length,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,     //front bottom right
		width, -height, -length,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//back bottom right	
		0.0f, height, 0.0f,		1.0f, 0.0f, 0.0f,	0.5f, 1.0f,		//top point	
		//front side
		0.0f, height, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,		//top point			
		-width, -height, length,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,     //front bottom left	
		width, -height, length,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,     //front bottom right
		0.0f, height, 0.0f,		0.0f, 0.0f, 1.0f,	0.5f, 1.0f,		//top point
	};

	// Creates the Vertex Attribute Pointer for the screen coordinates
	const GLuint floatsPerVertex = 3; // Number of coordinates per vertex
	const GLuint floatsPerNormal = 3;  // (r, g, b, a)
	const GLuint floatsPerUV = 2;
	// Strides between sets of attribute data
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

	m_numVerts = vertices.size() / (floatsPerVertex + floatsPerNormal + floatsPerUV);

	m_vao.bind();
	m_vbo.createVBO(vertices, vertices.size() * sizeof(float));
	m_vao.linkVBO(m_vbo, 3, 3, 2, stride);
	m_vao.unbind();
}


/*
	createTextures() allows an object to use up to 5 different image textures.
*/
void Mesh::createTexture(int count, const char* tex1Name, const char* tex2Name, const char* tex3Name, const char* tex4Name, const char* tex5Name)
{
	m_texture.loadTexture(count, tex1Name, tex2Name, tex3Name, tex4Name, tex5Name);
}

/*
	scaleMesh() is a mutator for the scale matrix
*/
void Mesh::scaleMesh(glm::vec3 scale)
{
	m_scale = scale;
}

/*
	rotateMesh() is a mutator for the rotation matrix
*/
void Mesh::rotateMesh(glm::vec3 rotation)
{
	m_rotation = rotation;
}

/*
	translateMesh() is a mutator for the translation matrix
*/
void Mesh::translateMesh(glm::vec3 translation)
{
	m_translation = translation;
}

void Mesh::scaleTexture(glm::vec2 scale)
{
	m_UVScale = scale;
}

/*
	Acessor for the model matrix
*/
glm::mat4 Mesh::getModelMatrix()
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translation) * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), m_rotation) * glm::scale(glm::mat4(1.0f), m_scale);
	return model;
}


/*
	Destroys the mesh
*/
void Mesh::destroyMesh()
{
	m_vao.Delete();
}

/*
	Destroys the textures
*/
void Mesh::destroyTexture()
{
	m_texture.destroyTexture();
}