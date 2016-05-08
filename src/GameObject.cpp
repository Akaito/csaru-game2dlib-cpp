#include "../include/GameObject.hpp"
#include "../include/GameObjectComponent.hpp"

#ifdef WIN32
#	include <SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

namespace CSaruGame {

//==============================================================================
GameObject::GameObject ()
{}

//==============================================================================
GameObject::~GameObject () {
	// TODO : Assert instead of silently delete.
	for (GameObjectComponent * goc : m_components) {
		delete goc;
	}
	m_components.clear();
}

//==============================================================================
void GameObject::AddComponent (GameObjectComponent * component) {
	SDL_assert_release(component->GetModuleId());
	SDL_assert_release(component->GetLocalTypeId());
	SDL_assert_release(component->GetGeneration());

    m_components.push_back(component);
    component->SetOwner(this);
}

//==============================================================================
GameObjectComponent * GameObject::GetGocByType (ObjId globalTypeId) {

    for (GameObjectComponent * goc : m_components) {
        if ((goc->GetGlobalTypeId() & ~CSARU_GENERATION_MASK) == globalTypeId)
            return goc;
    }

    return nullptr;

}

//==============================================================================
GameObjectComponent * GameObject::GetGocExact (ObjId id) {

    for (GameObjectComponent * goc : m_components) {
        if (goc->GetId() == id)
            return goc;
    }

    return nullptr;

}

//==============================================================================
void GameObject::Render () {

    for (unsigned i = 0; i < m_components.size(); ++i) {
        GameObjectComponent * comp = m_components[i];
        comp->Render();
    }

}

//==============================================================================
void GameObject::Update (float dt) {

    for (unsigned i = 0; i < m_components.size(); ++i) {
        GameObjectComponent * comp = m_components[i];
		SDL_assert_release(comp);
        comp->Update(dt);
    }

}

} // namespace CSaruGame

