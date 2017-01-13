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
	~GameObject ();

public: // Queries

    Transform &       GetTransform ()       { return m_transform; }
    const Transform & GetTransform () const { return m_transform; }

    GameObjectComponent * GetGocExact (ObjId id);
    GameObjectComponent * GetGocByType (ObjId globalTypeId);

	template <typename T_Goc>
	T_Goc * GetGoc () {
		return static_cast<T_Goc *>(GetGocByType(T_Goc::s_gocTypeId));
	}
    
public: // Commands

    void Update (float dt);
    void Render ();

    void                  AddComponent (GameObjectComponent * component);

};

} // namespace CSaruGame

