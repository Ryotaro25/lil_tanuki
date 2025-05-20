#ifndef LILTANUKI_SRC_UTIL_MOVEGENERATOR_H_
#define LILTANUKI_SRC_UTIL_MOVEGENERATOR_H_

#include <vector>
#include "move.h"
#include "position.h"

class MoveGenerator {
public:
  static std::vector<Move> GenerateMoves(const Position& position);
  static std::vector<Move> GenerateLegalMoves(const Position& position);

private:
  static bool IsPawnExist(const Piece board[9][9], int file, Piece pawn);
};

#endif // LILTANUKI_SRC_POSITION_H_
