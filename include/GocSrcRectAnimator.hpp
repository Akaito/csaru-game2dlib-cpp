#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

#include "GameObjectComponent.hpp"
#include "TextureAnimation.hpp"

struct SDL_Rect;

namespace CSaruGame {

class GocSrcRectAnimator : public GameObjectComponent {
public: // ID
	// 9XXX are miscellaneous gocs; easier debugging by module-local convention
	// 92XX mostly interact with 2XXX (2d graphics) components
	static const ObjId s_gocTypeId = CSARU_TYPE_ID(s_Module_Base, 0x9201);

private: // Data
	const CSaru2d::TextureAnimation * m_animation  = nullptr;
	SDL_Rect *                        m_targetRect = nullptr;

	unsigned m_frameIndex  = 0;
	unsigned m_msThisFrame = 0;

public: // Construction
	GocSrcRectAnimator (uint32_t generation) :
		GameObjectComponent(s_Module_Base, s_gocTypeId, generation)
	{}

	~GocSrcRectAnimator ();

public: // Commands
	void Clear ();
	void SetAnimation (const CSaru2d::TextureAnimation * anim);
	void SetTargetRect (SDL_Rect * rectToAnimate) { m_targetRect = rectToAnimate; }

public: // GameObjectComponent interface
	void Update (float dt);

};

} // namespace CSaruGame

