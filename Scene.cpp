#include "Scene.h"

using namespace GAME; 
/// All this constructor does is set the windowPtr 
Scene::Scene(Window& windowRef): windowPtr(&windowRef) {}
Scene::~Scene() {}