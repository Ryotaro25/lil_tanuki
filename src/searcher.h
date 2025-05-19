#ifndef LILTANUKI_SRC_SEARCHER_H_
#define LILTANUKI_SRC_SEARCHER_H_

#include "evaluator.h"
#include "move.h"
#include "move_generator.h"
#include "position.h"

#include <limits>
#include <vector>

struct BestMove {
  Move move;
  int value;

  BestMove(const Move& m = Move::RESIGN, int v = 0) : move(m), value(v) {}
};

// https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%8B%E3%83%9E%E3%83%83%E3%82%AF%E3%82%B9%E6%B3%95
namespace Searcher {
  BestMove Search(Position& position, int depth, int& nodes) {
    if (depth == 0) {
      return BestMove(Move::NONE, Evaluator::Evaluate(position));
    }

    int best_value = std::numeric_limits<int>::min();
    Move best_move = Move::RESIGN;

    std::vector<Move> moves = MoveGenerator::GenerateMoves(position);
    for (const auto& move : moves) {
      if (move.piece_to == Piece::BlackKing || move.piece_to == Piece::WhiteKing) {
        return BestMove(move, std::numeric_limits<int>::max());
      }

      nodes++;
      position.DoMove(move);
      BestMove child_best_move = Search(position, depth - 1, nodes);
      position.UndoMove(move);

      int score = -child_best_move.value;
      if (score > best_value) {
        best_value = score;
        best_move = move;
      }
    }
    return BestMove(best_move, best_value);
  }
}

#endif // LILTANUKI_SRC_SEARCH_SEARCHER_H_
