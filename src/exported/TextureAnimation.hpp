#pragma once

#ifdef WIN32
#	include <SDL.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#endif


namespace CSaru2d {

class Texture;

class TextureAnimation {
private:
	static const unsigned s_maxFrames = 32;

	unsigned m_frameCount = 0;
	SDL_Rect m_srcRects[s_maxFrames];
	unsigned m_frameDurationMs[s_maxFrames];

public:
	TextureAnimation ();

	// Queries
	unsigned         GetFrameCount () const { return m_frameCount; }
	const SDL_Rect & GetSrcRect (unsigned index) const;
	unsigned         GetDurationMs (unsigned index) const;

	// Commands
	void SetSrcRect (unsigned index, const SDL_Rect & rect);
	void SetFrameDuration (unsigned index, unsigned milliseconds);
};

} // namespace CSaru2d

