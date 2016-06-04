#pragma once

#include <map>

#include <csaru-core-cpp/csaru-core-cpp.h>
#include <csaru-container-cpp/csaru-container-cpp.h>

#include "ObjId.hpp"
#include "GameObject.hpp"

namespace CSaruGame {

class Level {
private: // data
	std::map<ObjId, GameObject *> m_gameObjects;

private: // helpers
	void LoadLevelStuffGameObject (CSaruContainer::DataMapReaderSimple);
	void LoadLevelStuffComponent (CSaruContainer::DataMapReaderSimple);

public: // construction
	Level ();
	~Level ();

public: // commands
	bool AcceptDataMap (CSaruContainer::DataMapReader);
	void Destroy ();

public: // queries
	GameObject * GetGameObject (ObjId);
};

} // namespace CSaruGame

