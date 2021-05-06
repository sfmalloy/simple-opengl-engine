/// \file Transform.hpp
/// \brief Implementation of Transform class and any associated global functions.
/// \author Sean Malloy
/// \version A06
/******************************************************************/
// System includes
#include <iostream>
#include <iomanip>

/******************************************************************/
// Local includes
#include "Transform.hpp"
#include "Matrix3.hpp"
#include "Vector3.hpp"
#include "Matrix4.hpp"
#include "Vector4.hpp"

/******************************************************************/
Transform::Transform()
  : m_rotScale(),
    m_position()
{
}

void
Transform::orthonormalize()
{
  m_rotScale.orthonormalize();
}

void
Transform::reset()
{
  *this = Transform();
}

Matrix4
Transform::getTransform() const
{
  Vector4 right(m_rotScale.getRight().m_x, m_rotScale.getRight().m_y, m_rotScale.getRight().m_z, 0.0f);
  Vector4 up(m_rotScale.getUp().m_x, m_rotScale.getUp().m_y, m_rotScale.getUp().m_z, 0.0f);
  Vector4 back(m_rotScale.getBack().m_x, m_rotScale.getBack().m_y, m_rotScale.getBack().m_z, 0.0f);
  Vector4 translation(m_position.m_x, m_position.m_y, m_position.m_z, 1.0f);
  return Matrix4(right, up, back, translation);
}

void
Transform::getTransform(float array[16]) const
{
  auto matPtr = m_rotScale.data();
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j, ++matPtr)
      array[(4 * j) + i] = *matPtr;
    array[(4 * i) + 3] = 0.0f;
  }

  array[12] = m_position.m_x;
  array[13] = m_position.m_y;
  array[14] = m_position.m_z;
  array[15] = 1.0f;
}

Vector3
Transform::getPosition() const
{
  return m_position;
}

void
Transform::setPosition(const Vector3& position)
{
  m_position = position;
}

void
Transform::setPosition(float x, float y, float z)
{
  m_position = Vector3(x, y, z);
}

Vector3
Transform::getRight() const
{
  return m_rotScale.getRight();
}

Vector3
Transform::getUp() const
{
  return m_rotScale.getUp();
}

Vector3
Transform::getBack() const
{
  return m_rotScale.getBack();
}

Matrix3
Transform::getOrientation() const
{
  return m_rotScale;
}

void
Transform::setOrientation(const Matrix3& orientation)
{
  m_rotScale = orientation;
}

void
Transform::setOrientation(const Vector3& right, const Vector3& up, 
  const Vector3& back)
{
  m_rotScale = Matrix3(right, up, back);
}

void
Transform::moveRight(float distance)
{
  moveLocal(distance, m_rotScale.getRight());
}

void
Transform::moveUp(float distance)
{
  moveLocal(distance, m_rotScale.getUp());
}

void
Transform::moveBack(float distance)
{
  moveLocal(distance, m_rotScale.getBack());
}

void
Transform::moveLocal(float distance, const Vector3& localDirection)
{
  m_position += distance * localDirection;
}

void
Transform::moveWorld(float distance, const Vector3& worldDirection)
{
  m_position += m_rotScale * (distance * worldDirection);
}

void
Transform::pitch(float angleDegrees)
{
  Matrix3 rot;
  rot.setToRotationX(angleDegrees);
  m_rotScale *= rot;
}

void
Transform::yaw(float angleDegrees)
{
  Matrix3 rot;
  rot.setToRotationY(angleDegrees);
  m_rotScale *= rot;
}

void
Transform::roll(float angleDegrees)
{
  Matrix3 rot;
  rot.setToRotationZ(angleDegrees);
  m_rotScale *= rot;
}

void
Transform::rotateLocal(float angleDegrees, const Vector3& axis)
{
  Matrix3 rot;
  rot.setFromAngleAxis(angleDegrees, axis);
  m_rotScale *= rot;
}

void
Transform::alignWithWorldY()
{
  m_rotScale.orthonormalize();
}

void
Transform::rotateWorld(float angleDegrees, const Vector3& axis)
{
  Matrix3 rot;
  rot.setFromAngleAxis(angleDegrees, axis);
  m_rotScale = rot * m_rotScale;
  m_position = rot * m_position; 
}

void
Transform::scaleLocal(float scale)
{
  m_rotScale *= scale;
}

void
Transform::scaleLocal(float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMat;
  scaleMat.setToScale(scaleX, scaleY, scaleZ);
  m_rotScale *= scaleMat;
}

void
Transform::scaleWorld(float scale)
{
  Matrix3 scaleMat;
  scaleMat.setToScale(scale);
  m_rotScale = scaleMat * m_rotScale;
}

void
Transform::scaleWorld(float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMat;
  scaleMat.setToScale(scaleX, scaleY, scaleZ);
  m_rotScale = scaleMat * m_rotScale;
}

void
Transform::shearLocalXByYz(float shearY, float shearZ)
{
  Matrix3 shearMat;
  shearMat.setToShearXByYz(shearY, shearZ);
  m_rotScale *= shearMat;
}

void
Transform::shearLocalYByXz(float shearX, float shearZ)
{
  Matrix3 shearMat;
  shearMat.setToShearYByXz(shearX, shearZ);
  m_rotScale *= shearMat;
}

void
Transform::shearLocalZByXy(float shearX, float shearY)
{
  Matrix3 shearMat;
  shearMat.setToShearZByXy(shearX, shearY);
  m_rotScale *= shearMat;
}

void
Transform::invertRt()
{
  m_rotScale.invertRotation();
}

void
Transform::combine(const Transform& t)
{
  *this = *this * t;
}

Transform
operator*(const Transform& t1, const Transform& t2)
{
  Transform result;
  result.setOrientation(t1.getOrientation() * t2.getOrientation());
  result.setPosition((t1.getOrientation() * t2.getPosition()) + t1.getPosition());
  return result;
}

std::ostream&
operator<<(std::ostream& out, const Transform& t)
{
  Matrix3 matCopy = t.getOrientation();
  matCopy.transpose();
  
  out << std::setprecision(2) << std::fixed    << std::right
      << matCopy.getRight()   << std::setw(10) << t.getPosition().m_x << '\n'
      << matCopy.getUp()      << std::setw(10) << t.getPosition().m_y << '\n'
      << matCopy.getBack()    << std::setw(10) << t.getPosition().m_z << '\n'
      << std::setw(10) << 0.0f
      << std::setw(10) << 0.0f
      << std::setw(10) << 0.0f
      << std::setw(10) << 1.0f;

  return out;
}

bool
operator==(const Transform& t1, const Transform& t2)
{
  return t1.getOrientation() == t2.getOrientation() 
    && t1.getPosition() == t2.getPosition();
}