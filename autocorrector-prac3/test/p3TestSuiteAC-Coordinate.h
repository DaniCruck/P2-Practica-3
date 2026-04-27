#include <cxxtest/TestSuite.h>

#include "Coordinate.h"

class TestSuiteACCoordinate : public CxxTest::TestSuite {
public:
  void testCoordinate() {

    // comprueba el constructor por defecto
    Coordinate c;
    TS_ASSERT_EQUALS(c.getRow(), 0);
    TS_ASSERT_EQUALS(c.getColumn(), 0);
  
    // comprueba el constructor parametrizado (positivo)
    Coordinate c2(3, 7);
    TS_ASSERT_EQUALS(c2.getRow(), 3);
    TS_ASSERT_EQUALS(c2.getColumn(), 7);

    // comprueba el constructor parametrizado (negativo)
    Coordinate c3(-5, -1);
    TS_ASSERT_EQUALS(c3.getRow(), -5);
    TS_ASSERT_EQUALS(c3.getColumn(), -1);

    // comprueba la suma de coordenadas
    Coordinate a(5, 2);
    Coordinate b(0, -1);
    Coordinate result = a.add(b);

    TS_ASSERT_EQUALS(result.getRow(), 5);
    TS_ASSERT_EQUALS(result.getColumn(), 1);
  
  }
};
