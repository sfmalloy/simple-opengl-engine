/// \file ColorsMesh.hpp
/// \brief Declaration of Mesh subclass for meshes with Color data.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// System includes

/******************************************************************/
// Local includes
#include "Mesh.hpp"

/******************************************************************/

class ColorsMesh : public Mesh
{
public:
  /// \brief Initial value constructor
  ColorsMesh(OpenGLContext* context, ShaderProgram* shader);

  virtual unsigned int
  getFloatsPerVertex() const;
protected:

  virtual void
  enableAttributes();

};