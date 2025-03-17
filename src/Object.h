#pragma once
#include "Mesh.h"
#include "Material.h"

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