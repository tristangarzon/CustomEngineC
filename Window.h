#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

namespace GAME {
	class Window {
	public:
		Window();
		~Window();

		/// C11 precautions delete these non-needed default constructors and operators
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator = (const Window&) = delete;
		Window& operator = (Window&&) = delete;
		
		bool OnCreate();
		void OnDestroy();
		
		void setWindowSize(const int Width_, const int Height_);
		void ToggleFullScreen();
		
		int getWidth() const;
		int getHeight() const;
		inline SDL_Window* getSDLWindow(){ return windowPtr;}
	protected:
		void GetInstalledOpenGLInfo();
	private:
		SDL_Window* windowPtr;
		SDL_GLContext glContext;
		SDL_Rect winRect;
		bool isInitialized;
		bool isFullScreen;
	};
}

#endif