/// \file Main.cpp
/// \brief Declaration of main function, helper functions, and helper classes.
/// \author Gary M. Zopetti, Chad Hogg, Sean Malloy
/// \version A08
///
/// This is a fairly simple program that uses OpenGL 3.3 to draw a scene.  It
///   allows limited movement of a very simple virtual camera.

/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>

// GLM is a header-only library, so we do not need to link to it
// It provides matrix classes and mathematical functions

/******************************************************************/
// Local includes
#include "RealOpenGLContext.hpp"
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Scene.hpp"
#include "MyScene.hpp"
#include "Camera.hpp"
#include "Vector3.hpp"
#include "KeyBuffer.hpp"
#include "Transform.hpp"
#include "MouseBuffer.hpp"
#include "Matrix4.hpp"

/******************************************************************/
// Global variables

/// \brief The OpenGLContext through which all OpenGL calls will be made.
///
/// This should be allocated in ::init and deallocated in ::releaseGlResources.
OpenGLContext* g_context;

// We use one VAO for each object we draw
/// \brief A collection of the VAOs for each of the objects we want to draw.
///
/// This will be filled in initScene, and its contents need to be deleted in
///   releaseGlResources.
Scene* g_scene;

/// \brief The ShaderProgram that transforms and lights the primitives that
///   provide color info in their Meshes.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_shaderColorInfo;

/// \brief The ShaderProgram that transforms and lights the primitives that
///   provide normal vectors in their Meshes.
///
/// This should be allocated in ::initShaders and deallocated in
///   ::releaseGlResources.
ShaderProgram* g_shaderNormalVectors;

/// \brief The Camera that views the Scene.
///
/// This should be allocated in ::initCamera and deallocated in
///   ::releaseGlResources.
Camera* g_camera;

/// \brief Key buffer that allows keeping track of which keys are pressed
KeyBuffer g_keyBuffer;

/// \brief Mouse buffer that allows keeping track of pressed mouse buttons
///   and the current mouse position.
MouseBuffer g_mouseBuffer;

/// \brief Keeps track of current vertical field of view for mouse scrolling.
double g_verticalFov;

/******************************************************************/
// Function prototypes

/// \brief Initializes all libraries and global variables.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
///
/// This should be called once at the beginning of the application.
void
init(GLFWwindow*& window);

/// \brief Initializes the GLFW library.  Should only be called by ::init.
void
initGlfw();

/// \brief Initializes the GLEW library.  Should only be called by ::init.
void
initGlew();

/// \brief Creates and initializes the window.  Should only be called by
///   ::init.
/// \param[out] window A pointer that will be filled with a GLFWwindow.
void
initWindow(GLFWwindow*& window);

/// \brief Re-renders the window.  This should be called whenever the window
///   size changes.
/// \param[in] window The GLFWwindow to reset.
/// \param[in] width The new width of the window.
/// \param[in] height The new height of the window.
void
resetViewport(GLFWwindow* window, int width, int height);

/// \brief Creates the Scene.  Should only be called by ::init.
void
initScene();

/// \brief Creates the ShaderProgram.  Should only be called by ::init.
void
initShaders();

/// \brief Initializes the Camera.  Should only be called by ::init.
void
initCamera();

/// \brief Moves geometric objects around using game logic.  This should be
///   called for every frame.
/// \param[in] time The number of seconds since the previous update.
void
updateScene(double time);

/// \brief Draws the Scene onto the window.  This should be called for every
///   frame.
/// \param[in] window The GLFWwindow to draw in.
void
drawScene(GLFWwindow* window);

/// \brief Responds to any user input.  This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] key The key that was pressed or released.
/// \param[in] scanCode The system-specific scancode of the key.
/// \param[in] action What happened to the key.
/// \param[in] modifiers Which modifier keys were depressed.
void
recordKeys(GLFWwindow* window, int key, int scanCode, int action,
            int modifiers);

/// \brief Responds to mouse input. This should be set as a callback.
/// \param[in] window The GLFWwindow the input came from.
/// \param[in] button The button that was pressed or released
/// \param[in] action What happened to the button
/// \param[in] modifiers Which modifier buttons were pressed.
void
recordMouse(GLFWwindow* window, int button, int action, int modifiers);

/// \brief Responds to mouse scroll input. Should be set as a callback.
/// \param[in] window The GFLWwindow the input came from.
/// \param[in] xOffset The amount the horizontal wheel was scrolled. 
///   In our case we ignore the xOffset
/// \param[in] yOffset The amount the vertical wheel was scrolled.
void
processScroll(GLFWwindow* window, double xOffset, double yOffset);

/// \brief Processes keys that are pressed and performs necessary actions
///   for those pressed keys.
void
processKeys();

/// \brief Process mouse buttons that are pressed and mouse movement to
///   rotate camera depending on those inputs
/// \param[in] window The window the mouse actions take place.
void
processMouse(GLFWwindow* window);

