#include "../include/TextureAnimation.hpp"

#include <csaru-core-cpp/csaru-core-cpp.h>

namespace CSaru2d {

//===========================================================================
TextureAnimation::TextureAnimation () {
	CSaruCore::SecureZero(m_srcRects, sizeof(m_srcRects));
}

//===========================================================================
const SDL_Rect & TextureAnimation::GetSrcRect (unsigned index) const {
	SDL_assert_release(index < m_frameCount);

	return m_srcRects[index];
}

//===========================================================================
void TextureAnimation::SetSrcRect (unsigned index, const SDL_Rect & rect) {
	SDL_assert_release(index < s_maxFrames);

	m_srcRects[index] = rect;
	m_frameCount      = SDL_max(m_frameCount, index + 1);
}

} // namespace CSaru2d

