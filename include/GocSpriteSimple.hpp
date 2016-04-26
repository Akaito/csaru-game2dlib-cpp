#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

#include "GameObjectComponent.hpp"
#include "Texture.hpp" // TODO : Once a handle's in use, forward-declare needed bits instead?

//struct SDL_Renderer;

namespace CSaruGame {

class GocSpriteSimple : public GameObjectComponent {
public: // ID
	// 2XXX are 2d graphics gocs; easier debugging by module-local convention
	static const ObjId s_gocTypeId = CSARU_TYPE_ID(s_Module_Base, 2001);

private: // Data
	CSaru2d::Texture m_texture; // TODO : Use handle to texture in some manager
	SDL_Rect         m_sourceRect;
	SDL_Renderer *   m_renderer = nullptr;

public: // Construction
	GocSpriteSimple (uint32_t generation) :
		GameObjectComponent(s_Module_Base, s_gocTypeId, generation)
	{}

	~GocSpriteSimple ();

public: // Queries
	CSaru2d::Texture * GetTexture () { return &m_texture; }
	SDL_Rect &         SrcRect ()    { return m_sourceRect; }

public: // Commands
	bool LoadTextureFromFile(SDL_Renderer *, const char * path);

public: // GameObjectComponent interface
	void Render ();
};

} // namespace CSaruGame
