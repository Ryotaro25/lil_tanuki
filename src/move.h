#ifndef LILTANUKI_SRC_UTIL_MOVE_H_
#define LILTANUKI_SRC_UTIL_MOVE_H_

#include "piece.h"
#include "position.h"
#include <functional>
#include <ostream>

class Move {
public:
  // file: 将棋盤では、横方向の列、rank: 将棋盤では、縦方向の行
  int file_from;
  int rank_from;
  Piece piece_from;
  int file_to;
  int rank_to;
  Piece piece_to;
  bool drop;
  bool promotion;
  Color side_to_move; // どちらの手番か

  Move(int ff = -1, int rf = -1, Piece pf = Piece::NoPiece,
       int ft = -1, int rt = -1, Piece pt = Piece::NoPiece,
       bool d = false, bool prom = false, Color stm = Color::Black)
      :file_from(ff), rank_from(rf), piece_from(pf),
       file_to(ft), rank_to(rt), piece_to(pt),
       drop(d), promotion(prom), side_to_move(stm) {}

  // 投了・入玉宣言勝ち・無効な指し手を表すための定数
  static const Move RESIGN;
  static const Move WIN;
  static const Move NONE;

  // 指し手の文字列変換（デバッグ用）
  std::string ToString() const;
  // USI形式との相互変換
  std::string ToUsiString() const;
  Move FromUsiString(const Position& pos, const std::string& str);

  // 比較関数
  bool operator==(const Move& other) const;

  
};
// クラスの外で宣言する（非メンバ）
// メンバ関数として定義するとoperator<< が三つの引数を取っている、そんな関数は存在できないよとエラーが出る
// これは内部的にクラスへのポインタを引数に渡すため
std::ostream& operator<<(std::ostream& os, const Move& move);

#endif // LILTANUKI_SRC_POSITION_H_
