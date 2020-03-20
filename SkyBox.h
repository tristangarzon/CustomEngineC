#ifndef SKYBOX_H
#define SKYBOX_H

#include "Model.h"
#include "ObjLoader.h"
#include "Shader.h"
#include <SDL.h>
#include <SDL_image.h>

namespace GAME {

class SkyBox : public Model {

	public:
		SkyBox(const char * positive_x_image, const char * negative_x_image, const char * positive_y_image, const char * negative_y_image, const char * positive_z_image, const char * negative_z_image);
		virtual ~SkyBox();

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float time);
		virtual void Render() const;

	private:
		const char * positive_x_image;
		const char * negative_x_image;
		const char * positive_y_image;
		const char * negative_y_image;
		const char * positive_z_image;
		const char * negative_z_image;
		class Shader *skyBoxShader;
		GLuint textureID;
		GLuint texture;
		GLuint projectionMatrixID;
		GLuint modelViewMatrixID;


	};
}
#endif // !SKYBOX_H