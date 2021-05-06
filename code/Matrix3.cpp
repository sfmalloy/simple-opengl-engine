/// \file Matrix3.hpp
/// \brief Implementation of Matrix3 class and any associated global functions.
/// \author Sean Malloy
/// \version A05
/******************************************/
#include <iostream>
#include <cmath>

#include "Vector3.hpp"
#include "Matrix3.hpp"

/******************************************/
// Helper functions
float
minorDet(int r, int c, const Matrix3& A)
{
  float minor[4];
  float* m = &minor[0];
  auto dataPtr = A.data();
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j, ++dataPtr)
    {
      if (i != r && j != c)
      {
        *m = *dataPtr;
        ++m;
      }
    }
  }

  return (minor[0] * minor[3]) - (minor[2] * minor[1]);
}

float
radians(float degrees)
{
  return degrees * (M_PI / 180.0f);
}

/******************************************/
// Class functions

Matrix3::Matrix3()
  : m_right(1.0f, 0.0f, 0.0f),
    m_up(0.0f, 1.0f, 0.0f),
    m_back(0.0f, 0.0f, 1.0f)
{
}

Matrix3::Matrix3(float rx, float ry, float rz,
                 float ux, float uy, float uz,
                 float bx, float by, float bz)
  : m_right(rx, ry, rz),
    m_up(ux, uy, uz),
    m_back(bx, by, bz)
{
}

Matrix3::Matrix3(const Vector3& right, const Vector3& up, const Vector3& back)
  : m_right(right),
    m_up(up),
    m_back(back)
{
}

Matrix3::Matrix3(const Vector3& right, const Vector3& up, bool makeOrthonormal)
  : m_right(right),
    m_up(up),
    m_back(m_right.cross(m_up))
{
  if (makeOrthonormal)
    orthonormalize();
}

Matrix3::~Matrix3()
{
}

void
Matrix3::setToIdentity()
{
  *this = Matrix3();
}

void
Matrix3::setToZero()
{
  m_right.set(0.0f);
  m_up.set(0.0f);
  m_back.set(0.0f);
}

float*
Matrix3::data()
{
  return &(m_right.m_x);
}

const float*
Matrix3::data() const
{
  return &(m_right.m_x);
}

void
Matrix3::setRight(const Vector3& right)
{
  m_right = right;
}

Vector3
Matrix3::getRight() const
{
  return m_right;
}

void
Matrix3::setUp(const Vector3& up)
{
  m_up = up;
}

Vector3
Matrix3::getUp() const
{
  return m_up;
}

void
Matrix3::setBack(const Vector3& back)
{
  m_back = back;
}

Vector3
Matrix3::getBack() const
{
  return m_back;
}

void
Matrix3::setForward(const Vector3& forward)
{
  m_back = -forward;
}

Vector3
Matrix3::getForward() const
{
  return -m_back;
}

void
Matrix3::invertRotation()
{
  transpose();
}

void
Matrix3::invert()
{
  Matrix3 thisCopy = *this;
  // Calculates the adjugate matrix by getting the cofactor of element (i, j)
  // Which is the same as the determinant of the 2x2 minor matrix of (i, j)
  auto dataPtr = thisCopy.data();
  float sign = 1.0f;
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j, ++dataPtr)
    {
      *dataPtr = sign * minorDet(j, i, *this);
      sign *= -1.0f;
    }
  }
  
  *this = thisCopy * (1.0f / determinant());
}

float
Matrix3::determinant() const
{
  auto dataPtr = data();
  float det = 0.0f;
  float sign = 1.0f;
  
  for (int i = 0; i < 3; ++i, ++dataPtr)
  {
    det += *dataPtr * minorDet(0, i, *this) * sign;
    sign *= -1.0f;
  }

  return det;
}

void
Matrix3::transpose()
{
  Vector3 newRight(m_right.m_x, m_up.m_x, m_back.m_x);
  Vector3 newUp(m_right.m_y, m_up.m_y, m_back.m_y);
  Vector3 newBack(m_right.m_z, m_up.m_z, m_back.m_z);

  *this = Matrix3(newRight, newUp, newBack);
}

void
Matrix3::orthonormalize()
{
  m_back.normalize();

  m_right = m_up.cross(m_back);
  m_right.normalize();

  m_up = m_back.cross(m_right);
  m_up.normalize();
}

void
Matrix3::setToScale(float scale)
{
  setToIdentity();
  *this *= scale;
}

void
Matrix3::setToScale(float scaleX, float scaleY, float scaleZ)
{
  Matrix3 scaleMatrix(scaleX, 0.0f, 0.0f, 0.0f, scaleY, 0.0f, 0.0f, 0.0f, scaleZ);
  *this = scaleMatrix;
}

void
Matrix3::setToShearXByYz(float shearY, float shearZ)
{
  Matrix3 shearMatrix(1.0f, 0.0f, 0.0f, shearY, 1.0f, 0.0f, shearZ, 0.0f, 1.0f);
  *this = shearMatrix;
}

