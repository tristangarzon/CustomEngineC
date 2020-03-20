#include <GL/glew.h>
#include <SDL.h>
#include "Scene2.h"
#include <iostream>
#include "MMath.h"
#include "SkyBox.h"
#include "ReflectionSkull.h"
#include "Trackball.h"

using namespace GAME;
using namespace MATH;

Scene2::Scene2(class Window& windowRef):Scene(windowRef), skyBox(nullptr) {
	
	
}

Scene2::~Scene2(){ 
	OnDestroy();
}

bool Scene2::OnCreate() {
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());
	trackball = new Trackball();
	
	/// Load Assets: as needed 
	
	skyBox = new SkyBox("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");
	if (skyBox->OnCreate() == false) return false;


	lightPos = Vec3(0.0f, 10.0f, -10.0f);
	reflectionSkull = new ReflectionSkull();


	return true;
}

static float z = 8.0f;
void Scene2::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	
	projectionMatrix = MMath::perspective(45.0f, aspect, 0.75f, 100.0f);

	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, z), 
							   Vec3(0.0f, 0.0f, 0.0f), 
							   Vec3(0.0f, 1.0f, 0.0f));

	
}

void Scene2::OnDestroy(){
	/// Cleanup Assets
	if(skyBox) delete skyBox;
	skyBox = nullptr;

	if (reflectionSkull) delete reflectionSkull;
	reflectionSkull = nullptr;

	if(trackball) delete trackball;
	trackball = nullptr;
}

void Scene2::Update(const float deltaTime){
	skyBox->Update(deltaTime);
}

void Scene2::Render() const{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	/// Draw your scene here
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	skyBox->Render(projectionMatrix , trackball->GetMatrix4(), trackball->GetMatrix3());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	reflectionSkull->SetLightPos(lightPos);
	reflectionSkull->Render(projectionMatrix, viewMatrix * trackball->GetMatrix4() , trackball->GetMatrix3());

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
	
}

void Scene2::HandleEvents(const SDL_Event& SDLEvent){
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT])) {
		trackball->OnLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}else if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN){
		trackball->OnLeftMouseDown(SDLEvent.button.x,SDLEvent.button.y);
	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION && 
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		trackball->OnMouseMove(SDLEvent.button.x,SDLEvent.button.y);
	}
	
			
}