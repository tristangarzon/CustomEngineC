#ifndef QUADSPHERE_H
#define QUADSPHERE_H
#include "QuadSphere.h"
#include "VMath.h"


using namespace GAME;

QuadSphere::QuadSphere(int numSubDivisions, bool smooth_) {
	numVertices = 6 * int(pow(4.0, numSubDivisions + 1 ) );
	index = 0;
	verticies.resize(numVertices);
	normals.resize(numVertices);
	texCoords.resize(numVertices);


	Vec3 cube[8] = {
		///Front 4
		Vec3( -0.5, -0.5,  0.5),/// Left bottom
		Vec3( -0.5,  0.5,  0.5),/// Left top
		Vec3(  0.5,  0.5,  0.5),/// Right top
		Vec3(  0.5, -0.5,  0.5),/// Right bottom
		///Back 4
		Vec3( -0.5, -0.5, -0.5),
		Vec3( -0.5,  0.5, -0.5),
		Vec3(  0.5,  0.5, -0.5),
		Vec3(  0.5, -0.5, -0.5)
	};


	int count = numSubDivisions;
	if (count > 0){
		for(int j = 0; j<8;++j){
			cube[j] = VMath::normalize(cube[j]);
		}
	}
	/// I'm using the GL_QUADS method of drawing so I'll need specify cube 1234
	divideFace( cube[1], cube[0], cube[3], cube[2], count); /// Front face
	divideFace( cube[2], cube[3], cube[7], cube[6], count); /// Right face
	divideFace( cube[3], cube[0], cube[4], cube[7], count); /// Bottom face
	divideFace( cube[6], cube[5], cube[1], cube[2], count); /// Top face
	divideFace( cube[4], cube[5], cube[6], cube[7], count); /// Back face
	divideFace( cube[5], cube[4], cube[0], cube[1], count); /// Left face

	if(smooth_) sphericalNormals();	

}

QuadSphere::~QuadSphere(){}




///////////   Utility Routines  ////////////////
///  loadFace generates one quad for each face and assigns colors to the vertices
void QuadSphere::loadFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d){
	
	Vec4 u = b - a;
	Vec4 v = c - b;
	Vec4 normal = VMath::normalize(VMath::cross(u,v));
	
	normals[index] = normal;  
	verticies[index] = a;
	texCoords[index][0] = 0.0; texCoords[index][1] = 0.0;
	index++;

	normals[index] = normal;
	verticies[index] = b;
	texCoords[index][0] = 0.0; texCoords[index][1] = 1.0;
	index++;

	normals[index] = normal;
	verticies[index] = c;
	texCoords[index][0] = 1.0; texCoords[index][1] = 1.0;
	index++;


	normals[index] = normal;
	verticies[index] = d;
	texCoords[index][0] = 1.0; texCoords[index][1] = 0.0;
	index++;
}


void QuadSphere::divideFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int count ) {
	if(count > 0){
		Vec3 v1 = VMath::normalize(a + b);
		Vec3 v2 = VMath::normalize(b + c);
		Vec3 v3 = VMath::normalize(c + d);
		Vec3 v4 = VMath::normalize(d + a);
		Vec3 vc = VMath::normalize(a + c);
		divideFace(a,v1,vc,v4, count-1);
		divideFace(v1,b,v2,vc, count-1);
		divideFace(vc,v2,c,v3, count-1);
		divideFace(v4,vc,v3,d, count-1);
	}else{
		loadFace(a, b, c, d);
	}
}
/// Since the center of the sphere is at the origin, the vector formed from the origin to the surface vertex of the sphere
/// (once normalized) would be the normal to a sphere's surface - not to the face of the polygon on that sphere! Now it looks smooth. 
void QuadSphere::sphericalNormals(){
	for (int j = 0; j < numVertices; ++j){
		normals[j] = VMath::normalize(verticies[j]);
	}
}




#endif ///QUADSPHERE_H









