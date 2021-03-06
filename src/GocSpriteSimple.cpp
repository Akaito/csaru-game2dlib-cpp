#include <cml/cml.h>

#include "exported/GameObject.hpp"
#include "exported/GocSpriteSimple.hpp"

namespace CSaruGame {

//==============================================================================
GocSpriteSimple::~GocSpriteSimple () {
	// (texture frees itself on destruction)
	m_renderer = nullptr;
}

//==============================================================================
bool GocSpriteSimple::LoadTexture (SDL_Renderer * renderer, SDL_RWops * rwOps) {
	m_renderer = renderer;

	// note: can add color-keying, etc. args here
	if (!m_texture.Load(m_renderer, rwOps)) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "GocSpriteSimple failed to load given texture.");
		return false;
	}
	m_texture.SetBlendMode(SDL_BLENDMODE_BLEND); // lazy assumption about simple sprites
	return true;
}

//==============================================================================
void GocSpriteSimple::Render () {
	if (!m_renderer)
		return;

	GameObject * owner = GetOwner();
	if (!owner)
		return;

	const cml::vector3f & pos = owner->GetTransform().GetPosition();
	m_texture.Render(
		m_renderer,
		pos[0],
		pos[1],
		&m_sourceRect,
		owner->GetTransform().GetRotation() * 180.0f / M_PI,
		nullptr /* rotCenter */,
		m_flip
	);
}

//==============================================================================
void GocSpriteSimple::SetFlip (SDL_RendererFlip flip) {
	m_flip = flip;
}

} // namespace CSaruGame

