#include <GL/glew.h>
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "TextureSkull.h"
#include "Trackball.h"

using namespace GAME;
using namespace MATH;

Scene0::Scene0(class Window& windowRef): Scene(windowRef) {
	textureSkull = nullptr;
	trackball = new Trackball();
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
	
}

Scene0::~Scene0(){ 
	OnDestroy();
}

bool Scene0::OnCreate() {
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	lightPos = Vec3(0.0f, 0.0f, 2.0f);
	textureSkull = new TextureSkull();
	textureSkull->SetVel(Vec3(0.0f,0.0f,0.0f));
	textureSkull->SetPos(Vec3(0.0f,0.0f,0.0f));
	return true;
}


void Scene0::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	
	projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 100.0f);

	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), 
							   Vec3(0.0f, 0.0f, 0.0f), 
							   Vec3(0.0f, 1.0f, 0.0f));	
}

void Scene0::OnDestroy(){
	/// Cleanup Assets
	if(textureSkull) delete textureSkull;
	textureSkull = nullptr;
	if(trackball) delete trackball;
	trackball = nullptr;
}

void Scene0::Update(const float deltaTime){
	textureSkull->Update(deltaTime);
}

void Scene0::Render() const{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	textureSkull->SetLightPos(viewMatrix * lightPos);
	textureSkull->Render(projectionMatrix , viewMatrix * trackball->GetMatrix4(), trackball->GetMatrix3());
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent) {
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		trackball->OnLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		trackball->OnMouseMove(SDLEvent.button.x, SDLEvent.button.y);
	}
	if (SDLEvent.type == SDL_EventType::SDL_KEYDOWN) {
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_UP] && (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT])) {
			lightPos.z += 0.1f;
			lightPos.print();
		}
		else if (state[SDL_SCANCODE_UP]) {
			lightPos.y += 0.1f;
			lightPos.print();
		}

		else if (state[SDL_SCANCODE_DOWN] && (state[SDL_SCANCODE_RSHIFT] || state[SDL_SCANCODE_LSHIFT])) {
			lightPos.z -= 0.1f;
			lightPos.print();
		}
		else if (state[SDL_SCANCODE_DOWN]) {
			lightPos.y -= 0.1f;
			lightPos.print();
		}
		else if (state[SDL_SCANCODE_LEFT]) {
			lightPos.x -= 0.1f;
			lightPos.print();
		}
		else if (state[SDL_SCANCODE_RIGHT]) {
			lightPos.x += 0.1f;
			lightPos.print();
		}
	}
}
		