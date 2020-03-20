/// A simple subdivided cube - SSF
#include <vector>
#include "Vector.h"

using namespace MATH;
namespace GAME {


class QuadSphere{
private:
	unsigned int numVertices;
	unsigned int index;
	std::vector<Vec3> verticies;
	std::vector<Vec3> normals;
	std::vector<Vec2> texCoords;
	
public:
	QuadSphere(int numSubDivisions, bool smooth_);
	~QuadSphere();

	inline int getNumVertices() { return numVertices; }
	inline std::vector<Vec3> & getVerticies() { return verticies; } 
	inline std::vector<Vec3> & getNormals() { return normals; } 
	inline std::vector<Vec2> & getTexCoords() { return texCoords; } 
	

	/// C11 Delete these possible default constructors and operators 
	QuadSphere(const QuadSphere&) = delete;
	QuadSphere(QuadSphere &&) = delete;
	QuadSphere& operator=(const QuadSphere &) = delete;
	QuadSphere& operator=(QuadSphere &&) = delete;

	
protected:
	void loadFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d);
	void divideFace(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int count);
	void sphericalNormals();
};


}
