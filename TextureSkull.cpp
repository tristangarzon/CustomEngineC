#include "TextureSkull.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "LoadTextureRAW.h"
#include <SDL_image.h>

using namespace GAME;

TextureSkull::TextureSkull():shader(nullptr) {
	OnCreate();
}

bool TextureSkull::OnCreate(){
	
	ObjLoader obj("cube.obj");
	meshes.push_back(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords));


	
	/// Create a shader with attributes
	shader = new Shader("textureVert.glsl","textureFrag.glsl",3,  0,"vVertex",   1,"vNormal",   2,"texCoords",nullptr);

	SDL_Surface *textureSurface = IMG_Load("skull_texture.jpg");
	if (textureSurface == nullptr) {
		return false;
	}
	int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	
	glGenTextures(1, &texture0ID);
	glBindTexture(GL_TEXTURE_2D, texture0ID);
	glTexImage2D(GL_TEXTURE_2D, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture0 = glGetUniformLocation(shader->getProgram(), "myTexture0");
	

	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
	modelMatrix = MMath::translate(0.0f,0.3f,0.0f);
	return true;
}


void TextureSkull::OnDestroy(){
	glDeleteBuffers(1,  &vbo);
	if(shader) delete shader;

	for(Mesh* mesh : meshes) {
		if(mesh) delete mesh;
	}	
}

void TextureSkull::Update(const float deltaTime){
	
}

void TextureSkull::SetLightPos(const Vec3& lightPos_){
	lightPos = lightPos_;
}


void TextureSkull::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix) const{
	
	glUseProgram(shader->getProgram());
	glBindTexture(GL_TEXTURE_2D, texture0ID);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix  );
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	glUniform3fv(lightPosID, 1, lightPos);
	for(Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO
}


TextureSkull::~TextureSkull(){
	OnDestroy();
}