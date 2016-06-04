#include "../include/Level.hpp"

#include <cstring>

#ifdef WIN32
#	include <SDL.h>
#	include <SDL_image.h>
#	include <SDL_ttf.h>
#	undef main
#else
#	include <SDL2/SDL.h>
#	include <SDL2/SDL_image.h>
#	include <SDL2/SDL_ttf.h>
#endif

#include "../include/GocSpriteSimple.hpp"
#include "../include/GocGobjRotator.hpp"

namespace CSaruGame {

//==============================================================================
Level::Level () {
}

//==============================================================================
Level::~Level () {
	Destroy();
}

//==============================================================================
bool Level::AcceptDataMap (CSaruContainer::DataMapReader dmrRoot) {

	// root -> data
	dmrRoot.ToFirstChild();
	SDL_assert_release(!std::strcmp(dmrRoot.ReadName(), "data"));
	if (!std::strcmp(dmrRoot.ReadName(), "data")) {
		CSaruContainer::DataMapReaderSimple simpleReader(dmrRoot);
		// data -> array of data objects or first data object
		simpleReader.ToFirstChild();

		// for each data object
		for (; simpleReader.IsValid(); simpleReader.ToNextSibling()) {
			// ignore if it's not a GameObject
			if (simpleReader.String("type") == "GameObject")
				LoadLevelStuffGameObject(simpleReader);
			else
				LoadLevelStuffComponent(simpleReader);
		}
	}

	return true;

}

//==============================================================================
void Level::Destroy () {
	for (auto pair : m_gameObjects) {
		delete pair.second;
	}
	m_gameObjects.clear();
}

//==============================================================================
GameObject * Level::GetGameObject (ObjId id) {
	auto iter = m_gameObjects.find(id);
	if (iter == m_gameObjects.end())
		return nullptr;

	return iter->second;
}

//==============================================================================
void Level::LoadLevelStuffGameObject (CSaruContainer::DataMapReaderSimple simpleReader) {
	int id = simpleReader.Int("id");
	//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "id: %d", id);

	GameObject * gobj = new GameObject;

	simpleReader.ToChild("attributes");
	if (simpleReader.ToChild("transform")) {
		if (simpleReader.EnterArray("position")) {
			CSaruContainer::DataMapReader posReader = simpleReader.GetReader();
			int x = posReader.ReadIntWalk();
			int y = posReader.ReadIntWalk();
			int z = posReader.ReadIntWalk();
			//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "pos: |%d, %d, %d|", x, y, z);
			gobj->GetTransform().SetPosition(x, y, z);
			simpleReader.ExitArray();
		}

		float rot = simpleReader.Float("rotation", 0.0f);
		if (rot != 0.0f) {
			gobj->GetTransform().SetRotation(rot);
		}

		simpleReader.ToParent();
	}

	m_gameObjects[id] = gobj;
}

//==============================================================================
void Level::LoadLevelStuffComponent (CSaruContainer::DataMapReaderSimple simpleReader) {

	//SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "type: %s", simpleReader.String("type").c_str());

	// module
	const std::string fullType = simpleReader.String("type");
	SDL_assert_release(std::strstr(fullType.c_str(), "CSaruBase_") != nullptr);

	// type
	const char * type = std::strchr(fullType.c_str(), '_');
	SDL_assert_release(type);
	++type;

	// component id
	const unsigned componentId = simpleReader.Int("id", 0);
	SDL_assert_release(componentId);

	// owner gobj id
	unsigned ownerId = unsigned(-1);
	simpleReader.ToChild("relationships"); {
		simpleReader.ToChild("owner"); {
			simpleReader.ToChild("data"); {
				SDL_assert_release(simpleReader.String("type") == "GameObject");
				ownerId = simpleReader.Int("id", unsigned(-1));
			} simpleReader.ToParent();
		} simpleReader.ToParent();
	} simpleReader.ToParent();
	SDL_assert_release(ownerId != unsigned(-1));

	// Find owner GameObject.
	auto ownerGobjIter = m_gameObjects.find(ownerId);
	const bool ownerGobjExists = ownerGobjIter != m_gameObjects.end();
	if (!ownerGobjExists) {
		// TODO : Test this log.
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Level file component {%u} owned by missing GameObject {%u}."
				"Consider using multiple files with prefixed numbers to indicate loading order.",
			componentId, ownerId
		);
		SDL_assert(ownerGobjExists);
		return;
	}
	GameObject * ownerGobj = ownerGobjIter->second;
	if (!ownerGobj) {
		// TODO : Test this log.
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Level file component {%u} owned by a GameObject {%u} which has been deleted (is nullptr)."
				"Did logic happen between files/loading objects to delete this GameObject?",
			componentId, ownerId
		);
		SDL_assert(ownerGobj);
		return;
	}

	// Create and serialize new component.
	if (!std::strncmp(type, "GocSpriteSimple", 80)) {
		ownerGobj->AddComponent(new CSaruGame::GocSpriteSimple(componentId));
		if (simpleReader.ToChild("attributes")) {
			auto goc = ownerGobj->GetGoc<CSaruGame::GocSpriteSimple>();
			// src_rect
			{
				if (simpleReader.EnterArray("src_rect")) {
					CSaruContainer::DataMapReader posReader = simpleReader.GetReader();
					int x = posReader.ReadIntWalk();
					int y = posReader.ReadIntWalk();
					int w = posReader.ReadIntWalk();
					int h = posReader.ReadIntWalk();
					goc->GetSrcRect() = SDL_Rect{x, y, w, h};
					simpleReader.ExitArray();
				}
				else
					simpleReader.ToParent();
			}

			// flip
			{
				std::string flip = simpleReader.String("flip", "none");
				if (flip == "horizontal")
					goc->SetFlip(SDL_FLIP_HORIZONTAL);
				else if (flip == "vertical")
					goc->SetFlip(SDL_FLIP_VERTICAL);
				else if (flip == "horizontal,vertical")
					goc->SetFlip(SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
				else
					goc->SetFlip(SDL_FLIP_NONE);
			}

			/*
			// color
			// (to be moved to post-create load section)
			{
				if (simpleReader.EnterArray("color")) {
					CSaruContainer::DataMapReader posReader = simpleReader.GetReader();
					int r = posReader.ReadIntWalk();
					int g = posReader.ReadIntWalk();
					int b = posReader.ReadIntWalk();
					goc->GetSrcRect() = SDL_Rect{x, y, w, h};
					simpleReader.ExitArray();
				}
				else
					simpleReader.ToParent();
			}
			*/
		}
		else
			simpleReader.ToParent();
		simpleReader.ToParent();
	}
	else if (!std::strncmp(type, "GocGobjRotator", 80)) {
		ownerGobj->AddComponent(new CSaruGame::GocGobjRotator(componentId));
		if (simpleReader.ToChild("attributes")) {
			auto goc = ownerGobj->GetGoc<CSaruGame::GocGobjRotator>();
			goc->SetRadiansPerSecond(simpleReader.Float("rads_per_sec", 10.0f));
		}
		else
			simpleReader.ToParent();
		simpleReader.ToParent();
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Invalid component type {%s}!\n", type);
	}

}

} // namespace CSaruGame

