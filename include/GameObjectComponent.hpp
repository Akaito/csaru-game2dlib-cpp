#pragma once

#include <csaru-core-cpp/csaru-core-cpp.h>

namespace CSaruGame {

class GameObject;

// GameObjectComponents must be guaranteed to not change address or delete while attached to a GameObject.
class GameObjectComponent {
public: // Types
	// TODO : Demand 64-bit?  16 module, 16 type, 32 generation?
    typedef unsigned GlobalTypeId;
    static const unsigned s_InvalidGlobalTypeId = 0;

protected: // Data
    GlobalTypeId m_typeId;
    GameObject * m_owner;

public: // Methods
    GameObjectComponent (GlobalTypeId typeId = s_InvalidGlobalTypeId) : m_typeId(typeId), m_owner(nullptr)
    {}

    GameObjectComponent (unsigned short moduleId, unsigned short componentTypeId) :
        m_typeId(moduleId << 16 | componentTypeId),
        m_owner(nullptr)
    {}

    virtual ~GameObjectComponent () {}

    virtual void Update (float dt) { unused(dt); }
    virtual void Render ()         {}

    GlobalTypeId    GetGlobalTypeId () const      { return m_typeId; }
    unsigned short  GetLocalTypeId () const       { return m_typeId & 0xFFFF; }
    unsigned short  GetModuleId () const          { return m_typeId >> 16; }
    GameObject *    GetOwner ()                   { return m_owner; }
    void            SetOwner (GameObject * owner) { m_owner = owner; }
};

} // namespace CSaruGame

