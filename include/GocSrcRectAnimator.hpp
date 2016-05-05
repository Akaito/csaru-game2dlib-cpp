#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

#include "GameObjectComponent.hpp"

struct SDL_Rect;

namespace CSaruGame {

class GocSrcRectAnimator : public GameObjectComponent {
public: // ID
	// 9XXX are miscellaneous gocs; easier debugging by module-local convention
	// 92XX mostly interact with 2XXX (2d graphics) components
	static const ObjId s_gocTypeId = CSARU_TYPE_ID(s_Module_Base, 0x9201);

private: // Data
	SDL_Rect * m_rect;

public: // Construction
	GocSrcRectAnimator (uint32_t generation) :
		GameObjectComponent(s_Module_Base, s_gocTypeId, generation)
	{}

	~GocSrcRectAnimator ()            { m_rect = nullptr; }

public: // Commands
	void SetSrcRect (SDL_Rect * rect) { m_rect = rect; }

public: // GameObjectComponent interface
	void Update (float dt);

};

} // namespace CSaruGame

