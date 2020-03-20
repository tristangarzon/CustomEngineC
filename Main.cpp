#include <iostream>
#include "GameSceneManager.h"
#include "Debug.h"

using namespace GAME;

int main(int argc, char* argcs[]) {


	/// c11: This is evaluated at compile time, if void* != 4 then
	/// this must be a 64-bit build - just a quick test
	static_assert(sizeof(void*) == 4, "This program is not ready for 64-bit build");


	Debug::Init();
	try{ 
		GameSceneManager::getInstance()->Run();
	}catch(std::string fatalError){
		std::cout << "Fatal error: " << fatalError << std::endl;
	}catch(...) {
		std::cout << "Unknown Fatal error: " << std::endl;
	} 
	exit(0);
}