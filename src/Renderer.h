#ifndef RENDERER_H
#define RENDERER_H
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include "shader.h"
#include "Texture.h"
#include "camera.h"
#include "Material.h"

/*
	File Name: Renderer.h
	Author: Mason Shaner
	Date: 2/21/2024
	Course: CS-330
	Description: A class for rendering meshes and lights
*/

class Renderer
{
public:
	Renderer();
	~Renderer();
	void drawLights(Shader &shader, Camera &camera);
	void drawMesh(Mesh &mesh, Shader &shader, Camera &camera, Material &material);
};

#endif

