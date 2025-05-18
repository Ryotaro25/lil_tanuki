#ifndef LILTANUKI_SRC_EVALUATOR_H_
#define LILTANUKI_SRC_EVALUATOR_H_

#include "piece.h"
#include "position.h"

#include <array>

namespace Evaluator {
  constexpr std::array<int, static_cast<int>(Piece::NumPieces)> PIECE_VALUES = {
    0,     // NoPiece
    90,    // 歩
    315,   // 香
    405,   // 桂
    495,   // 銀
    540,   // 金
    855,   // 角
    990,   // 飛
    15000, // 王
    540,   // と
    540,   // 成香
    540,   // 成桂
    540,   // 成銀
    945,   // 馬
    1395,  // 龍
    -90,   // 後手 歩
    -315,  // 後手 香
    -405,  // 後手 桂
    -495,  // 後手 銀
    -540,  // 後手 金
    -855,  // 後手 角
    -990,  // 後手 飛
    -15000,// 後手 王
    -540,  // 後手 と
    -540,  // 後手 成香
    -540,  // 後手 成桂
    -540,  // 後手 成銀
    -945,  // 後手 馬
    -1395  // 後手 龍
  };

  inline int  Evaluate(const Position& position) {
    int value = 0;
    // 盤面の評価
    for (int rank = 0; rank < Position::BOARD_SIZE; rank++) {
      for (int file = 0; file < Position::BOARD_SIZE; file++) {
        Piece piece = position.board[rank][file];
        value += PIECE_VALUES[static_cast<int>(piece)];
      }
    }

    // 持ち駒の評価
    for (int i = 0; i < static_cast<int>(Piece::NumPieces); i++) {
      value += (PIECE_VALUES[i] * position.hand_pieces[i]);
    }

    // 手番に応じて符号反転
    if (position.side_to_move == Color::White) {
      value = -value;
    }
    return value;
  }
};
#endif 