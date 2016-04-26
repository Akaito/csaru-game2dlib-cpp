#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

#include "ObjId.hpp"

namespace CSaruGame {

class GameObject;

// GameObjectComponents must be guaranteed to not change address or delete while attached to a GameObject.
class GameObjectComponent {
protected: // Data
    ObjId        m_id;
    GameObject * m_owner;

public: // Methods
    GameObjectComponent (ObjId id = s_ObjId_Invalid) : m_id(id), m_owner(nullptr)
    {}

    GameObjectComponent (uint16_t module, uint16_t type, uint32_t generation) :
        m_id(CSARU_ID(module, type, generation)),
        m_owner(nullptr)
    {}

    virtual ~GameObjectComponent () {}

    virtual void Update (float dt) { unused(dt); }
    virtual void Render ()         {}

    ObjId        GetId () const                { return m_id; }
    uint16_t     GetLocalTypeId () const       { return CSARU_GET_TYPE_ID(m_id); }
	uint32_t     GetGlobalTypeId () const      { return static_cast<uint32_t>(m_id >> 32); }
    uint16_t     GetModuleId () const          { return CSARU_GET_MODULE_ID(m_id); }
    uint32_t     GetGeneration () const        { return CSARU_GET_GENERATION(m_id); }
    GameObject * GetOwner ()                   { return m_owner; }
    void         SetOwner (GameObject * owner) { m_owner = owner; }
};

} // namespace CSaruGame

