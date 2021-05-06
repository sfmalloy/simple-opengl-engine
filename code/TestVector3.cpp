/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Vector3 class.
/// \author Chad Hogg, Sean Malloy
/// \version A04

#include <sstream>

#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


// Note: I included just a few representative / unusually tricky test cases here.  You should write the others, for every function declared in Vector3.hpp.

SCENARIO ("Vector3 constructors.", "[Vector3][A04]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Vector3 constructor.") {
      Vector3 v;
      THEN ("All components should be 0.0f.") {
	      REQUIRE (0.0f == Approx (v.m_x));
	      REQUIRE (0.0f == Approx (v.m_y));
	      REQUIRE (0.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 5.3f to the constructor with one parameter.") {
      Vector3 v (5.3f);
      THEN ("All components should be 5.3f.") {
        REQUIRE (5.3f == Approx (v.m_x));
        REQUIRE (5.3f == Approx (v.m_y));
        REQUIRE (5.3f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 3.4f, 9.1f, and -2.4f to the constructor with three parameters.") {
      Vector3 v (3.4f, 9.1f, -2.4f);
      THEN ("The components should be 3.4f, 9.1f, and -2.4f respectively.") {
        REQUIRE (3.4f == Approx (v.m_x));
        REQUIRE (9.1f == Approx (v.m_y));
        REQUIRE (-2.4f == Approx (v.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 set to all same value.", "[Vector3][A04]") {
  GIVEN ("A default vector") {
    Vector3 v;
    WHEN ("I pass 3.0f into single-value set function") {
      v.set(3.0f);
      THEN ("All components should be 3.0f") {
        REQUIRE (3.0f == Approx (v.m_x));
        REQUIRE (3.0f == Approx (v.m_y));
        REQUIRE (3.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass -2.1f into the single-value set function in same vector") {
      v.set(-2.1f);
      THEN ("All components should be -2.1f") {
        REQUIRE (-2.1f == Approx (v.m_x));
        REQUIRE (-2.1f == Approx (v.m_y));
        REQUIRE (-2.1f == Approx (v.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 set to different values.", "[Vector3][A04]") {
  GIVEN ("A default vector") {
    Vector3 v;
    WHEN ("I pass (1.0f, 2.0f, 3.0f) into multi-value set function") {
      v.set(1.0f, 2.0f, 3.0f);
      THEN ("Components should be 1.0f, 2.0f, and 3.0f, respectively") {
        REQUIRE (1.0f == Approx (v.m_x));
        REQUIRE (2.0f == Approx (v.m_y));
        REQUIRE (3.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass (-2.1f, 0.0f, 3.142f) into the multi-value set function in same vector") {
      v.set(-2.1f, 0.0f, 3.142f);
      THEN ("Components should be -2.1f, 0.0f, and 3.142f respectively") {
        REQUIRE (-2.1f == Approx (v.m_x));
        REQUIRE (0.0f == Approx (v.m_y));
        REQUIRE (3.142f == Approx (v.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 negation.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.0f, -2.3f, 20.1f).") {
    Vector3 v (1.0f, -2.3f, 20.1f);
    WHEN ("I negate the given vector using negate function") {
      Vector3 vCopy = v;
      vCopy.negate();
      THEN ("All values should have flipped signs.") {
        REQUIRE (-1.0f == Approx (vCopy.m_x));
        REQUIRE (2.3f == Approx (vCopy.m_y));
        REQUIRE (-20.1f == Approx (vCopy.m_z));
      }
    }

    WHEN("I negate the given vector again using operator-") {
      v = -v;
      THEN ("All the values should have flipped signs again.") {
        REQUIRE (-1.0f == Approx (v.m_x));
        REQUIRE (2.3f == Approx (v.m_y));
        REQUIRE (-20.1f == Approx (v.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 dot product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the dot product of the vectors.") {
      float dot = v1.dot (v2);
      THEN ("The dot product should be the sum of the element-wise products.") {
	      // Source: typed "dot product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	      REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}

SCENARIO ("Vector3 angle between." "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the angle (in radians) between the vectors.") {
      float angle = v1.angleBetween (v2);
      THEN ("The angle should be the inverse cosine of the dot product "
        + "divided by the product of the vector lengths") {
	      // Source: typed "angle between (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	      REQUIRE (0.861372f == Approx (angle));
      }
    }
  }
}

SCENARIO ("Vector3 cross product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (3.3f, 1.2f, 3.3f);
    Vector3 v2 (-0.1f, -0.2f, 11.1f);
    WHEN ("I find the cross product of the vectors.") {
      Vector3 cross = v1.cross (v2);
      float angle1 = v1.angleBetween(cross);
      float angle2 = v2.angleBetween(cross);
      THEN ("The cross product should result in a vector orthogonal to the other two vectors.") {
	      // Source: typed "cross product of (3.3, 1.2, 3.3) and (-0.1, -0.2, 11.1)" into Wolfram Alpha
	      REQUIRE (13.98f == Approx (cross.m_x));
	      REQUIRE (-36.96f == Approx (cross.m_y));
	      REQUIRE (-0.54f == Approx (cross.m_z));

        REQUIRE (1.570796f == Approx (angle1));
        REQUIRE (1.570796f == Approx (angle2));
      }
    }
  }
}

SCENARIO ("Vector3 length.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (12.2f, 3.4f, -1.0f).") {
    Vector3 v (12.2f, 3.4f, -1.0f);
    WHEN ("I find the length of the vector") {
      float length = v.length ();
      THEN ("The length should be the square root of the sum of the squares of all 3 unit vector lengths.") {
        // Source: typed "length of vector (12.2, 3.4, -1.0) into Wolfram Alpha"
        REQUIRE (12.7043f == Approx (length));
      }
    }
  }
}

SCENARIO ("Vector3 normalize.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (-2.0f, 3.0f, 1.0f)") {
    Vector3 v (-2.0f, 3.0f, 1.0f);
    WHEN ("I normalize the vector") {
      v.normalize();
      THEN ("The vector points in the same direction, but its length changes to 1.") {
        // Source: typed "normalize vector (-2.0, 3.0, 1.0) into Wolfram Alpha"
        REQUIRE (1.0f == Approx (v.length()));
        REQUIRE (-0.534522f == Approx (v.m_x));
        REQUIRE (0.801784f == Approx (v.m_y));
        REQUIRE (0.267261f == Approx (v.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 addition", "[Vector3][A04]") {
  GIVEN ("Two vectors a and b initialized to (1.0f, 2.0f, 3.0f) and (8.2f, -2.0f, -11.9f) respectively") {
    Vector3 a (1.0f, 2.0f, 3.0f);
    Vector3 b (8.2f, -2.0f, -11.9f);
    WHEN ("I add vector a and b into another vector c") {
      Vector3 c = a + b;
      THEN ("Each individual component is added and vector a changes, while vector b stays the same") {
        REQUIRE (9.2f == Approx (c.m_x));
        REQUIRE (0.0f == Approx (c.m_y));
        REQUIRE (-8.9f == Approx (c.m_z));
        
        REQUIRE (1.0f == Approx (a.m_x));
        REQUIRE (2.0f == Approx (a.m_y));
        REQUIRE (3.0f == Approx (a.m_z));

        REQUIRE (8.2f == Approx (b.m_x));
        REQUIRE (-2.0f == Approx (b.m_y));
        REQUIRE (-11.9f == Approx (b.m_z));
      }
    }

    WHEN ("I add vector b to vector a (operator +=)") {
      a += b;
      THEN ("Each individual component is added and vector a changes, while vector b stays the same") {
        REQUIRE (9.2f == Approx (a.m_x));
        REQUIRE (0.0f == Approx (a.m_y));
        REQUIRE (-8.9f == Approx (a.m_z));

        REQUIRE (8.2f == Approx (b.m_x));
        REQUIRE (-2.0f == Approx (b.m_y));
        REQUIRE (-11.9f == Approx (b.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 subtraction.", "[Vector3][A04]") {
  GIVEN ("Two vectors a and b initialized to (1.0f, 2.0f, 3.0f) and (8.2f, -2.0f, -11.9f) respectively") {
    Vector3 a (1.0f, 2.0f, 3.0f);
    Vector3 b (8.2f, -2.0f, -11.9f);
    WHEN ("I add vector a and b to a new vector c") {
      Vector3 c = a - b;
      THEN ("a and b don't change, each component of c is the sum of the components of a and b") {
        REQUIRE (-7.2f == Approx (c.m_x));
        REQUIRE (4.0f == Approx (c.m_y));
        REQUIRE (14.9f == Approx (c.m_z));

        REQUIRE (1.0f == Approx (a.m_x));
        REQUIRE (2.0f == Approx (a.m_y));
        REQUIRE (3.0f == Approx (a.m_z));

        REQUIRE (8.2f == Approx (b.m_x));
        REQUIRE (-2.0f == Approx (b.m_y));
        REQUIRE (-11.9f == Approx (b.m_z));
      }
    }

    WHEN ("I add vector b to vector a (operator -=)") {
      a -= b;
      THEN ("Each individual component is subtracted and vector a changes, while vector b stays the same") {
        REQUIRE (-7.2f == Approx (a.m_x));
        REQUIRE (4.0f == Approx (a.m_y));
        REQUIRE (14.9f == Approx (a.m_z));

        REQUIRE (8.2f == Approx (b.m_x));
        REQUIRE (-2.0f == Approx (b.m_y));
        REQUIRE (-11.9f == Approx (b.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 scalar multiplication", "[Vector3][A04]") {
  GIVEN ("A vector v initialized to (1.0f, 3.0f, -2.2f) and a scalar k initialized to 7.0f") {
    Vector3 v (1.0f, 3.0f, -2.2f);
    float k = 7.0f;
    WHEN ("I multiply v by scalar k. (v * k)") {
      Vector3 u = v * k;
      THEN ("Each component of v is multiplied by k, and k stays the same") {
        REQUIRE (7.0f == Approx (u.m_x));
        REQUIRE (21.0f == Approx (u.m_y));
        REQUIRE (-15.4 == Approx (u.m_z));

        REQUIRE (7.0f == Approx (k));
      }
    }

    WHEN ("I multiply v by scalar k. (k * v)") {
      Vector3 u = k * v;
      THEN ("Each component of v is multiplied by k, and k stays the same") {
        REQUIRE (7.0f == Approx (u.m_x));
        REQUIRE (21.0f == Approx (u.m_y));
        REQUIRE (-15.4 == Approx (u.m_z));

        REQUIRE (7.0f == Approx (k));
      }
    }

    WHEN ("I multiply v by scalar k (v *= k)") {
      v *= k;
      THEN ("Each component of v is multiplied by k, and k stays the same") {
        REQUIRE (7.0f == Approx (v.m_x));
        REQUIRE (21.0f == Approx (v.m_y));
        REQUIRE (-15.4 == Approx (v.m_z));

        REQUIRE (7.0f == Approx (k));
      }
    }
  }
}

SCENARIO ("Vector3 scalar division", "[Vector3][A04]") {
  GIVEN ("A vector v initialized to (1.0f, 3.0f, -2.2f) and a scalar k initialized to 2.0f") {
    Vector3 v (1.0f, 3.0f, -2.2f);
    float k = 2.0f;
    WHEN ("I divide v by scalar k") {
      v /= k;
      THEN ("Each component of v is divided by k, and k stays the same") {
        REQUIRE (0.5f == Approx (v.m_x));
        REQUIRE (1.5f == Approx (v.m_y));
        REQUIRE (-1.1f == Approx (v.m_z));

        REQUIRE (2.0f == Approx (k));
      }
    }
  }
}

SCENARIO ("Vector3 stream insertion.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (4.3, 102345, and -1.2).") {
    Vector3 v(4.3f, 102345.0f, -1.2f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << v;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	      REQUIRE ("      4.30 102345.00     -1.20" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	      REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Vector3 equality.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (1.2, 3.4, and 0.1).") {
    Vector3 v1(1.2f, 3.4f, 0.1f);
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.1000000001).") {
      Vector3 v2(1.2f, 3.4f, 0.1000000001f);
      bool equal = v1 == v2;
      THEN ("They should be equal.") {
	      REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.101).") {
      Vector3 v3(1.2f, 3.4f, 0.101f);
      bool equal = v1 == v3;
      THEN ("They should not be equal.") {
	      REQUIRE (false == equal);
      }
    }
  }
}
