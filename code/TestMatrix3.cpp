/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Sean Malloy
/// \version A05

#include <sstream>

#include "Matrix3.hpp"
#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

SCENARIO("Matrix3 Constructors", "[Matrix3][A05]") {
  GIVEN("Nothing at all.") {
    WHEN("I use the default Matrix3 constructor.") {
      Matrix3 A;
      THEN("rx, uy, bz are 1.0f while all other elements should be 0.0f") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("I pass 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, -6.0f, -7.0f, 8.1f, 9.9f " +
          "into the constructor with 9 parameters") {
      Matrix3 B(1.0f, 2.0f, 3.0f, 
                4.0f, 5.0f, -6.0f, 
                -7.0f, 8.1f, 9.9f);
      THEN("The right vector is (1.0f, 2.0f, 3.0f), the up vector is (4.0f, 5.0f, -6.0f) and " +
            "the back vector is -7.0f, 8.1f, 9.9f") {
        REQUIRE(B.getRight() == Vector3(1.0f, 2.0f, 3.0f));
        REQUIRE(B.getUp() == Vector3(4.0f, 5.0f, -6.0f));
        REQUIRE(B.getBack() == Vector3(-7.0f, 8.1f, 9.9f));
      }
    }

    WHEN("I pass three Vector3's containing (1.0f, 2.0f, 3.0f), (4.0f, 5.0f, -6.0f), " +
          "(-7.0f, 8.1f, 9.9f) into the constructor with 9 parameters") {
      Vector3 right(1.0f, 2.0f, 3.0f);
      Vector3 up(4.0f, 5.0f, -6.0f);
      Vector3 back(-7.0f, 8.1, 9.9f);
      Matrix3 M(right, up, back);
      THEN("The right vector is (1.0f, 2.0f, 3.0f), the up vector is (4.0f, 5.0f, -6.0f) and " +
            "the back vector is -7.0f, 8.1f, 9.9f") {
        REQUIRE(M.getRight() == right);
        REQUIRE(M.getUp() == up);
        REQUIRE(M.getBack() == back);
      }
    }

    WHEN("I pass a right Vector3 (2.0f, 0.0f, 0.0f) and up Vector3 (0.0f, 3.0f, 0.0f) into " +
          "and no boolean into the constructor that takes two vectors and an optional " +
          "boolean for orthonormal") {
      Vector3 right(2.0f, 0.0f, 0.0f);
      Vector3 up(0.0f, 3.0f, 0.0f);
      Matrix3 M(right, up);
      // TODO change this description lol
      THEN("The right and up vectors are unchanged while the back vector is their cross product") {
        REQUIRE(M.getRight() == right);
        REQUIRE(M.getUp() == up);
        REQUIRE(M.getBack() == right.cross(up));
      }
    }

    WHEN("I pass a right Vector3 (2.0f, 0.0f, 0.0f) and up Vector3 (0.0f, 3.0f, 0.0f) into " +
          "and true into the constructor that takes two vectors and an optional " +
          "boolean for orthonormal") {
      Vector3 right(2.0f, 0.0f, 0.0f);
      Vector3 up(0.0f, 3.0f, 0.0f);
      Matrix3 M(right, up, true);
      right.normalize();
      up.normalize();
      // TODO change this description lol
      THEN("The right and up vectors are normalized while the back vector is their cross product") {
        REQUIRE(M.getRight() == right);
        REQUIRE(M.getUp() == up);
        REQUIRE(M.getBack() == right.cross(up));
      }
    }
  }
}

SCENARIO("Set to Identity", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (1.0f, 1.0f, 1.0f), up vector (2.0f, 2.0f, 2.0f), and " +
  "back vector (3.0f, 3.0f, 3.0f)") {
    Matrix3 A;
    WHEN("I call setToIdentity() on the given matrix") {
      A.setToIdentity();
      THEN("The given matrix becomes the identity matrix") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }  
  }
}

SCENARIO("Set to Zero", "[Matrix3][A05]") {
  GIVEN("A matrix with right vector (1.0f, 1.0f, 1.0f), up vector (2.0f, 2.0f, 2.0f), and " +
  "back vector (3.0f, 3.0f, 3.0f)") {
    Matrix3 A(1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f);
    WHEN("I call setToZero() on the given matrix") {
      A.setToZero();
      THEN("Every element in the given matrix becomes 0") {
        REQUIRE(A.getRight() == Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 0.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 0.0f));
      }
    }  
  }
}

