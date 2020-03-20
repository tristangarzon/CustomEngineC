#ifndef TRACKBALL_H
#define	TRACKBALL_H
#include "MMath.h"

namespace GAME {	/// The trackball is part of my namespace GAME but,
	using namespace MATH;	/// needs namespace MATH to find the math functions 

	class Trackball {
	private:
		bool mouseDown;
		static Trackball *instance;
		Matrix4 mouseRotationMatrix;	/// This the final rotation matrix
		Matrix4 invNDC;			/// the inverse of the viewportNDC matrix
		Vec3 beginV, endV;		/// Begin and end points after being transformed by invNDC

	public:
		static Trackball* getInstance();
		Trackball(); /// Usual constructor
		~Trackball();/// Usual destructor
	
		Trackball(const Trackball&) = delete;
		Trackball(Trackball&&) = delete;
		Trackball& operator=(const Trackball&) = delete;
		Trackball& operator=(Trackball&&) = delete;

		///Any time the window dimensions change like stretching it we will
		/// need to rebuild the invNDC matrix
		void setWindowDimensions(int w, int h);

		void onLeftMouseDown(int x, int y);
		void onLeftMouseUp(int x, int y);
		void onMouseMove(int x, int y);

		/// Return the 4x4 rotational matrix
		const Matrix4 getMatrix4() const { return mouseRotationMatrix; }

		/// Return the 3x3 rotational matrix, after all a rotational matrix is a 3x3!
		const Matrix3 getMatrix3() const { return Matrix3(mouseRotationMatrix); }

	private:
		/// Just a helper function for internal use only thus private
		const Vec3 getMouseVector(int x, int y);
	};

}
#endif

