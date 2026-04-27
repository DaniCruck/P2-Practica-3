#include <cxxtest/TestSuite.h>

#include "Game.h"

class TestSuiteACGame : public CxxTest::TestSuite {
public:
  void testGame() {

    // comprueba constructor y estado inicial
    Shape::setSeqPieceTypes("O");
    Game game(12, 10);
    TS_ASSERT_EQUALS(game.isGameOver(), false);

    // comprueba que se crea una nueva pieza en la posición correcta
    bool ok = game.nextPiece();

    TS_ASSERT(ok);
    TS_ASSERT_DIFFERS(game.getCurrentPiece(), nullptr);
    TS_ASSERT_EQUALS(game.isPieceFixed(), false);
    TS_ASSERT_EQUALS(game.getCurrentPosition().getRow(), 0);
    TS_ASSERT_EQUALS(game.getCurrentPosition().getColumn(), 3);

    // comprueba que las piezas se fijan al tocar el suelo
    int maxSteps = 20;
    while (!game.isPieceFixed() && maxSteps > 0) {
      game.moveDown();
      maxSteps--;
    }

    TS_ASSERT(game.isPieceFixed());
  }
};
