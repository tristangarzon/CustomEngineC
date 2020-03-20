#include "SkyBox.h"

using namespace GAME;

	bool SkyBox::OnCreate()
	{
		//ObjLoader obj;

		if (addModel("cube.obj") == false)
		{
			return false;
		}


		meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));


		SDL_Surface *textureSurface;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		/// Wrapping and filtering options
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		textureSurface = IMG_Load(positive_x_image);
		if (textureSurface == nullptr) return false;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
		textureSurface = nullptr;

		textureSurface = IMG_Load(negative_x_image);
		if (textureSurface == nullptr) return false;
		///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, textureSurface->w, textureSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
		textureSurface = nullptr;


		textureSurface = IMG_Load(positive_y_image);
		if (textureSurface == nullptr) return false;
		///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
		textureSurface = nullptr;

		textureSurface = IMG_Load(negative_y_image);
		if (textureSurface == nullptr) return false;
		///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, textureSurface->w, textureSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
		textureSurface = nullptr;


		textureSurface = IMG_Load(positive_z_image);
		if (textureSurface == nullptr) return false;
		///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
		textureSurface = nullptr;


		textureSurface = IMG_Load(negative_z_image);
		if (textureSurface == nullptr) return false;
		///mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, textureSurface->w, textureSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE, textureSurface->pixels);
		SDL_FreeSurface(textureSurface);
		textureSurface = nullptr;



		skyBoxShader = new Shader("skyboxVert.glsl", "skyboxFrag.glsl", 1, 0, "vVertex");
		projectionMatrixID = glGetUniformLocation(skyBoxShader->getProgram(), "projectionMatrix");
		/// You may prefer to send the view and model matrices separately 
		modelViewMatrixID = glGetUniformLocation(skyBoxShader->getProgram(), "modelViewMatrix");
		textureID = glGetUniformLocation(skyBoxShader->getProgram(), "cubeTexture");
		return true;


	}


