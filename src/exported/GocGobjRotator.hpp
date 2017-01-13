#pragma once

#include <csaru-core-cpp/csaru-core-cpp.hpp>

#include "GameObjectComponent.hpp"

namespace CSaruGame {

class GocGobjRotator : public GameObjectComponent {
public: // ID
	// 9XXX are miscellaneous gocs; easier debugging by module-local convention
	// 9CXX mostly interact with the most-basic C5A2 (CSaruGameLib) module stuff
	static const ObjId s_gocTypeId = CSARU_TYPE_ID(s_Module_Base, 0x9C01);

private: // Data
	float m_radiansPerSecond = 0.0f;

public: // Construction
	GocGobjRotator (uint32_t generation = 0) :
		GameObjectComponent(s_Module_Base, s_gocTypeId, generation)
	{}

	~GocGobjRotator ();

public: // Commands
	void SetRadiansPerSecond (float radians) { m_radiansPerSecond = radians; }

public: // GameObjectComponent interface
	void Update (float dt);

};

} // namespace CSaruGame

