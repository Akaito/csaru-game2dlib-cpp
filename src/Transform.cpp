#include "../include/Transform.hpp"

namespace CSaruGame {

//==============================================================================
Transform::Transform () : m_rotation(0.0f) {

  m_position.zero();
  m_scale.set(1.0f, 1.0f, 1.0f);
  m_velocity.zero();

}

//==============================================================================
Transform::~Transform () {
}

//==============================================================================
void Transform::GetWorldFromModelMtx (cml::matrix44f_c * worldMatrixOut) const {

    cml::matrix44f_c translation;
	cml::matrix44f_c rotationZ;
	cml::matrix44f_c scale;

	cml::matrix_translation(translation, m_position[0], m_position[1], 0.0f);
	cml::matrix_rotation_world_z(rotationZ, m_rotation);
	cml::matrix_scale(scale, m_scale[0], m_scale[1], 1.0f);

    //*worldMatrixOut = translation * rotationZ * scale;
    *worldMatrixOut = scale * rotationZ * translation;

}

//===========================================================================
void Transform::SetPosition (float x, float y, float z) {
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;
}

//==============================================================================
void Transform::SetPosition (const cml::vector3f & position) {
    m_position = position;
}

//==============================================================================
void Transform::SetRotation (float rotation) {
    m_rotation = rotation;
}

//==============================================================================
void Transform::SetScale (const cml::vector3f & scale) {
    m_scale = scale;
}

//==============================================================================
void Transform::SetVelocity (const cml::vector3f & velocity) {
    m_velocity = velocity;
}

//==============================================================================
void Transform::SetVelocity (float x, float y) {
    m_velocity.set(x, y, 0.0f);
}

} // namespace CSaruGame

