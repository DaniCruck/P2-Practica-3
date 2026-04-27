#include <cxxtest/TestSuite.h>

#include <vector>

#include "Piece.h"

class TestSuiteACPiece : public CxxTest::TestSuite {
private:
  // comprueba si una pieza contiene una coordenada dada
  bool containsCoordinate(const std::vector<Coordinate> &positions, int row, int column) {
    
    bool found = false;
    
    // recorre todas las posiciones de la pieza
    for (size_t i = 0; i < positions.size(); i++) {
      if (positions[i].getRow() == row && positions[i].getColumn() == column) {
        found = true;
      }
    }

    return found;
  }

public:
  void testPiece() {
    // comprueba estado inicial de una pieza O
    Shape::setSeqPieceTypes("O");
    Piece p;

    TS_ASSERT_EQUALS(p.getType(), PT_O);
    TS_ASSERT_EQUALS(p.getOrientation(), D0);
    TS_ASSERT_EQUALS(p.isFixed(), false);

    // comprueba posiciones finales para una pieza O en una coordenada dada
    Coordinate base(5, 3);
    std::vector<Coordinate> positions = p.getFinalPositions(base);

    TS_ASSERT_EQUALS(positions.size(), 4U);
    TS_ASSERT(containsCoordinate(positions, 5, 4));
    TS_ASSERT(containsCoordinate(positions, 5, 5));
    TS_ASSERT(containsCoordinate(positions, 6, 4));
    TS_ASSERT(containsCoordinate(positions, 6, 5));
  }
};
