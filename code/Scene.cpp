/// \file Scene.cpp
/// \brief Implementation of Scene class and any associated global functions.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// System includes
#include <iostream>
#include <string>

/******************************************************************/
// Local includes
#include "Scene.hpp"
#include "Matrix4.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"

/******************************************************************/
Scene::Scene()
  : m_scene(),
    m_activeMesh(m_scene.begin())
{
}

Scene::~Scene()
{
  clear();
}

void
Scene::add(const std::string& meshName, Mesh* mesh)
{
  if (!hasMesh(meshName))
    m_scene[meshName] = mesh;
  else
    delete mesh;

  if (m_scene.size() == 1)
    m_activeMesh = m_scene.begin();
}

void
Scene::remove(const std::string& meshName)
{
  delete m_scene[meshName];
  m_scene.erase(meshName);
}

void
Scene::clear()
{
  for (auto& mesh : m_scene)
    delete mesh.second;
  m_scene.clear();
}

void
Scene::draw(const Transform& viewMatrix, const Matrix4& projectionMatrix)
{
  for (auto& mesh : m_scene)
    mesh.second->draw(viewMatrix, projectionMatrix);
}

bool
Scene::hasMesh(const std::string& meshName)
{
  return m_scene.find(meshName) != m_scene.end();
}

Mesh*
Scene::getMesh(const std::string& meshName)
{
  return m_scene.at(meshName);
}

void
Scene::setActiveMesh(const std::string& meshName)
{
  m_activeMesh = m_scene.find(meshName);
}

Mesh*
Scene::getActiveMesh()
{
  return m_activeMesh->second;
}

void
Scene::activateNextMesh()
{
  ++m_activeMesh;
  if (m_activeMesh == m_scene.end())
    m_activeMesh = m_scene.begin();
}

void
Scene::activatePreviousMesh()
{
  if (m_activeMesh == m_scene.begin())
    m_activeMesh = m_scene.end();
  --m_activeMesh;
}

