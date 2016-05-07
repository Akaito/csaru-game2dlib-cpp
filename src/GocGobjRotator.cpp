#include "../include/GocGobjRotator.hpp"
#include "../include/Transform.hpp"
#include "../include/GameObject.hpp"

/*
#ifdef WIN32
#	include <SDL.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#endif
*/

namespace CSaruGame {

//==============================================================================
GocGobjRotator::~GocGobjRotator () {
}

//==============================================================================
void GocGobjRotator::Update (float dt) {

	if (m_radiansPerSecond == 0.0f)
		return;

	Transform & transform = m_owner->GetTransform();
	transform.SetRotation(
		transform.GetRotation() +
			m_radiansPerSecond * dt
	);

}

} // namespace CSaruGame

