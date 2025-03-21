#pragma once
#include "Mesh.h"
#include "Material.h"

/*
*		   File: MeshObject.h
*		   Author: Mason Shaner
*		   Date: 3/20/2025
*		   Description: MeshOject type contains Mesh and Material members
*/

struct MeshObject
{
	Mesh m_mesh;
	Material m_mat;

	MeshObject(Mesh& mesh, Material& mat)
		: m_mesh{ mesh },
		  m_mat{ mat }
	{

	}
};