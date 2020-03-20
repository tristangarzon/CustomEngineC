#ifndef _SCENEENVIRONMENT_H
#define _SCENEENVIRONMENT_H

#include <memory>
#include <vector>
#include "Vector.h"

namespace GAME {

	using namespace MATH;

	class SceneEnvironment {
	private:

		SceneEnvironment() {};
		~SceneEnvironment() {};

	public:
		SceneEnvironment(const SceneEnvironment&) = delete;
		SceneEnvironment(SceneEnvironment&&) = delete;
		SceneEnvironment& operator=(const SceneEnvironment&) = delete;
		SceneEnvironment& operator=(SceneEnvironment&&) = delete;

	private:

		Vec3 light;

		///std::unique_ptr is a smart pointer that destroys the object it points to when the unique_ptr goes out of scope.
		static std::unique_ptr<SceneEnvironment> instance;

		/// Since my destructor is private the template std::unique_ptr needs access to it so I made it a friend.
		/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
		/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
		friend std::default_delete<SceneEnvironment>;


	public:
		static SceneEnvironment* getInstance();
		const Vec3& getLight() { return static_cast<const Vec3&>(light); }
		void setLight(const Vec3& lightPos) { light = lightPos; }
	};
}

#endif