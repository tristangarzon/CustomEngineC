#include "Mesh.h"

using namespace MATH;

Mesh::Mesh(GLenum drawmode_, std::vector<Vec3> verticies_, std::vector<Vec3> normals_, std::vector<Vec2> uvCoords_ ){
	drawmode = drawmode_;
    this->vertices = verticies_;
    this->normals = normals_;
    this->uvCoords = uvCoords_;
    this->setupMesh();
}

void Mesh::setupMesh() {
	#define VERTEX_LENGTH 	(vertices.size() * (sizeof(Vec3)))
	#define NORMAL_LENGTH 	(vertices.size() * (sizeof(Vec3)))
	#define TEXCOORD_LENGTH (vertices.size() * (sizeof(Vec2)))
	
    /// Create and initialize vertex buffer object VBO
    glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
    glGenBuffers(1, &vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH + TEXCOORD_LENGTH , NULL, GL_STATIC_DRAW );

	 /// assigns the addr of "points" to be the beginning of the array buffer "sizeof(points)" in length
    glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_LENGTH, &vertices[0] );
	/// assigns the addr of "normals" to be "sizeof(points)" offset from the beginning and "sizeof(normals)" in length  
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH, NORMAL_LENGTH, &normals[0] );
	/// assigns the addr of "texCoords" to be "sizeof(points) + sizeof(normals)" offset from the beginning and "sizeof(texCoords)" in length  
    glBufferSubData(GL_ARRAY_BUFFER, VERTEX_LENGTH + NORMAL_LENGTH , TEXCOORD_LENGTH , &uvCoords[0]);
	
	int verticiesID = 0;
	int normalsID = 1;
	int uvCoordsID = 2;

	glEnableVertexAttribArray(verticiesID);
	glVertexAttribPointer(verticiesID, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(0) );
	glEnableVertexAttribArray(normalsID);
	glVertexAttribPointer(normalsID, 3, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH) );
	glEnableVertexAttribArray(uvCoordsID);
	glVertexAttribPointer(uvCoordsID, 2, GL_FLOAT, GL_FALSE, 0,(GLvoid*)(VERTEX_LENGTH + NORMAL_LENGTH) );

	glBindBuffer(GL_ARRAY_BUFFER,0); /// Unbinds the buffer by setting it to zero   
	glBindVertexArray(0); // Disable the VBO  
	glEnableVertexAttribArray(0); // Disable the VAO

	#undef VERTEX_LENGTH
	#undef NORMAL_LENGTH
	#undef TEXCOORD_LENGTH
}  


void Mesh::Render() const{
	glBindVertexArray(vao);
	glDrawArrays(drawmode, 0, vertices.size());
	glEnableVertexAttribArray(0); // Disable the VAO
}