void
Matrix3::setToShearYByXz(float shearX, float shearZ)
{
  Matrix3 shearMatrix(1.0f, shearX, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, shearZ, 1.0f);
  *this = shearMatrix;
}

void
Matrix3::setToShearZByXy(float shearX, float shearY)
{
  Matrix3 shearMatrix(1.0f, 0.0f, shearX, 0.0f, 1.0f, shearY, 0.0f, 0.0f, 1.0f);
  *this = shearMatrix;
}

void
Matrix3::setToRotationX(float angleDegrees)
{
  Vector3 rotAxis(1.0f, 0.0f, 0.0f);
  setFromAngleAxis(angleDegrees, rotAxis);
}

void
Matrix3::setToRotationY(float angleDegrees)
{
  Vector3 rotAxis(0.0f, 1.0f, 0.0f);
  setFromAngleAxis(angleDegrees, rotAxis);
}

void
Matrix3::setToRotationZ(float angleDegrees)
{
  Vector3 rotAxis(0.0f, 0.0f, 1.0f);
  setFromAngleAxis(angleDegrees, rotAxis);
}

// applies the Rodrigues Rotation formula 
// https://mathworld.wolfram.com/RodriguesRotationFormula.html
void
Matrix3::setFromAngleAxis(float angleDegrees, const Vector3& axis)
{  
  setToIdentity();

  Vector3 normAxis = axis;
  normAxis.normalize();

  float angleRadians = radians(angleDegrees);

  Matrix3 omega(0.0f, normAxis.m_z, -normAxis.m_y, 
                -normAxis.m_z, 0.0f, normAxis.m_x, 
                normAxis.m_y, -normAxis.m_x, 0.0f);
  
  *this += (omega * std::sin(angleRadians)) + 
    ((omega * omega) * (1 - std::cos(angleRadians)));
}

void
Matrix3::negate()
{
  *this *= -1.0f;
}

Vector3
Matrix3::transform(const Vector3& v) const
{
  return *this * v;
}

Matrix3&
Matrix3::operator+=(const Matrix3& m)
{
  auto thisData = data();
  auto mData = m.data();

  for (int i = 0; i < 9; ++i, ++thisData, ++mData)
    *thisData += *mData;

  return *this;
}

Matrix3&
Matrix3::operator-=(const Matrix3& m)
{
  auto thisData = data();
  auto mData = m.data();

  for (int i = 0; i < 9; ++i, ++thisData, ++mData)
    *thisData -= *mData;

  return *this;
}

Matrix3&
Matrix3::operator*=(float scalar)
{
  auto thisData = data();

  for (int i = 0; i < 9; ++i, ++thisData)
    *thisData *= scalar;

  return *this;
}

Matrix3&
Matrix3::operator*=(const Matrix3& m)
{
  transpose();

  Vector3 r(m_right.dot(m.getRight()), m_up.dot(m.getRight()), m_back.dot(m.getRight()));
  Vector3 u(m_right.dot(m.getUp()), m_up.dot(m.getUp()), m_back.dot(m.getUp()));
  Vector3 b(m_right.dot(m.getBack()), m_up.dot(m.getBack()), m_back.dot(m.getBack()));
  *this = Matrix3(r, u, b);

  return *this;
}

Matrix3
operator+(const Matrix3& m1, const Matrix3& m2)
{
  return (Matrix3) m1 += m2;
}

Matrix3
operator-(const Matrix3& m1, const Matrix3& m2)
{
  return (Matrix3) m1 -= m2;
}

Matrix3
operator-(const Matrix3& m)
{
  return (Matrix3) m *= -1.0f;
}

Matrix3
operator*(const Matrix3& m, float scalar)
{
  return (Matrix3) m *= scalar;
}

Matrix3
operator*(float scalar, const Matrix3& m)
{
  return (Matrix3) m *= scalar;
}

Matrix3
operator*(const Matrix3& m1, const Matrix3& m2)
{
  return (Matrix3) m1 *= m2;
}

Vector3
operator*(const Matrix3& m, const Vector3& v)
{
  Matrix3 mTransposed = m;
  mTransposed.transpose();
  return Vector3(mTransposed.getRight().dot(v), mTransposed.getUp().dot(v), 
    mTransposed.getBack().dot(v));
}

std::ostream&
operator<<(std::ostream& out, const Matrix3& m)
{
  Matrix3 mCopy = m;
  mCopy.transpose();

  out << mCopy.getRight() << '\n';
  out << mCopy.getUp() << '\n';
  out << mCopy.getBack() << '\n';

  return out;
}

bool
operator==(const Matrix3& m1, const Matrix3& m2)
{
  return m1.getRight() == m2.getRight() && m1.getUp() == m2.getUp() &&
    m1.getBack() == m2.getBack();
}