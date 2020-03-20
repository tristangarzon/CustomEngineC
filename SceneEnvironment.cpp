#include "SceneEnvironment.h"

namespace GAME {

	std::unique_ptr<GAME::SceneEnvironment> GAME::SceneEnvironment::instance(nullptr);


	GAME::SceneEnvironment* SceneEnvironment::getInstance()
	{
		if (instance.get() == nullptr) {
			/// I originally set the unique_ptr to be null in the constructor - 
			/// reset() sets the new address
			instance.reset(new SceneEnvironment());
		}
		return instance.get();
	}
}
