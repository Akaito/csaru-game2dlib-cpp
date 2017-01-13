#pragma once

#include <map>

#include <csaru-core-cpp/csaru-core-cpp.hpp>
#include <csaru-container-cpp/csaru-container-cpp.hpp>
#include <csaru-datamap-cpp/csaru-datamap-cpp.hpp>

#include "ObjId.hpp"
#include "GameObject.hpp"

namespace CSaruGame {

class Level {
private: // data
	CSaruContainer::ObjectPool<GameObject> m_gobPool;
	std::map<ObjId, GameObject *>          m_gameObjects;

private: // helpers
	void LoadLevelStuffGameObject (CSaruDataMap::DataMapReaderSimple);
	void LoadLevelStuffComponent (CSaruDataMap::DataMapReaderSimple);

public: // construction
	Level ();
	~Level ();

public: // commands
	bool AcceptDataMap (CSaruDataMap::DataMapReader);
	void Destroy ();

public: // queries
	GameObject * GetGameObject (ObjId);
};

} // namespace CSaruGame

