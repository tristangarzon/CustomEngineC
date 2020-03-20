
#include "VMath.h"
using namespace MATH;
 
Vec3 VMath::reflect(const Vec3 &v, const Vec3 &n){
	return ((2.0f * dot(v, n)) * n - v);
}

Vec3 VMath::reflect(const Vec3 &v, const Plane &n) {
	return ((2.0f * dot(v, n)) * n - v);
}

float VMath::distance(const Vec3 &a, const Vec3 &b){
	Vec3 r  = a - b;
	return(mag(r));
}

float VMath::distance(const Vec3 &v, const Plane &p){
	return v.x*p.x + v.y*p.y + v.z*p.z - p.d;
}

float VMath::distance(const Sphere &s, const Plane &p){
	return distance((Vec3)s,p) - s.r;
}
