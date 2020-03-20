#include "Trackball.h"
#include <GL/glew.h> /// I don't like this and its my code see below
#include "VMath.h"
#include "MMath.h"

using namespace GAME;
using namespace MATH;

/// The math for this was taken from www.khronos.org/opengl/wiki/Object_Mouse_Trackball///
Trackball* Trackball::instance(nullptr);


Trackball* Trackball::getInstance() {
	if (instance == nullptr) {
		/// I originally set the unique_ptr to be null in the constructor - 
		/// reset() sets the new address
		instance = new Trackball();
	}
	return instance;
}

Trackball::Trackball() {
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	setWindowDimensions(viewport[2], viewport[3]);
	mouseDown = false;
}

Trackball::~Trackball() {}

void Trackball::setWindowDimensions(int w, int h) {
	invNDC = MMath::inverse(MMath::viewportNDC(w, h));
}

void Trackball::onLeftMouseDown(int x, int y) {
	beginV = getMouseVector(x, y);
	mouseDown = true;
}

void Trackball::onLeftMouseUp(int x, int y) {
	mouseDown = false;
}

void Trackball::onMouseMove(int x, int y) {
	if (mouseDown == false) return;
	endV = getMouseVector(x, y);
	float cosAngle = VMath::dot(beginV, endV);
	float angle = acos(cosAngle) * 180.0f / M_PI; /// acos() returns radians must convert to degrees
	Vec3 rotAxis = VMath::cross(beginV, endV);

	mouseRotationMatrix = MMath::rotate(angle, rotAxis) * mouseRotationMatrix;
	/// reset for the next mousemove
	beginV = endV;
}

const Vec3 Trackball::getMouseVector(int x, int y) {
	/// static_cast if the new way of type casting since c11
	Vec3 mousePosition(static_cast<float>(x), static_cast<float>(y), 0.0f);
	Vec3 v = invNDC * mousePosition;
	float xSquared = v.x * v.x;
	float ySquared = v.y * v.y;
	if (xSquared + ySquared <= 0.5f) {
		v.z = sqrt(1.0f - (xSquared + ySquared));
	}
	else {
		v.z = 0.5f / sqrt(xSquared + ySquared);
		v = VMath::normalize(v);
	}
	return v;
}

