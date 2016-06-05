#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

#include "GameObjectComponent.hpp"
#include "Texture.hpp" // TODO : Once a handle's in use, forward-declare needed bits instead?

//struct SDL_Renderer;

namespace CSaruGame {

class GocSpriteSimple : public GameObjectComponent {
public: // ID
	// 2XXX are 2d graphics gocs; easier debugging by module-local convention
	static const ObjId s_gocTypeId = CSARU_TYPE_ID(s_Module_Base, 0x2001);

private: // Data
	CSaru2d::Texture m_texture; // TODO : Use handle to texture in some manager
	SDL_Rect         m_sourceRect;
	SDL_Renderer *   m_renderer = nullptr;
	SDL_RendererFlip m_flip     = SDL_FLIP_NONE;

public: // Construction
	GocSpriteSimple (uint32_t generation = 0) :
		GameObjectComponent(s_Module_Base, s_gocTypeId, generation)
	{}

	~GocSpriteSimple ();

public: // Queries
	CSaru2d::Texture * GetTexture () { return &m_texture; }
	SDL_Rect &         GetSrcRect () { return m_sourceRect; }

public: // Commands
	void SetGeneration (uint32_t generation) {
		m_id =
			(m_id & (CSARU_MODULE_MASK | CSARU_TYPE_MASK)) |
			(generation & CSARU_GENERATION_MASK);
	}
	bool LoadTexture(SDL_Renderer *, SDL_RWops *);
	void SetFlip (SDL_RendererFlip);

public: // GameObjectComponent interface
	void Render ();
};

} // namespace CSaruGame

