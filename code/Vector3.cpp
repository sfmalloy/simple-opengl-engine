/// \file Vector3.cpp
/// \brief Implementation of Vector class and any associated global functions.
/// \author Sean Malloy
/// \version A04

#include <iostream>
#include <iomanip>
#include <cmath>

// Helper functions
bool
almostEqual(float a, float b);

#include "Vector3.hpp"

Vector3::Vector3()
{
  *this = Vector3(0);
}

Vector3::Vector3(float xyz)
{
  *this = Vector3(xyz, xyz, xyz);
}

Vector3::Vector3(float x, float y, float z)
  : m_x(x),
    m_y(y),
    m_z(z)
{
}

void
Vector3::set(float xyz)
{
  *this = Vector3(xyz);
}

void
Vector3::set(float x, float y, float z)
{
  *this = Vector3(x, y, z);
}

void
Vector3::negate()
{
  *this = Vector3(-m_x, -m_y, -m_z);
}

float
Vector3::dot(const Vector3& v) const
{
  return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
}

float
Vector3::angleBetween(const Vector3& v) const
{
  return std::acos(this->dot(v) / (this->length() * v.length()));
}

Vector3
Vector3::cross(const Vector3& v) const
{
  Vector3 crossProd;
  crossProd.m_x = (m_y * v.m_z) - (m_z * v.m_y);
  crossProd.m_y = (m_z * v.m_x) - (m_x * v.m_z);
  crossProd.m_z = (m_x * v.m_y) - (m_y * v.m_x);

  return crossProd;
}

float
Vector3::length() const
{
  return std::sqrt(std::pow(m_x, 2.0f) + std::pow(m_y, 2.0f) + std::pow(m_z, 2.0f));
}

void
Vector3::normalize()
{
  *this /= this->length();
}

Vector3&
Vector3::operator+=(const Vector3& v)
{
  *this = Vector3(m_x + v.m_x, m_y + v.m_y, m_z + v.m_z);
  return *this;
}

Vector3&
Vector3::operator-=(const Vector3& v)
{
  *this = Vector3(m_x - v.m_x, m_y - v.m_y, m_z - v.m_z);
  return *this;
}

Vector3&
Vector3::operator*=(float s)
{
  *this = Vector3(s * m_x, s * m_y, s * m_z);
  return *this;
}

Vector3&
Vector3::operator/=(float s)
{
  *this = Vector3(m_x / s, m_y / s, m_z / s);
  return *this;
}

Vector3
operator+(const Vector3& v1, const Vector3& v2)
{
  return (Vector3) v1 += v2;
}

Vector3
operator-(const Vector3& v1, const Vector3& v2)
{
  return (Vector3) v1 -= v2;
}

Vector3
operator-(const Vector3& v)
{
  Vector3 vCopy = v;
  vCopy.negate();
  return vCopy;
}

Vector3
operator*(float s, const Vector3& v)
{
  return (Vector3) v *= s;
}

Vector3
operator*(const Vector3& v, float s)
{
  return (Vector3) v *= s;
}

Vector3
operator/(const Vector3& v, float s)
{
  return (Vector3) v /= s;
}

std::ostream&
operator<<(std::ostream& out, const Vector3& v)
{
  out << std::setprecision(2) << std::fixed << std::right
      << std::setw(10) << v.m_x
      << std::setw(10) << v.m_y
      << std::setw(10) << v.m_z;

  return out;
}

bool
operator==(const Vector3& v1, const Vector3& v2)
{
  return almostEqual(v1.m_x, v2.m_x) && almostEqual(v1.m_y, v2.m_y) && almostEqual(v1.m_z, v2.m_z);
}

bool
almostEqual(float a, float b)
{
  float diff = std::fabs(a - b);
  float epsilon = 0.00001f;
  return diff <= epsilon;
}