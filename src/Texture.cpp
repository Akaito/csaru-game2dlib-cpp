// NOTE: Much of this early code is taken from Lazy Foo's SDL tutorials at http://lazyfoo.net/tutorials/SDL/

#include "../include/Texture.hpp"

//===========================================================================
TextureWrapper::TextureWrapper () :
	m_texture(nullptr),
	m_width(0),
	m_height(0)
{}

//===========================================================================
TextureWrapper::~TextureWrapper () {
	Free();
}

//===========================================================================
bool TextureWrapper::LoadFromFile (const char * path, bool colorKeying, uint8_t r, uint8_t g, uint8_t b) {

	Free();

	SDL_Surface * tempSurface = IMG_Load(path);
	if (!tempSurface) {
		printf("SDL_image failed to load {%s}.  %s\n", path, IMG_GetError());
		return false;
	}

	// Have to set the color key (transparent color) on the surface before creating a texture from it.
	if (colorKeying) {
		SDL_SetColorKey(
			tempSurface,
			SDL_TRUE /* enable/disable color key */,
			SDL_MapRGB(tempSurface->format, r, g, b)
		);
	}

	m_texture = SDL_CreateTextureFromSurface(g_renderer, tempSurface);
	if (!m_texture) {
		printf("SDL failed to create a texture from surface for {%s}.  %s\n", path, SDL_GetError());
		SDL_FreeSurface(tempSurface);
		return false;
	}

	m_width  = tempSurface->w;
	m_height = tempSurface->h;

	SDL_FreeSurface(tempSurface);

	return m_texture != nullptr;

}

//===========================================================================
void TextureWrapper::Free () {
	if (!m_texture)
		return;

	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	m_width   = 0;
	m_height  = 0;
}

//===========================================================================
void TextureWrapper::Render (
	unsigned          x,
	unsigned          y,
	const SDL_Rect *  srcRect,
	double            rotDegrees,
	const SDL_Point * rotCenter,
	SDL_RendererFlip  flip
) const {

	SDL_Rect destRect = { int(x), int(y), int(m_width), int(m_height) };
	if (srcRect) {
		destRect.w = srcRect->w;
		destRect.h = srcRect->h;
	}

	SDL_RenderCopyEx(g_renderer, m_texture, srcRect, &destRect, rotDegrees, rotCenter, flip);

}

