#pragma once

#include <csaru-core-cpp/csaru-core-cpp.hpp>

#include "ObjId.hpp"

namespace CSaruGame {

class GameObject;

/**
 * GameObjectComponents must be guaranteed to not change address or delete while
 * attached to a GameObject.
 */
class GameObjectComponent {
protected: // Data
    ObjId        m_id;
    GameObject * m_owner;

public: // Methods
    GameObjectComponent (ObjId id = s_ObjId_Invalid) : m_id(id), m_owner(nullptr)
    {}

    GameObjectComponent (ObjId module, ObjId type, uint32_t generation) :
        m_id(CSARU_ID(module, type, generation)),
        m_owner(nullptr)
    {}

    virtual ~GameObjectComponent () {}

    virtual void Update (float dt) { unused(dt); }
    virtual void Render ()         {}

    ObjId        GetId () const                { return m_id; }
    ObjId        GetLocalTypeId () const       { return m_id & CSARU_TYPE_MASK; }
	ObjId        GetGlobalTypeId () const      { return m_id & (CSARU_MODULE_MASK | CSARU_TYPE_MASK); }
    ObjId        GetModuleId () const          { return m_id & CSARU_MODULE_MASK; }
    ObjId        GetGeneration () const        { return m_id & CSARU_GENERATION_MASK; }
    GameObject * GetOwner ()                   { return m_owner; }
    void         SetOwner (GameObject * owner) { m_owner = owner; }
};

} // namespace CSaruGame

