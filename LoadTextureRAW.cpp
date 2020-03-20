#include <stdio.h>
#include <GL/glew.h>
#include "LoadTextureRAW.h"

/// load an RGB Adobe Photoshop .RAW file as a texture
GLuint loadTextureRAW(const char * filename, int width, int height) {
	GLuint texture = NULL;
	GLubyte * data;
	FILE * file;

	/// open texture data file
	fopen_s(&file, filename, "rb");
	if (file == NULL) return 0;

	/// allocate a buffer to hold the image (assume 3 channel RGB data)
	data = new GLubyte[width * height * 3];
	//data = (GLubyte*)malloc( width * height * 3 ); /// Old C-style allocation

	/// read texture data - just that easy 
	fread(data, width * height * 3, 1, file);
	fclose(file); /// all done close the file 


				  /// Now for the OpenGL stuff
				  /// This call generates a unique name (uint) for a texture (or even an array of textures)
	glGenTextures(1, &texture);

	/// This informs the machine what type of texture the previous call's name refers to.
	/// In this case I want a 2D texture 
	glBindTexture(GL_TEXTURE_2D, texture);

	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/// This connects the image date with the named texture. Includes the format of the image data
	/// ours is interleaved, meaning rgb-rgb-rgb instead of rrr-ggg-bbb 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	/// de-allocate the buffer
	delete[] data;

	//free data; /// Old C-style de-allocation

	return texture;	/// return the index
}