SCENARIO("Data pointer", "[Matrix3][A05]") {
  GIVEN("A matrix with right, up, and back vectors (2.0f, 1.32f, -0.5f), (1034.0f, 0.974f, -7.0f), "+
  " and (-25.6f, 0.111f, 4.2f) respectively") {
    Matrix3 A(2.0f, 1.32f, -0.5f, 1034.0f, 0.974f, -7.0f, -25.6f, 0.111f, 4.2f);
    WHEN("I get the data pointer") {
      float* ptr = A.data();
      THEN("The data being pointed to should be 2.0f, the element in the first row and first column.") {
        REQUIRE(2.0f == Approx(*ptr));
      }
    }

    WHEN("I add 2 to the original data pointer.") {
      float* ptr = A.data();
      ptr += 2;
      THEN("The data being pointed to should be -0.5f, the element in the third row and first column.") {
        REQUIRE(-0.5f == Approx(*ptr));
      }
    }

    WHEN("I add 3 to the original data pointer.") {
      float* ptr = A.data();
      ptr += 3;
      THEN("The data being pointed to should be 1034.0f, the element in the first row and second column.") {
        REQUIRE(1034.0f == Approx(*ptr));
      }
    }
  }
}

SCENARIO("Getters and setters", "[Matrix3][A05]") {
  GIVEN("A matrix with right, up, and back vectors (8.0f, 16.0f, 24.0f), (-3.14f, -1.514f, 2.18281f), " +
  " and (1.0f, 2.0f, 3.0f) respectively.") {
    Vector3 right(8.0f, 16.0f, 24.0f);
    Vector3 up(-3.14f, -1.514f, 2.18281f);
    Vector3 back(1.0f, 2.0f, 3.0f);
    Matrix3 A(right, up, back);

    WHEN("I call the getters for right, back, and up") {
      Vector3 matRight = A.getRight();
      Vector3 matUp = A.getUp();
      Vector3 matBack = A.getBack();
      THEN("Nothing has changed") {
        REQUIRE(matRight == right);
        REQUIRE(matUp == up);
        REQUIRE(matBack == back);
      }
    }

    WHEN("I set the right vector to be (0.0f, -1.0f, -2.0f)") {
      Vector3 matUp = A.getUp();
      Vector3 matBack = A.getBack();
      Vector3 newRight(0.0f, -1.0f, -2.0f);
      A.setRight(newRight);
      THEN("Only the right vector has changed") {
        REQUIRE(newRight == A.getRight());
        REQUIRE(matUp == A.getUp());
        REQUIRE(matBack == A.getBack());
      }
    }

    WHEN("I set the up vector to be (8.8f, -9.9f, -1.1f)") {
      Vector3 matRight = A.getRight();
      Vector3 matBack = A.getBack();
      Vector3 newUp(8.8f, -9.9f, -1.1f);
      A.setUp(newUp);
      THEN("Only the up vector has changed") {
        REQUIRE(matRight == A.getRight());
        REQUIRE(newUp == A.getUp());
        REQUIRE(matBack == A.getBack());
      }
    }

    WHEN("I set the back vector to be (7.0f, -2.0f, 3.0f)") {
      Vector3 matRight = A.getRight();
      Vector3 matUp = A.getUp();
      Vector3 newBack(7.0f, -2.0f, 3.0f);
      A.setBack(newBack);
      THEN("Only the back vector has changed") {
        REQUIRE(matRight == A.getRight());
        REQUIRE(matUp == A.getUp());
        REQUIRE(newBack == A.getBack());
      }
    }

    WHEN("I set and get the forward vector") {
      Vector3 matRight = A.getRight();
      Vector3 matUp = A.getUp();
      Vector3 matForward(2.0f, 4.0f, -5.0f);
      A.setForward(matForward);
      THEN("The back vector is equal to the negation of the forward vector. Right and up don't change") {
        REQUIRE(A.getForward() == -A.getBack());
        REQUIRE(matRight == A.getRight());
        REQUIRE(matUp == A.getUp());
      }
    }
  }
}

