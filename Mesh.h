#ifndef MESH_H
#define MESH_H
#include <Vector>
#include <GL/glew.h>
#include "Vector.h"
#include "Matrix.h"


using namespace MATH;

class Mesh {
    public:
		GLenum drawmode;
        std::vector<Vec3> vertices;
		std::vector<Vec3> normals;
		std::vector<Vec2> uvCoords;
        std::vector<GLuint> indices; 
      
        Mesh(GLenum drawmode_,  std::vector<Vec3>, std::vector<Vec3>, std::vector<Vec2> );
        void Render() const;
    private: 
        GLuint vao, vbo;
        void setupMesh();
};  

#endif