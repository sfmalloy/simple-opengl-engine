/// \file MyScene.cpp
/// \brief Implementation of MyScene class.
/// \author Sean Malloy
/// \version A08
/******************************************************************/
// System includes
#include <vector>
#include <cmath>

/******************************************************************/
// Local includes
#include "Scene.hpp"
#include "MyScene.hpp"
#include "OpenGLContext.hpp"
#include "Geometry.hpp"
#include "ColorsMesh.hpp"
#include "NormalsMesh.hpp"

/******************************************************************/

MyScene::MyScene(OpenGLContext* context, ShaderProgram* shaderColorInfo, ShaderProgram* shaderNormalVectors)
{
  // Constants needed for decagon
  const float x1Deca = std::cos(36.0f * M_PI/ 180.0f);
  const float y1Deca = std::sin(36.0f * M_PI/ 180.0f);

  const float x2Deca = std::cos(72.0f * M_PI/ 180.0f);
  const float y2Deca = std::sin(72.0f * M_PI/ 180.0f);

  const float xCenterDeca = x2Deca + x1Deca - 3.5;
  const float yCenterDeca = 0.0f;

  std::vector<float> decagon {
    // Front side
    -4.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca - 4.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca - 4.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 4.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + x1Deca - 4.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 3.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + x1Deca - 3.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + 2*x1Deca - 3.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + 2*x1Deca - 3.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    2*x2Deca + 2*x1Deca - 3.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    2*x2Deca + 2*x1Deca - 3.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + 2*x1Deca - 3.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + 2*x1Deca - 3.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 3.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + x1Deca - 3.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 4.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,
    
    x2Deca + x1Deca - 4.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca - 4.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca - 4.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    -4.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, 0.0f,
    1.0f, 0.0f, 0.0f,

    // Back side
    -4.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca - 4.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca - 4.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 4.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f, 

    x2Deca + x1Deca - 4.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 3.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f, 

    x2Deca + x1Deca - 3.0f, y2Deca + y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + 2*x1Deca - 3.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + 2*x1Deca - 3.0f, y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    2*x2Deca + 2*x1Deca - 3.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    2*x2Deca + 2*x1Deca - 3.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + 2*x1Deca - 3.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + 2*x1Deca - 3.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 3.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + x1Deca - 3.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca + x1Deca - 4.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca + x1Deca - 4.0f, -y2Deca - y1Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    x2Deca - 4.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,

    x2Deca - 4.0f, -y2Deca, 0.0f,
    0.0f, 1.0f, 1.0f,
    -4.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 1.0f,
    xCenterDeca, yCenterDeca, -2.0f,
    1.0f, 0.0f, 0.0f,
  };

  std::vector<float> decagonData;
  std::vector<unsigned int> decagonIndices;
  indexData(decagon, 6, decagonData, decagonIndices);

  this->add("decagon", new ColorsMesh(context, shaderColorInfo));
  this->getMesh("decagon")->addGeometry(decagonData);
  this->getMesh("decagon")->addIndices(decagonIndices);
  this->getMesh("decagon")->moveRight(-1.0f);
  this->getMesh("decagon")->pitch(50.0f);
  this->getMesh("decagon")->prepareVao();
  
  // Constants for octacone
  const float x1Octa = M_SQRT2 / 2.0f;
  const float y1Octa = M_SQRT2 / 2.0f;

  const float xCenterOcta = (M_SQRT2 + 1.0f) / 2.0f;
  const float yCenterOcta = -1.0f / 2.0f;

  std::vector<float> octacone {
    // Octagonal base of cone
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa + 1, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa + 1, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    2*x1Octa + 1, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    2*x1Octa + 1, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    2*x1Octa + 1, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    2*x1Octa + 1, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa + 1, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa + 1, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 0.0f,
    0.0f, 0.0f, 1.0f,

    // Cone part
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa + 1, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa + 1, -(1.0f + y1Octa), 0.0f,
    1.0f, 0.0f, 0.0f,
    2*x1Octa + 1, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,

    2*x1Octa + 1, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    2*x1Octa + 1, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,
    
    2*x1Octa + 1, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa + 1, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa + 1, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    x1Octa, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f,

    x1Octa, y1Octa, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    xCenterOcta, yCenterOcta, 4.0f,
    0.0f, 0.0f, 1.0f
  };

  std::vector<float> octaconeData;
  std::vector<unsigned int> octaconeIndices;
  indexData(octacone, 6, octaconeData, octaconeIndices);

  this->add("octacone", new ColorsMesh(context, shaderColorInfo));
  this->getMesh("octacone")->addGeometry(octaconeData);
  this->getMesh("octacone")->addIndices(octaconeIndices);
  this->getMesh("octacone")->shearLocalXByYz(0.5f, 0.5f);
  this->getMesh("octacone")->moveWorld(2.0f, Vector3(-1.0f, 2.0f, -1.0f));
  this->getMesh("octacone")->prepareVao();

  std::vector<Triangle> cube = buildCube();
  
  ColorsMesh* cubeRandomFaceColors = new ColorsMesh(context, shaderColorInfo);
  std::vector<Vector3> randomFaceColors = generateRandomFaceColors(cube);
  std::vector<float> randomFaceColorsGeometry = dataWithFaceColors(cube, randomFaceColors);
  std::vector<float> randomFaceColorsData;
  std::vector<unsigned int> randomFaceColorsIndices;
  indexData(randomFaceColorsGeometry, cubeRandomFaceColors->getFloatsPerVertex(), 
    randomFaceColorsData, randomFaceColorsIndices);
  this->add("cubeRandomFaceColors", cubeRandomFaceColors);
  this->getMesh("cubeRandomFaceColors")->addGeometry(randomFaceColorsData);
  this->getMesh("cubeRandomFaceColors")->addIndices(randomFaceColorsIndices);
  this->getMesh("cubeRandomFaceColors")->moveUp(-4.0f);
  this->getMesh("cubeRandomFaceColors")->moveRight(-2.0f);
  this->getMesh("cubeRandomFaceColors")->prepareVao();

  ColorsMesh* cubeRandomVertexColors = new ColorsMesh(context, shaderColorInfo);
  std::vector<Vector3> randomVertexColors = generateRandomVertexColors(cube);
  std::vector<float> randomVertexColorsGeometry = dataWithVertexColors(cube, randomVertexColors);
  std::vector<float> randomVertexColorsData;
  std::vector<unsigned int> randomVertexColorsIndices;
  indexData(randomVertexColorsGeometry, cubeRandomVertexColors->getFloatsPerVertex(), 
    randomVertexColorsData, randomVertexColorsIndices);
  this->add("cubeRandomVertexColors", cubeRandomVertexColors);
  this->getMesh("cubeRandomVertexColors")->addGeometry(randomVertexColorsData);
  this->getMesh("cubeRandomVertexColors")->addIndices(randomVertexColorsIndices);
  this->getMesh("cubeRandomVertexColors")->moveUp(-3.0f);
  this->getMesh("cubeRandomVertexColors")->moveRight(2.0f);
  this->getMesh("cubeRandomVertexColors")->prepareVao();

  NormalsMesh* cubeFaceNormals = new NormalsMesh(context, shaderNormalVectors);
  std::vector<Vector3> faceNormals = computeFaceNormals(cube);
  std::vector<float> faceNormalsGeometry = dataWithFaceNormals(cube, faceNormals);
  std::vector<float> faceNormalsData;
  std::vector<unsigned int> faceNormalsIndices;
  indexData(faceNormalsGeometry, cubeFaceNormals->getFloatsPerVertex(), 
    faceNormalsData, faceNormalsIndices);
  this->add("cubeFaceNormals", cubeFaceNormals);
  this->getMesh("cubeFaceNormals")->addGeometry(faceNormalsData);
  this->getMesh("cubeFaceNormals")->addIndices(faceNormalsIndices);
  this->getMesh("cubeFaceNormals")->moveUp(-2.0f);
  this->getMesh("cubeFaceNormals")->moveRight(-2.0f);
  this->getMesh("cubeFaceNormals")->prepareVao();

  NormalsMesh* cubeVertexNormals = new NormalsMesh(context, shaderNormalVectors);
  std::vector<Vector3> vertexNormals = computeVertexNormals(cube, faceNormals);
  std::vector<float> vertexNormalsGeometry = dataWithVertexNormals(cube, vertexNormals);
  std::vector<float> vertexNormalsData;
  std::vector<unsigned int> vertexNormalsIndices;
  indexData(vertexNormalsGeometry, cubeVertexNormals->getFloatsPerVertex(), 
    vertexNormalsData, vertexNormalsIndices);
  this->add("cubeVertexNormals", cubeVertexNormals);
  this->getMesh("cubeVertexNormals")->addGeometry(vertexNormalsData);
  this->getMesh("cubeVertexNormals")->addIndices(vertexNormalsIndices);
  this->getMesh("cubeVertexNormals")->moveUp(-1.0f);
  this->getMesh("cubeVertexNormals")->moveRight(2.0f);
  this->getMesh("cubeVertexNormals")->prepareVao();

  NormalsMesh* bear = new NormalsMesh(context, shaderNormalVectors, "models/bear.obj", 0);
  this->add("bear", bear);
  this->getMesh("bear")->scaleWorld(0.1f);
  this->getMesh("bear")->yaw(30.0f);
  this->getMesh("bear")->moveWorld(-15.0f, Vector3(0.0f, 1.0f, 0.0f));
  this->getMesh("bear")->prepareVao();
}