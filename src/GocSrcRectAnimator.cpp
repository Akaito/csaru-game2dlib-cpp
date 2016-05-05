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
GocSrcRectAnimator::~GocSrcRectAnimator () {
	Clear();
}

//==============================================================================
void GocSrcRectAnimator::Clear () {
	m_animation   = nullptr;
	m_targetRect  = nullptr;
	m_frameIndex  = 0;
	m_msThisFrame = 0;
}

//===========================================================================
void GocSrcRectAnimator::SetAnimation (const CSaru2d::TextureAnimation * anim) {

	m_animation   = anim;

	if (m_animation) {
		const unsigned frameCount = m_animation->GetFrameCount();
		if (frameCount)
			m_frameIndex %= m_animation->GetFrameCount();
	}

}

//==============================================================================
void GocSrcRectAnimator::Update (float dt) {

	if (!m_animation || !m_targetRect)
		return;

	const unsigned frameCount = m_animation->GetFrameCount();
	if (frameCount <= 1) {
		m_frameIndex = 0;
		return;
	}

	m_msThisFrame += unsigned(dt * 1000.0f);
	if (m_msThisFrame < m_animation->GetDurationMs(m_frameIndex))
		return;

	m_frameIndex  = (m_frameIndex + 1) % frameCount;
	*m_targetRect = m_animation->GetSrcRect(m_frameIndex);

}

} // namespace CSaruGame