SCENARIO("Invert rotation matrix", "[Matrix3][A05]") {
  GIVEN("A rotation matrix, rotating counterclockwise by 90 degrees around the X-axis.") {
    Matrix3 rot(0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    WHEN("I invert the matrix") {
      Matrix3 rotCopy = rot;
      rot.invertRotation();
      THEN("All non-diagonal values should flip signs") {
        float* oldData = rotCopy.data();
        float* newData = rot.data();
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            if (i != j)
              REQUIRE(*oldData == Approx(-(*newData)));
            ++oldData;
            ++newData;
          }
        }
      }
    }
  }
}

SCENARIO("Invert regular matrix", "[Matrix3][A05]") {
  GIVEN("A matrix with right, up, and back vectors (1.0f, 2.0f, 4.0f), (2.0f, 4.0f, -1.0f), " + 
  "and (2.0f, 3.0f, 6.0f) respectively") {
    Vector3 right(1.0f, 2.0f, 4.0f);
    Vector3 up(2.0f, 4.0f, -1.0f);
    Vector3 back(2.0f, 3.0f, 6.0f);
    Matrix3 A(right, up, back);
    WHEN("I invert the matrix") {
      A.invert();
      // source: symbolab.com
      THEN("The matrix right, up, and back vectors become (-3.0f, 0.0f, 2.0f), (1.555556f, 0.222222f, -1.0f) " +
      "and (0.222222f, -0.111111f, 0.0f) respectively") {
        REQUIRE(A.getRight() == Vector3(-3.0f, 0.0f, 2.0f));
        REQUIRE(A.getUp() == Vector3(1.555556f, 0.222222f, -1.0f));
        REQUIRE(A.getBack() == Vector3(0.222222f, -0.111111f, 0.0f));
      }
    }
  }
}

SCENARIO("Matrix Determinant", "[Matrix3][A05]") {
  GIVEN("A matrix with right, up, and back vectors (0.0f, 1.0f, 2.0f), (8.0f, -3.0f, -2.0f), " + 
  " and (9.0f, 11.0f, -76.0f)") {
    Matrix3 A(0.0f, 1.0f, 2.0f, 8.0f, -3.0f, -2.0f, 9.0f, 11.0f, -76.0f);
    WHEN("I find the determinant") {
      float det = A.determinant();
      // source: symbolab.com
      THEN("The determinant is 820.0f") {
        REQUIRE(det == Approx(820.0f));
      }
    }
  }
}

SCENARIO("Orthonormalize", "[Matrix3][A05]") {
  GIVEN("A matrix with values (1, 2, 3, 4, 5, 6, 7, 8, 9)") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I orthonormalize the matrix") {
      Matrix3 ACopy = A;
      A.orthonormalize();
      THEN("All columns have a length of 1") {
        REQUIRE(A.getRight().length() == Approx(1.0f));
        REQUIRE(A.getUp().length() == Approx(1.0f));
        REQUIRE(A.getBack().length() == Approx(1.0f));
      }
      THEN("All vectors are perpendicular to each other (dot product is 0)") {
        REQUIRE(A.getRight().dot(A.getBack()) == Approx(0.0f));
        REQUIRE(A.getRight().dot(A.getUp()) == Approx(0.0f));
        REQUIRE(A.getUp().dot(A.getBack()) == Approx(0.0f));
      }
      THEN("Back vector points in the same direction that it did before") {
        REQUIRE(A.getBack().dot(ACopy.getBack()) == 
          Approx(A.getBack().length() * ACopy.getBack().length()));
      }
    }
  }
}

SCENARIO("Set to scale", "[Matrix3][A05]") {
  GIVEN("A matrix with values (1, 2, 3, 4, 5, 6, 7, 8, 9)") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I set the matrix to 2 * identity matrix") {
      A.setToScale(2.0f);
      THEN("All vectors are multiplied by scalar 2") {
        REQUIRE(A.getRight() == Vector3(2.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 2.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 2.0f));
      }
    }

    WHEN("I scale x, y, and z by 2, 0.5, and 3 respectively") {
      A.setToScale(2.0f, 0.5f, 3.0f);
      THEN("The matrix becomes (2, 0, 0, 0, 0.5, 0, 0, 0, 3)") {
        REQUIRE(A.getRight() == Vector3(2.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 0.5f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 3.0f));
      }
    }
  }
}


