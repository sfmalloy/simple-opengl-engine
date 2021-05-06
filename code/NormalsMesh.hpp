/// \file NormalsMesh.hpp
/// \brief Declaration of Mesh subclass for meshes with Normal vector data.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// System includes

/******************************************************************/
// Local includes
#include "Mesh.hpp"

/******************************************************************/

class NormalsMesh : public Mesh
{
public:
  /// \brief Initial value constructor
  NormalsMesh(OpenGLContext* context, ShaderProgram* shader);

  /// \brief Constructs a NormalsMesh with triangles pulled from a file.
  /// \param[in] context A pointer to an objec tthrough which the Mesh will be
  ///   able to make OpenGL calls.
  /// \param[in] shader A pointer to the shader program that should be used for
  ///   drawing this mesh.
  /// \param[in] fileName The name of the file this mesh's geometry should be
  ///   read from.
  /// \param[in] meshNum The 0-based index of which mesh from that file should
  ///   be used.
  /// \post A unique VAO, VBO, and IBO have been generated for this Mesh and
  ///   stored for later use.
  /// \post If that file exists and contains a mesh of that number, the indexes
  ///   and geometry from it have been pre-populated into this Mesh.  Otherwise
  ///   this Mesh is empty and an error message has been printed.
  NormalsMesh (OpenGLContext* context, ShaderProgram* shader, std::string fileName, 
    unsigned int meshNum);


  virtual unsigned int
  getFloatsPerVertex() const;
protected:
  virtual void
  enableAttributes();

};
