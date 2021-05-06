/// \file KeyBuffer.hpp
/// \brief Implementation of KeyBuffer class and any associated global functions.
/// \author Sean Malloy
/// \version A04

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "KeyBuffer.hpp"

KeyBuffer::KeyBuffer()
{
  for (int key = 0; key < GLFW_KEY_LAST + 1; ++key)
    keyIsPressed[key] = false;
}

void
KeyBuffer::setKeyDown(int key)
{
  keyIsPressed[key] = true;
}

void
KeyBuffer::reset()
{
  *this = KeyBuffer();
}

void
KeyBuffer::setKeyUp(int key)
{
  keyIsPressed[key] = false;
}

bool
KeyBuffer::isKeyDown(int key) const
{
  return keyIsPressed[key];
}