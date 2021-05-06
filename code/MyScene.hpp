/// \file MyScene.hpp
/// \brief Declaration of MyScene which is a subclass of Scene.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// Macro guard
#ifndef MYSCENE_HPP
#define MYSCENE_HPP

/******************************************************************/
// Local includes
#include "Scene.hpp"
#include "OpenGLContext.hpp"
#include "ShaderProgram.hpp"

/******************************************************************/
class MyScene : public Scene
{
public:
  MyScene(OpenGLContext* context, ShaderProgram* shaderColorInfo, ShaderProgram* shaderNormalVectors);

  MyScene(const MyScene&) = delete;

  void
  operator=(const MyScene&) = delete;
  
private:

};

#endif // MYSCENE_HPP