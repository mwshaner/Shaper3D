#include "Renderer.h"


/*
	File Name: Renderer.cpp
	Author: Mason Shaner
	Date: 2/21/2024
	Course: CS-330
	Description: A class for rendering meshes and lights
*/

//Light colors
glm::vec3 white(1.0f, 1.0f, 1.0f);
glm::vec3 red(1.0f, 0.0f, 0.0f);
glm::vec3 green(0.0f, 1.0f, 0.0f);
glm::vec3 blue(0.0f, 0.0f, 1.0f);
glm::vec3 yellow(1.0f, 1.0f, 0.6f);

// positions of the point lights
std::vector<glm::vec3> pointLightPositions =
{
	glm::vec3(10.0f,  10.0f,  0.0f),
	glm::vec3(-1.0f, 10.0f, -6.0f)
};

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::drawMesh(Mesh &mesh, Shader& shader, Camera& camera, Material &material)
{
	// Use the main shader program
	shader.bind();
	const glm::vec3 cameraPosition = camera.Position;
	shader.setFloat3("viewPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);
	shader.setFloat("material.shininess", 32.0f);

	// set the shader uniforms
	shader.setVec2("uvScale", mesh.getUVscale());
	shader.setMat4("model", mesh.getModelMatrix());
	shader.setVec3("material.ambient", material.ambient);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setFloat("material.shininess", material.shininess);

	// different meshes use different drawing techniques
	switch (mesh.shapeType)
	{
	case(CYLINDER):
		mesh.texture.bind(0);
		mesh.vao.bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh.numVerticesSide);	  //sides
		mesh.texture.bind(1);
		glDrawArrays(GL_TRIANGLE_FAN, mesh.numVerticesSide, mesh.numVerticesTopAndBottom);	  //top
		glDrawArrays(GL_TRIANGLE_FAN, mesh.numVerticesSide + mesh.numVerticesTopAndBottom, mesh.numVerticesTopAndBottom);	  //bottom
		break;

	case(CUBE):
		mesh.texture.bind(0);
		mesh.vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, mesh.numVerts);
		glBindVertexArray(0);
		break;

	case(PYRAMID):
		mesh.texture.bind(0);
		mesh.vao.bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh.numVerts);
		break;

	case(PLANE):
		mesh.texture.bind(0);
		mesh.vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, mesh.numVerts);
		break;
	}
}


void Renderer::drawLights(Shader &shader, Camera &camera)
{
	// directional light
	shader.setVec3("dirLight.direction", glm::vec3(-0.2, -2.0f, -1.9f));
	shader.setVec3("dirLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setVec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
	shader.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));

	// Point light 1
	shader.setVec3("pointLights[0].position", pointLightPositions[0]);
	shader.setVec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader.setVec3("pointLights[0].diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setVec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLights[0].constant", 1.0f);
	shader.setFloat("pointLights[0].linear", 0.09f);
	shader.setFloat("pointLights[0].quadratic", 0.032f);
	shader.setVec3("pointLights[0].color", yellow);

	//// Point light 2
	shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	shader.setVec3("pointLights[1].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader.setVec3("pointLights[1].diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setVec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLights[1].constant", 1.0f);
	shader.setFloat("pointLights[1].linear", 0.09f);
	shader.setFloat("pointLights[1].quadratic", 0.032f);
	shader.setVec3("pointLights[1].color", yellow);
}

