#include "../include/GocSrcRectAnimator.hpp"

#ifdef WIN32
#	include <SDL.h>
#	include <SDL_image.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_image.h>
#endif

namespace CSaruGame {

//==============================================================================
void GocSrcRectAnimator::Update (float dt) {
	SDL_assert(m_rect);
	//m_rect->w += 1;
}

} // namespace CSaruGame

