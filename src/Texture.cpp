#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  
#include <iostream>

/*
	File Name: Texture.cpp
	Author: Mason Shaner
	Date: 2/19/2024
	Course: CS-330
	Description: A class for loading and storing multiple image textures
*/

Texture::Texture()
{

}

Texture::~Texture()
{
	glGenTextures(1, textures);
}

void Texture::loadTexture(int count, const char* tex1Name, const char* tex2Name, const char* tex3Name, const char* tex4Name, const char* tex5Name)
{
	// Push the filenames into an array
	fileNames[0] = tex1Name;
	fileNames[1] = tex2Name;
	fileNames[2] = tex3Name;
	fileNames[3] = tex4Name;
	fileNames[4] = tex5Name;

	// loading data
	int width, height, channels;
	unsigned char* image;

	// create an array for the texture objects
	glGenTextures(count, textures);

	// Load the textures into the array
	for (int i = 0; i < count; ++i)
	{
		stbi_set_flip_vertically_on_load(true);
		image = stbi_load(fileNames[i], &width, &height, &channels, 0);

		if (image)
		{
			// Bind the current texture
			glBindTexture(GL_TEXTURE_2D, textures[i]);

			// set the texture wrapping parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// set texture filtering parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// 3 channels = RGB 4 channels = RGBA
			if (channels == 3)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			}
			else if (channels == 4)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}
			else
			{
				std::cout << "Not implemented to handle image with " << channels << " channels" << std::endl;
			}

			// Create the mipmaps and free the image
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(image);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void Texture::bind(GLuint pos)
{
	glBindTexture(GL_TEXTURE_2D, textures[pos]);
}

void Texture::destroyTexture()
{
	glGenTextures(1, textures);
}
