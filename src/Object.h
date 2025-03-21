#pragma once
#include "Mesh.h"
#include "Material.h"

/*
*		   File: meshObject.h
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description: Main application for creating an OpenGL window and rendering different mesh objects
*/


struct meshObject
{
	Mesh m_mesh;
	Material m_mat;

	meshObject(Mesh& mesh, Material& mat)
		: m_mesh{ mesh },
		  m_mat{ mat }
	{

	}
};