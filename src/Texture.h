#ifndef TEXTURE_H
#define TEXTURE_H
#include <../thirdparty/glad/include/glad/glad.h>

/*
	File Name: Texture.h
	Author: Mason Shaner
	Date: 2/19/2024
	Course: CS-330
	Description: A class for loading and storing multiple image textures
*/

class Texture
{
public: 
	Texture();
	~Texture();
	void loadTexture(int count, const char* tex1Name, const char* tex2Name = "0", const char* tex3Name = "0", const char* tex4Name = "0", const char* tex5Name = "0");
	void bind(GLuint pos);
	void destroyTexture();
private:
	GLuint textures[5];
	const char* fileNames[5];
};
#endif

