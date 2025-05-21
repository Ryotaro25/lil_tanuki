#ifndef LILTANUKI_SRC_POSITION_H_
#define LILTANUKI_SRC_POSITION_H_

#include <ostream>
#include <string>
#include <vector>
#include "piece.h"
#include "move.h"

class Position {
  public:
    static constexpr int BOARD_SIZE = 9;
    Position();

    // 手番
    Color side_to_move;
    // 盤面の状態
    Piece board[BOARD_SIZE][BOARD_SIZE];
    // 持ち駒（各駒の枚数）
    int hand_pieces[static_cast<int>(Piece::NumPieces)];
    // 手数
    int play;
    Move last_move;

    std::string ToString() const;
    void Set(const std::string& sfen);
    static const std::string StartposSfen;
    void DoMove(const Move& move);
    void UndoMove(const Move& move);
    std::pair<int, int> FindKing(Color color);
    bool IsSquareAttacked(int file, int rank, Color by_color);
    static bool IsKingInCheck(Color color, Position& position);

  private:
    void PutPiece(int file, int rank, Piece piece);
    void RemovePiece(int file, int rank);
    void PutHandPiece(Piece piece);
    void RemoveHandPiece(Piece piece);
};

std::ostream& operator<<(std::ostream& os, const Position& position);

#endif // LILTANUKI_SRC_POSITION_H_
