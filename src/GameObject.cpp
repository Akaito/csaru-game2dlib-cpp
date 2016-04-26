#include "../include/GameObject.hpp"
#include "../include/GameObjectComponent.hpp"

namespace CSaruGame {

//==============================================================================
GameObject::GameObject ()
{}

//==============================================================================
void GameObject::AddComponent (GameObjectComponent * component) {
    m_components.push_back(component);
    component->SetOwner(this);
}

//==============================================================================
GameObjectComponent * GameObject::GetComponentByType (ObjId globalTypeId) {

    for (GameObjectComponent * goc : m_components) {
        if (goc->GetGlobalTypeId() == globalTypeId)
            return goc;
    }

    return nullptr;

}

//==============================================================================
GameObjectComponent * GameObject::GetComponentExact (ObjId id) {

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
        comp->Update(dt);
    }

}

} // namespace CSaruGame

