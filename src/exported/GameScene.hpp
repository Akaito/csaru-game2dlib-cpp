#pragma once

#ifdef WIN32
#	include <SDL.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#endif

#include <csaru-core-cpp/csaru-core-cpp.hpp>

namespace CSaruGame {

class GameScene {
protected:

public:
	virtual ~GameScene () {}

	virtual bool Init (int argc, const char * const argv[]) { unused(argc); unused(argv); return true; }
	virtual bool Load (SDL_Renderer *)          { return true; }
	virtual void Unload ()                      {}
	// TODO : Update instead by how many frames fit within dtms.
	virtual void Update (float dtms)            { unused(dtms); } // delta time in milliseconds
	virtual void Render (SDL_Renderer *, int screenWidth, int screenHeight) { unused(screenWidth); unused(screenHeight);}

	virtual void OnSdlEvent (const SDL_Event &) {}

	virtual bool ShouldQuit ()                  { return false; }
};

} // namespace CSaruGame

