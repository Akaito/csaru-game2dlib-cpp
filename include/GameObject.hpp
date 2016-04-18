#pragma once

#include <vector>

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
    GameObjectComponent * GetComponent (unsigned componentTypeId);
    GameObjectComponent * GetComponent (unsigned short module, unsigned short componentType) {
        return GetComponent(module << 16 | componentType);
    }

};

} // namespace CSaruGame

