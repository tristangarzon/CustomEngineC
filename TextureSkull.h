#ifndef TextureSkull_H
#define TextureSkull_H
#include <GL/glew.h>
#include "Model.h"

namespace GAME {

/// Forward declarations;
class Shader; 
class QuadSphere;

class TextureSkull :public Model {
public:
	TextureSkull();


	TextureSkull(const TextureSkull&) = delete;
	TextureSkull(TextureSkull&&) = delete;
	TextureSkull& operator = (const TextureSkull&) = delete;
	TextureSkull& operator = (TextureSkull&&) = delete;

	virtual bool OnCreate() ;
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix) const;
	virtual ~TextureSkull();

	void SetLightPos(const Vec3& );
private:
             
	Shader *shader;
	GLuint vbo;
	GLuint vao;
	GLuint texture0;
	GLint verticiesID;
	GLint normalsID;
	GLint uvCoordsID;
	GLuint texture0ID;
	GLint projectionMatrixID;
	GLint modelViewMatrixID;
	GLint normalMatrixID;
	GLint lightPosID;
	Vec3 lightPos;
};
}
#endif
