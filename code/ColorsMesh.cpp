/// \file ColorsMesh.hpp
/// \brief Implementation of Mesh subclass for meshes with Color data.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// System includes

/******************************************************************/
// Local includes
#include "Mesh.hpp"
#include "ColorsMesh.hpp"

/******************************************************************/

ColorsMesh::ColorsMesh(OpenGLContext* context, ShaderProgram* shader)
  : Mesh(context, shader)
{
}

unsigned int
ColorsMesh::getFloatsPerVertex() const
{
  return 3 + Mesh::getFloatsPerVertex();
}

void
ColorsMesh::enableAttributes()
{
	const GLint COLOR_ATTRIB_INDEX = 1;
	const GLsizei VERTEX_STRIDE = 6 * sizeof(float);
	const GLintptr COLOR_OFFSET = 3 * sizeof(float);

	m_context->enableVertexAttribArray(COLOR_ATTRIB_INDEX);
	m_context->vertexAttribPointer(COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_STRIDE,
		reinterpret_cast<void*>(COLOR_OFFSET));

  Mesh::enableAttributes();
}