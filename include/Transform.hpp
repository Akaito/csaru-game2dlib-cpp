#pragma once

#include <cml/cml.h> // Configurable Math Library

namespace CSaruGame {

class Transform {

private: // Data

	cml::vector3f m_position;
    float         m_rotation;
	cml::vector3f m_scale;
    
	cml::vector3f m_velocity; // Hacks! (?)

public:
    // Construction
    Transform();
    virtual ~Transform();

    // Queries
    void                  GetWorldFromModelMtx (cml::matrix44f_c * worldMatrixOut) const;
    const cml::vector3f & GetPosition () const     { return m_position; }
    float                 GetRotation () const     { return m_rotation; }
    const cml::vector3f & GetScale () const        { return m_scale;    }
    const cml::vector3f & GetVelocity () const     { return m_velocity; }

    // Commands
    void SetPosition (const cml::vector3f & position);
    void SetRotation (float rotation);
    void SetScale (const cml::vector3f & scale);
    
    void SetVelocity (const cml::vector3f & velocity);
    void SetVelocity (float x, float y);

};

} // namespace CSaruGame

