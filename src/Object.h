#pragma once
#include "Mesh.h"
#include "Material.h"

struct Object
{
	Mesh m_mesh;
	Material m_mat;

	Object(Mesh mesh, Material mat)
		: m_mesh{ mesh },
		  m_mat{ mat }
	{

	}
};