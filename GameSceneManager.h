#pragma once
#include <memory>
#include <thread>
#include "Window.h"
#include "Scene.h"


namespace GAME {

class GameSceneManager {
private:
	
	GameSceneManager();
	~GameSceneManager();

public:
	GameSceneManager(const GameSceneManager&) = delete;
	GameSceneManager(GameSceneManager&&) = delete;
	GameSceneManager& operator=(const GameSceneManager&) = delete;
	GameSceneManager& operator=(GameSceneManager&&) = delete;

private:

	/// Notice that windowInstance is a stack variable here - see the 
	/// GameSceneManager.cpp constructor for the best way to initialize it 
	Window windowInstance;
	Scene *currentScene; 


	///std::unique_ptr is a smart pointer that destroys the object it points to when the unique_ptr goes out of scope.
	static std::unique_ptr<GameSceneManager> instance;

	/// Since my destructor is private the template std::unique_ptr needs access to it so I made it a friend.
	/// However, std::default_delete is the default destruction policy used by std::unique_ptr 
	/// when no deleter is specified, therefore I'll make std::default_delete my friend as well. 
	friend std::default_delete<GameSceneManager>;

private: 
	bool isRunning;
	unsigned int frameRate; /// Frames / second


public:
	static GameSceneManager* getInstance();
	void Run(); 
	bool Initialize();
	void Update(const float deltaTime);
	void Render() const;
	void HandleEvents();
};

}