SCENARIO("Set to Shear", "[Matrix3][A05]") {
  GIVEN("A matrix (1, 1, 2, 3, 3, 4, 5, 6, 7)") {
    Matrix3 A(1.0f, 1.0f, 2.0f, 3.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f);
    // source for all answers are symbolab.com
    WHEN("I shear X by YShear=2 and ZShear=2") {
      A.setToShearXByYz(2, 2);
      THEN("A becomes (1, 0, 0, 2, 1, 0, 2, 0, 1)") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(2.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(2.0f, 0.0f, 1.0f));
      }
    }
    WHEN("I shear Y by X and Z") {
      A.setToShearYByXz(2, 2);
      THEN("A becomes (1, 2, 0, 0, 1, 0, 0, 2, 1)") {
        REQUIRE(A.getRight() == Vector3(1.0f, 2.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 2.0f, 1.0f));
      }
    }
    WHEN("I shear Z by X and Y") {
      A.setToShearZByXy(2, 2);
      THEN("A becomes (1, 0, 2, 0, 1, 2, 0, 0, 1)") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 2.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 2.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Set to rotation", "[Matrix3][A05]") {
  GIVEN("A matrix (-9, 5, 6.2, 1, 7, 3, 8, 2, -10.1") {
    Matrix3 A(-9.0f, 5.0f, 6.2f, 1.0f, 7.0f, 3.0f, 8.0f, 2.0f, -10.1f);
    WHEN("I rotate around the X-axis by 90 degrees") {
      A.setToRotationX(90);
      THEN("The matrix becomes rotation matrix (1, 0, 0, 0, 0, 1, 0, -1, 0)") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 0.0f, 1.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, -1.0f, 0.0f));
      }
    }
    WHEN("I rotate around the Y-axis by 90 degrees") {
      A.setToRotationY(90);
      THEN("The matrix becomes rotation matrix (0, 0, -1, 0, 1, 0, 1, 0, 0)") {
        REQUIRE(A.getRight() == Vector3(0.0f, 0.0f, -1.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(1.0f, 0.0f, 0.0f));
      }
    }
    WHEN("I rotate around the Z-axis by 90 degrees") {
      A.setToRotationZ(90);
      THEN("The matrix becomes rotation matrix (0, 1, 0, -1, 0, 0, 0, 0, 1)") {
        REQUIRE(A.getRight() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(-1.0f, 0.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }
  }
}

SCENARIO("Set from angle axis", "[Matrix3][A05]") {
  GIVEN("A matrix (-9, 4, 3, 2, -3, -2, 4, 6, 7)") {
    Matrix3 A(-9.0f, 4.0f, 3.0f, 2.0f, -3.0f, -2.0f, 4.0f, 6.0f, 7.0f);
    WHEN("Rotate around the vector (0, 3, 4), by 30 degrees") {
      Vector3 rot(0.0f, 3.0f, 4.0f);
      A.setFromAngleAxis(30, rot);
      // source: symbolab.com using simplified form of Rodrigues Rotation Formula (https://mathworld.wolfram.com/RodriguesRotationFormula.html)
      THEN("The matrix becomes arbitrary rotation matrix using a normalized " + 
        "rotation vector in the same direction") {
        REQUIRE(A.getRight() == Vector3(0.866025f, 0.4f, -0.3f));
        REQUIRE(A.getUp() == Vector3(-0.4f, 0.914256f, 0.064308f));
        REQUIRE(A.getBack() == Vector3(0.3f, 0.064308f, 0.951769f));
      }
    }
  }
}

SCENARIO("Negate", "[Matrix3][A05]") {
  GIVEN("A matrix with values (1, 2, 3, 4, 5, 6, 7, 8, 9)") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("I negate the matrix") {
      A.invertRotation();
      THEN("Matrix is transposed") {
        REQUIRE(A.getRight() == Vector3(1.0f, 4.0f, 7.0f));
        REQUIRE(A.getUp() == Vector3(2.0f, 5.0f, 8.0f));
        REQUIRE(A.getBack() == Vector3(3.0f, 6.0f, 9.0f));
      }
    }
  }
}

SCENARIO("Transform", "[Matrix3][A05]") {
  GIVEN("A matrix initialized to (0, -1, 0, 1, 0, 0, 0, 0, 1)") {
    Matrix3 A(-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    WHEN("I transform the vector (1, 2, 3)") {
      Vector3 t = A.transform(Vector3(1.0f , 2.0f, 3.0f));
      THEN("I get the vector (1, 3, 3)") {
        REQUIRE(t == Vector3(1.0f, 3.0f, 3.0f));
      }
    }
  }
}

SCENARIO("Matrix addition", "[Matrix3][A05]") {
  GIVEN("Two matrices initialized to (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) and " +
  "(2.0, 4.0, 6.0, 8.0, -1.0, 0.0, -1.0, 1.0, -11.0) respectively") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 B(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f);
    WHEN("I use operator + to add first matrix by the second.") {
      Matrix3 C = A + B;
      THEN("The resulting matrix should be (3, 6, 9, 12, 4, 6, 6, 9, -2)") {
        REQUIRE(C == Matrix3(3.0f, 6.0f, 9.0f, 12.0f, 4.0f, 6.0f, 6.0f, 9.0f, -2.0f));
      }
      
      THEN("A and B have not changed") {
        REQUIRE(A == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        REQUIRE(B == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }

    WHEN("I use operator += to add the first matrix by the second") {
      A += B;
      THEN("The resulting matrix should be (3, 6, 9, 12, 4, 6, 6, 9, -2)") {
        REQUIRE(A == Matrix3(3.0f, 6.0f, 9.0f, 12.0f, 4.0f, 6.0f, 6.0f, 9.0f, -2.0f));
      }
      
      THEN("B has not changed") {
        REQUIRE(B == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }
  }
}

SCENARIO("Matrix subtraction", "[Matrix3][A05]") {
  GIVEN("Two matrices initialized to (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) and " +
  "(2.0, 4.0, 6.0, 8.0, -1.0, 0.0, -1.0, 1.0, -11.0) respectively") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 B(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f);
    WHEN("I use operator - to subtract first matrix by the second.") {
      Matrix3 C = A - B;
      THEN("The resulting matrix should be (-1, -2, -3, -4, 6, 6, 8, 7, 20)") {
        REQUIRE(C == Matrix3(-1.0f, -2.0f, -3.0f, -4.0f, 6.0f, 6.0f, 8.0f, 7.0f, 20.0f));
      }
      
      THEN("A and B have not changed") {
        REQUIRE(A == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        REQUIRE(B == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }

    WHEN("I use operator -= to subtract the first matrix by the second") {
      A -= B;
      THEN("The resulting matrix should be (-1, -2, -3, -4, 6, 6, 8, 7, 20)") {
        REQUIRE(A == Matrix3(-1.0f, -2.0f, -3.0f, -4.0f, 6.0f, 6.0f, 8.0f, 7.0f, 20.0f));
      }
      
      THEN("B has not changed") {
        REQUIRE(B == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }
  }
}

SCENARIO("Matrix-scalar multiplication", "[Matrix3][A05]") {
  GIVEN("An identity matrix") {
    Matrix3 A;
    A.setToIdentity();
    WHEN("I multiply the identity matrix by scalar 5 (A * 5)") {
      Matrix3 B = A * 5;
      THEN("The matrix becomes (5, 0, 0, 0, 5, 0, 0, 0, 5)") {
        REQUIRE(B.getRight() == Vector3(5.0f, 0.0f, 0.0f));
        REQUIRE(B.getUp() == Vector3(0.0f, 5.0f, 0.0f));
        REQUIRE(B.getBack() == Vector3(0.0f, 0.0f, 5.0f));
      }
      THEN("The given matrix does not change") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("I multiply the identity matrix by scalar 5 (5 * A)") {
      Matrix3 B = 5 * A;
      THEN("The result is (5, 0, 0, 0, 5, 0, 0, 0, 5)") {
        REQUIRE(B.getRight() == Vector3(5.0f, 0.0f, 0.0f));
        REQUIRE(B.getUp() == Vector3(0.0f, 5.0f, 0.0f));
        REQUIRE(B.getBack() == Vector3(0.0f, 0.0f, 5.0f));
      }
      THEN("The given matrix does not change") {
        REQUIRE(A.getRight() == Vector3(1.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 1.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 1.0f));
      }
    }

    WHEN("I multiply the identity matrix by scalar 5 (A *= 5)") {
      A *= 5;
      THEN("The matrix becomes (5, 0, 0, 0, 5, 0, 0, 0, 5)") {
        REQUIRE(A.getRight() == Vector3(5.0f, 0.0f, 0.0f));
        REQUIRE(A.getUp() == Vector3(0.0f, 5.0f, 0.0f));
        REQUIRE(A.getBack() == Vector3(0.0f, 0.0f, 5.0f));
      }
    }
  }
}

SCENARIO("Matrix-matrix multiplication", "[Matrix3][A05]") {
  GIVEN("Two matrices initialized to (1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0) and " +
  "(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f) respectively") {
    Matrix3 A(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    Matrix3 B(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f);
    WHEN("I use operator * to multiply first matrix by the second.") {
      Matrix3 C = A * B;
      THEN("The resulting matrix should be (54, 72, 84, 4, 11, 18, -63, -85, -96)") {
        REQUIRE(C == Matrix3(60.0f, 72.0f, 84.0f, 4.0f, 11.0f, 18.0f, -74.0f, -85.0f, -96.0f));
      }
      
      THEN("A and B have not changed") {
        REQUIRE(A == Matrix3(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f));
        REQUIRE(B == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }

    WHEN("I use operator *= to multiply the first matrix by the second") {
      A *= B;
      THEN("The resulting matrix should be (54, 72, 84, 4, 11, 18, -63, -85, -96)") {
        REQUIRE(A == Matrix3(60.0f, 72.0f, 84.0f, 4.0f, 11.0f, 18.0f, -74.0f, -85.0f, -96.0f));
      }
      
      THEN("B has not changed") {
        REQUIRE(B == Matrix3(2.0f, 4.0f, 6.0f, 8.0f, -1.0f, 0.0f, -1.0f, 1.0f, -11.0f));
      }
    }
  }
}

SCENARIO("Matrix-vector multiplication", "[Matrix3][A05]") {
  GIVEN("A matrix initialized to (0, -1, 0, 1, 0, 0, 0, 0, 1)") {
    Matrix3 A(-1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    WHEN("I multiply the matrix by the vector (1, 2, 3)") {
      Vector3 t = A.transform(Vector3(1.0f , 2.0f, 3.0f));
      THEN("I get the vector (1, 3, 3)") {
        REQUIRE(t == Vector3(1.0f, 3.0f, 3.0f));
      }
    }
  }
}

SCENARIO ("Matrix3 stream insertion.", "[Matrix3][A05]") {
  GIVEN ("A matrix initialized with (4.3, 31415.0, -1.2, 4.5, 2.2, 1.0, -12345.0, 2.12, 3.0).") {
    Matrix3 A(4.3f, 31415.0f, -1.2f, 4.5f, 2.2f, 1.0f, -12345.0f, 2.12f, 23.0f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << A;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
        std::string line1 = "      4.30      4.50 -12345.00\n";
        std::string line2 = "  31415.00      2.20      2.12\n";
        std::string line3 = "     -1.20      1.00     23.00\n";
        std::string outTest = line1 + line2 + line3;
	      REQUIRE (outTest == out.str());
      }
      THEN ("The original stream should have been returned.") {
	      REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Matrix3 equality.", "[Matrix3][A05]") {
  GIVEN ("A matrix initialized with (1.2, 3.4, 0.1, 2.2, 5.5, 7.312, -0.5, -2.1, 3.4).") {
    Matrix3 A(1.2f, 3.4f, 0.1f, 2.2f, 5.5f, 7.312f, -0.5f, -2.1f, 3.4f);
    WHEN ("I compare with a matrix initialized with (1.2, 3.4, 0.1000000001, 2.2, 5.5, 7.312, -0.5, -2.1, 3.4).") {
      Matrix3 B(1.2f, 3.4f, 0.1000000001f, 2.2f, 5.5f, 7.312f, -0.5f, -2.1f, 3.4f);
      bool equal = A == B;
      THEN ("They should be equal.") {
	      REQUIRE (true == equal);
      }
    }

    WHEN ("I compare with a vector initialized with (1.2, 3.4, 0.101, 2.2f, 5.5f, 7.312f, -0.5f, -2.1f, 3.4f).") {
      Matrix3 C(1.2f, 3.4f, 0.101f, 2.2f, 5.5f, 7.312f, -0.5f, -2.1f, 3.4f);
      bool equal = A == C;
      THEN ("They should not be equal.") {
	      REQUIRE (false == equal);
      }
    }
  }
}