#pragma once

// Inspirations/sources referred to:
// - lazyfoo's SDL2 tutorials.
// - Allegro
// - SFML

#ifdef WIN32
#	include <SDL.h>
#	include <SDL_image.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_image.h>
#endif

namespace CSaru2d {

class Texture {
private:
	// Data
	SDL_Texture * m_texture;
	unsigned      m_width;
	unsigned      m_height;

public:
	Texture ();
	~Texture ();

	// Accessors
	inline unsigned GetWidth () const  { return m_width;  }
	inline unsigned GetHeight () const { return m_height; }

	// Methods
	bool LoadFromFile (
		SDL_Renderer * renderer,
		const char *   filepath,
		bool           colorKeying = false,
		uint8_t        r           = 0xFF,
		uint8_t        g           = 0x00,
		uint8_t        b           = 0xFF
	)
	bool LoadFromRenderedText (
		SDL_Renderer * renderer,
		TTF_Font *     sdlFont,
		const char *   textureText,
		SDL_Color      textColor
	);

	void Free ();

	void SetColor (uint8_t r, uint8_t g, uint8_t b);
	void SetAlpha (uint8_t a);
	void SetBlendMode (SDL_BlendMode blendMode);

	void Render (
		SDL_Renderer *    renderer,
		unsigned          x,
		unsigned          y,
		const SDL_Rect *  srcRect    = nullptr,
		double            rotDegrees = 0.0,
		const SDL_Point * rotCenter  = nullptr,
		SDL_RendererFlip  flip       = SDL_FLIP_NONE
	) const;
};

} // namespace CSaru2d

