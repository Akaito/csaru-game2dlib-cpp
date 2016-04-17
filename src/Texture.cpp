// NOTE: Much of this early code is taken from Lazy Foo's SDL tutorials at http://lazyfoo.net/tutorials/SDL/

#include "../include/Texture.hpp"


namespace CSaru2d {

//===========================================================================
Texture::Texture () :
	m_texture(nullptr),
	m_width(0),
	m_height(0)
{}

//===========================================================================
Texture::~Texture () {
	Free();
}

//===========================================================================
void Texture::Free () {
	if (!m_texture)
		return;

	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
	m_width   = 0;
	m_height  = 0;
}

//===========================================================================
bool Texture::LoadFromFile (
	SDL_Renderer * renderer,
	const char * path,
	bool colorKeying,
	uint8_t r,
	uint8_t g,
	uint8_t b
) {

	Free();

	SDL_Surface * tempSurface = IMG_Load(path);
	if (!tempSurface) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image failed to load {%s}.  %s\n", path, IMG_GetError());
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

	m_texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!m_texture) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL failed to create a texture from surface for {%s}.  %s\n", path, SDL_GetError());
		SDL_FreeSurface(tempSurface);
		return false;
	}

	m_width  = tempSurface->w;
	m_height = tempSurface->h;

	SDL_FreeSurface(tempSurface);

	return m_texture != nullptr;

}

//===========================================================================
bool Texture::LoadFromRenderedText (
	SDL_Renderer * renderer,
	TTF_Font *     sdlFont,
	const char *   textureText,
	SDL_Color      textColor
) {
	// Get rid of pre-existing texture (if any)
	Free();

	// Render text surface
	SDL_Surface * textSurface = TTF_RenderText_Solid(sdlFont, textureText, textColor);
	if (!textSurface) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// Create texture from surface pixels
	m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!m_texture) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Get image dimensions
	m_width  = textSurface->w;
	m_height = textSurface->h;

	// Get rid of old surface
	SDL_FreeSurface(textSurface);
	return true;
}

//===========================================================================
void Texture::Render (
	SDL_Renderer *    renderer,
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

	SDL_RenderCopyEx(renderer, m_texture, srcRect, &destRect, rotDegrees, rotCenter, flip);

}

//===========================================================================
void Texture::SetAlpha (uint8_t a) {
	SDL_SetTextureAlphaMod(m_texture, a);
}

//===========================================================================
void Texture::SetBlendMode (SDL_BlendMode blendMode) {
	SDL_SetTextureBlendMode(m_texture, blendMode);
}

//===========================================================================
void Texture::SetColor (uint8_t r, uint8_t g, uint8_t b) {
	SDL_SetTextureColorMod(m_texture, r, g, b);
}

} // namespace CSaru2d

