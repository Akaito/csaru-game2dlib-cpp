#pragma once

#include <vector>

#include "ObjId.hpp"
#include "Transform.hpp"

namespace CSaruGame {

class GameObjectComponent;

class GameObject {
    
protected: // Data

    Transform                          m_transform;
    std::vector<GameObjectComponent *> m_components;
    
public:

    GameObject ();
    
private: // Helpers

public: // GameObject

    void Update (float dt);
    void Render ();
    
    Transform &       GetTransform ()       { return m_transform; }
    const Transform & GetTransform () const { return m_transform; }

    void                  AddComponent (GameObjectComponent * component);
    GameObjectComponent * GetComponentExact (ObjId id);
    GameObjectComponent * GetComponentByType (ObjId globalTypeId);

};

} // namespace CSaruGame