/// \brief Cleans up all resources as program exits.
void
releaseGlResources();

/// \brief Prints an error from GLFW.
/// \param[in] error The error code.
/// \param[in] description The error text.
void
outputGlfwError(int error, const char* description);

/******************************************************************/

/// \brief Runs our program.
/// \param[in] argc The number of command-line arguments, which we ignore.
/// \param[in] argv The array of command-line-arguments, which we ignore.
int
main(int argc, char* argv[])
{
  GLFWwindow* window;
  init(window);

  // Game/render loop
  double previousTime = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    double currentTime = glfwGetTime();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene(deltaTime);
    drawScene(window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents();
    processKeys();
    processMouse(window);
  }

  releaseGlResources();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init(GLFWwindow*& window)
{
  g_context = new RealOpenGLContext();
  // Always initialize GLFW before GLEW
  initGlfw();
  initWindow(window);
  initGlew();
  initShaders();
  initCamera();
  initScene();
}

/******************************************************************/

void
initGlfw()
{
  glfwSetErrorCallback(outputGlfwError);
  if (!glfwInit())
  {
    fprintf(stderr, "Failed to init GLFW -- exiting\n");
    exit(EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow(GLFWwindow*& window)
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow(800, 600, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf(stderr, "Failed to init the window -- exiting\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetWindowPos(window, 200, 100);

  glfwMakeContextCurrent(window);
  // Swap buffers after 1 frame
  glfwSwapInterval(1);
  glfwSetKeyCallback(window, recordKeys);
  glfwSetFramebufferSizeCallback(window, resetViewport);
  glfwSetMouseButtonCallback(window, recordMouse);
  glfwSetScrollCallback(window, processScroll);

  // Specify background color
  g_context->clearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  g_context->enable(GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  g_context->enable(GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  g_context->frontFace(GL_CCW);
  g_context->cullFace(GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  g_context->viewport(0, 0, width, height);
}

/******************************************************************/

void
initGlew()
{
  GLenum status = glewInit();
  if (status != GLEW_OK)
  {
    fprintf(stderr,
            "Failed to initialize GLEW -- exiting"
            " (%s).\n",
            glewGetErrorString(status));
    exit(EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString(GLEW_VERSION);
  fprintf(stderr, "Using GLEW version %s.\n", version);
  version = g_context->getString(GL_VERSION);
  fprintf(stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport(GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  g_camera->setProjectionSymmetricPerspective(g_verticalFov, 1200.0 / 900.0, 0.01, 40.0);
  g_context->viewport(0, 0, width, height);
}

/******************************************************************/

void
initScene()
{
  g_scene = new MyScene(g_context, g_shaderColorInfo, g_shaderNormalVectors);
}

/******************************************************************/

void
initShaders()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderColorInfo = new ShaderProgram(g_context);
  g_shaderColorInfo->createVertexShader("Vec3.vert");
  g_shaderColorInfo->createFragmentShader("Vec3.frag");
  g_shaderColorInfo->link();

  g_shaderNormalVectors = new ShaderProgram(g_context);
  g_shaderNormalVectors->createVertexShader("Vec3Norm.vert");
  g_shaderNormalVectors->createFragmentShader("Vec3.frag");
  g_shaderNormalVectors->link();
}

/******************************************************************/

void
initCamera()
{
  g_verticalFov = 50.0f;
  float aspectRatio = 1200.0f / 900.0f;
  // Near plane
  float nearZ = 0.01f;
  // Far plane
  float farZ = 40.0f;

  // Define the camera's coordinate system
  Vector3 position(0, 0, 12.0f);
  Vector3 localBack(0, 0, 1.0f);

  g_camera = new Camera(position, localBack, nearZ, farZ, aspectRatio, g_verticalFov);
}

/******************************************************************/

void
updateScene(double time)
{
  // No updates in this simple program.
}

/******************************************************************/

void
drawScene(GLFWwindow* window)
{
  Transform modelView = g_camera->getViewMatrix();
  Matrix4 projection = g_camera->getProjectionMatrix();

  g_context->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  g_scene->draw(modelView, projection);

  glfwSwapBuffers(window);
}

/******************************************************************/

void
recordKeys(GLFWwindow* window, int key, int scanCode, int action,
            int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
    return;
  }

  if (action == GLFW_PRESS)
    g_keyBuffer.setKeyDown(key);
  else if (action == GLFW_RELEASE)
    g_keyBuffer.setKeyUp(key);
}

void
recordMouse(GLFWwindow* window, int button, int action, int modifiers)
{
  if (action == GLFW_PRESS)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      g_mouseBuffer.setLeftButton(true);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
      g_mouseBuffer.setRightButton(true);
  }
  else if (action == GLFW_RELEASE)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      g_mouseBuffer.setLeftButton(false);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
      g_mouseBuffer.setRightButton(false);
  }
}

void
processScroll(GLFWwindow* window, double xOffset, double yOffset)
{
  g_verticalFov += yOffset;
  g_verticalFov = g_verticalFov < 120.0f ? g_verticalFov : 120.0f;
  g_verticalFov = g_verticalFov > 1.0f ? g_verticalFov : 1.0f;
  g_camera->setProjectionSymmetricPerspective(g_verticalFov, 1200.0 / 900.0, 0.01, 40.0);
}

void
processKeys()
{
  const float MOVEMENT_DELTA = 0.01f;
  const float DEGREE_DELTA   = 0.05f;
  const float SCALE_UP       = 1.01f;
  const float SCALE_DOWN     = 0.99f;

  for (int key = 0; key < GLFW_KEY_LAST; ++key)
  {
    // Translate camera/eye point using WASD keys
    if (g_keyBuffer.isKeyDown(key))
    {
      if (key == GLFW_KEY_W)
        g_camera->moveBack(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_S)
        g_camera->moveBack(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_A)
        g_camera->moveRight(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_D)
        g_camera->moveRight(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_C)
        g_camera->moveUp(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_F)
        g_camera->moveUp(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_R)
        g_camera->resetPose();
      else if (key == GLFW_KEY_J)
        g_scene->getActiveMesh()->yaw(DEGREE_DELTA);
      else if (key == GLFW_KEY_L)
        g_scene->getActiveMesh()->yaw(-DEGREE_DELTA);
      else if (key == GLFW_KEY_I)
        g_scene->getActiveMesh()->pitch(DEGREE_DELTA);
      else if (key == GLFW_KEY_K)
        g_scene->getActiveMesh()->pitch(-DEGREE_DELTA);
      else if (key == GLFW_KEY_N)
        g_scene->getActiveMesh()->roll(DEGREE_DELTA);
      else if (key == GLFW_KEY_M)
        g_scene->getActiveMesh()->roll(-DEGREE_DELTA);
      else if (key == GLFW_KEY_1)
        g_scene->getActiveMesh()->moveRight(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_2)
        g_scene->getActiveMesh()->moveRight(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_3)
        g_scene->getActiveMesh()->moveUp(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_4)
        g_scene->getActiveMesh()->moveUp(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_5)
        g_scene->getActiveMesh()->moveBack(MOVEMENT_DELTA);
      else if (key == GLFW_KEY_6)
        g_scene->getActiveMesh()->moveBack(-MOVEMENT_DELTA);
      else if (key == GLFW_KEY_7)
        g_scene->getActiveMesh()->scaleLocal(SCALE_UP);
      else if (key == GLFW_KEY_8)
        g_scene->getActiveMesh()->scaleLocal(SCALE_DOWN);
      else if (key == GLFW_KEY_MINUS)
      {
        g_scene->activatePreviousMesh();
        g_keyBuffer.setKeyUp(GLFW_KEY_MINUS);
      }
      else if (key == GLFW_KEY_EQUAL)
      {
        g_scene->activateNextMesh();
        g_keyBuffer.setKeyUp(GLFW_KEY_EQUAL);
      }
      else if (key == GLFW_KEY_P)
      {
        g_camera->setProjectionSymmetricPerspective(50.0, 1200.0 / 900.0, 0.01, 40.0);
        g_keyBuffer.setKeyUp(GLFW_KEY_P);
      }
      else if (key == GLFW_KEY_LEFT_BRACKET)
      {
        g_camera->setProjectionAsymmetricPerspective(-4.0, 6.0, -6.0, 5.0, 2.0, 20.0);
        g_keyBuffer.setKeyUp(GLFW_KEY_LEFT_BRACKET);
      }
      else if (key == GLFW_KEY_O)
      {
        g_camera->setProjectionOrthographic(-4.0, 6.0, -6.0, 5.0, 0.01, 30.0);
        g_keyBuffer.setKeyUp(GLFW_KEY_O);
      }
    }
  }
}

void
processMouse(GLFWwindow* window)
{
  double currXPos, currYPos;
  glfwGetCursorPos(window, &currXPos, &currYPos);
  
  double degrees = 0.05;

  if (g_mouseBuffer.getLeftButton())
  {
    double dx = currXPos - g_mouseBuffer.getX();
    double dy = currYPos - g_mouseBuffer.getY();
    g_camera->yaw(degrees * dx);
    g_camera->pitch(degrees * dy);
  }
  else if (g_mouseBuffer.getRightButton())
  {
    double dx = currXPos - g_mouseBuffer.getX();
    g_camera->roll(degrees * dx);
  }

  g_mouseBuffer.setPosition(currXPos, currYPos);
}
/******************************************************************/

void
releaseGlResources()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  delete g_camera;
  delete g_shaderColorInfo;
  delete g_shaderNormalVectors;
  delete g_scene;
  delete g_context;
}

/******************************************************************/

void
outputGlfwError(int error, const char* description)
{
  fprintf(stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/
