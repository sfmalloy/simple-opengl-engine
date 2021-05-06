/// \file Camera.hpp
/// \brief Declaration of Camera class and any associated global functions.
/// \author Sean Malloy
/// \version A03

#include <iostream>

#include "Camera.hpp"
#include "OpenGLContext.hpp"
#include "Vector3.hpp"
#include "Matrix3.hpp"

Camera::Camera(const Vector3& eyePosition, const Vector3& localBackDirection, 
  float nearClipPlaneDistance, float farClipPlaneDistance,
  float aspectRatio, float verticalFieldOfViewDegrees)
  : m_world(),
    m_changedView(true),
    m_originalEyePosition(eyePosition),
    m_originalBackDirection(localBackDirection / localBackDirection.length())
{
  // Make directions all orthogonal to each other
  Vector3 localUpDirection(0.0f, 1.0f, 0.0f);
  Vector3 localRightDirection = localUpDirection.cross(localBackDirection);
  localUpDirection = localBackDirection.cross(localRightDirection);

  m_world.setPosition(eyePosition);
  m_world.setOrientation(Matrix3(localRightDirection, localUpDirection, true));

  setProjectionSymmetricPerspective(verticalFieldOfViewDegrees, aspectRatio, 
    nearClipPlaneDistance, farClipPlaneDistance);
}

void
Camera::setPosition(const Vector3& position)
{
  m_world.setPosition(position);
  m_changedView = true;
}

void
Camera::moveRight(float distance)
{
  m_world.moveRight(distance);
  m_changedView = true;
}

void
Camera::moveUp(float distance)
{
  m_world.moveUp(distance);
  m_changedView = true;
}

void
Camera::moveBack(float distance)
{
  m_world.moveBack(distance);
  m_changedView = true;
}

void
Camera::pitch(float degrees)
{
  m_world.pitch(degrees);
  m_changedView = true;
}

void
Camera::yaw(float degrees)
{
  m_world.yaw(degrees);
  m_changedView = true;
}

void
Camera::roll(float degrees)
{
  m_world.roll(degrees);  
  m_changedView = true;
}

Transform
Camera::getViewMatrix()
{
  if (m_changedView)
  {
    Transform rotateInverse;
    rotateInverse.setOrientation(m_world.getOrientation());
    rotateInverse.invertRt();

    Transform translateInverse;
    translateInverse.setPosition(-m_world.getPosition());

    m_viewMatrix = rotateInverse * translateInverse;

    m_changedView = false;
  }

  return m_viewMatrix;
}

void
Camera::setProjectionSymmetricPerspective(double verticalFovDegrees, 
    double aspectRatio, double nearZ, double farZ)
{
  m_projectionMatrix.setToPerspectiveProjection(verticalFovDegrees, 
    aspectRatio, nearZ, farZ);
}

void
Camera::setProjectionAsymmetricPerspective(double left, double right,
  double bottom, double top, double nearPlaneZ, double farPlaneZ)
{
  m_projectionMatrix.setToPerspectiveProjection(left, right,
    bottom, top, nearPlaneZ, farPlaneZ);
}

void
Camera::setProjectionOrthographic(double left, double right,
  double bottom, double top, double nearPlaneZ, double farPlaneZ)
{
  m_projectionMatrix.setToOrthographicProjection(left, right,
    bottom, top, nearPlaneZ, farPlaneZ);
}

Matrix4
Camera::getProjectionMatrix()
{
  return m_projectionMatrix;
}

void
Camera::resetPose()
{
  // Reset position to face front
  setPosition(m_originalEyePosition);

  // Make directions all orthogonal to each other
  Vector3 localUpDirection(0.0f, 1.0f, 0.0f);
  Vector3 right = localUpDirection.cross(m_originalBackDirection);
  Vector3 up = m_originalBackDirection.cross(right);

  m_world.setOrientation(Matrix3(right, up, m_originalBackDirection));
}