/// \file Mesh.cpp
/// \brief Implementation of Mesh class and any associated global functions.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// System includes
#include <iostream>

/******************************************************************/
// Local includes
#include "Mesh.hpp"
#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Vector3.hpp"
#include "Transform.hpp"
#include "Matrix4.hpp"

/******************************************************************/
Mesh::Mesh(OpenGLContext* context, ShaderProgram* shader)
	: m_context(context),
		m_shader(shader),
		m_prepared(false),
		m_world()
{
	m_context->genVertexArrays(1, &m_vao);
	m_context->genBuffers(1, &m_vbo);
	m_context->genBuffers(1, &m_ibo);
}

Mesh::~Mesh()
{
  m_context->deleteVertexArrays(1, &m_vao);
	m_context->deleteBuffers(1, &m_vbo);
}

void
Mesh::addGeometry(const std::vector<float>& geometry)
{
	m_data.insert(m_data.end(), geometry.begin(), geometry.end());
}

void
Mesh::addIndices(const std::vector<unsigned int>& indices)
{
	m_indices.insert(m_indices.end(), indices.begin(), indices.end());
}

void
Mesh::prepareVao()
{
	m_context->bindVertexArray(m_vao);

	m_context->bindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_context->bufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float),
		m_data.data(), GL_STATIC_DRAW);
	
	m_context->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	m_context->bufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
		m_indices.data(), GL_STATIC_DRAW);

	enableAttributes();

	m_context->bindVertexArray(0);

	m_prepared = true;
}

void
Mesh::draw(const Transform& viewMatrix, const Matrix4& projectionMatrix)
{
	Transform modelView = viewMatrix;
	modelView.combine(m_world);
	m_shader->enable();
	m_shader->setUniformMatrix("uModelView", modelView.getTransform());
	m_shader->setUniformMatrix("uProjection", projectionMatrix);

	m_context->bindVertexArray(m_vao);
	m_context->drawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 
		reinterpret_cast<void*>(0));
	m_context->bindVertexArray(0);

	m_shader->disable();
}

Transform
Mesh::getWorld() const
{
	return m_world;
}

void
Mesh::moveRight(float distance)
{
	m_world.moveRight(distance);
}

void
Mesh::moveUp(float distance)
{
	m_world.moveUp(distance);
}

void
Mesh::moveBack(float distance)
{
	m_world.moveBack(distance);
}

void
Mesh::moveLocal(float distance, const Vector3& localDirection)
{
	m_world.moveLocal(distance, localDirection);
}

void
Mesh::moveWorld(float distance, const Vector3& worldDirection)
{
	m_world.moveWorld(distance, worldDirection);
}

void
Mesh::pitch(float angleDegrees)
{
	m_world.pitch(angleDegrees);
}

void
Mesh::yaw(float angleDegrees)
{
	m_world.yaw(angleDegrees);
}

void
Mesh::roll(float angleDegrees)
{
	m_world.roll(angleDegrees);
}

void
Mesh::rotateLocal(float angleDegrees, const Vector3& axis)
{
	m_world.rotateLocal(angleDegrees, axis);
}

void
Mesh::alignWithWorldY()
{
	m_world.alignWithWorldY();
}

void
Mesh::scaleLocal(float scale)
{
	m_world.scaleLocal(scale);
}

void
Mesh::scaleLocal(float scaleX, float scaleY, float scaleZ)
{
	m_world.scaleLocal(scaleX, scaleY, scaleZ);
}

void
Mesh::shearLocalXByYz(float shearY, float shearZ)
{
	m_world.shearLocalXByYz(shearY, shearZ);
}

void
Mesh::shearLocalYByXz(float shearX, float shearZ)
{
	m_world.shearLocalYByXz(shearX, shearZ);
}

void
Mesh::shearLocalZByXy(float shearX, float shearY)
{
	m_world.shearLocalZByXy(shearX, shearY);
}

void
Mesh::scaleWorld(float scale)
{
	m_world.scaleWorld(scale);
}

unsigned int
Mesh::getFloatsPerVertex() const
{
	return 3;
}

void
Mesh::enableAttributes()
{	
  const GLint POSITION_ATTRIB_INDEX = 0;
	const GLsizei VERTEX_STRIDE = 6 * sizeof(float);

	m_context->enableVertexAttribArray(POSITION_ATTRIB_INDEX);
	m_context->vertexAttribPointer(POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE,
		VERTEX_STRIDE, reinterpret_cast<void*>(0));
}