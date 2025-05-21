#ifndef LILTANUKI_SRC_PIECE_H_
#define LILTANUKI_SRC_PIECE_H_

#include <cassert>
#include <string>
#include <vector>

// 手番（先手・後手）
enum class Color {
  Black,
  White,
  NumColors
};

inline Color Opponent(Color c) {
  switch (c) {
    case Color::Black: return Color::White;
    case Color::White: return Color::Black;
    default:
      assert(false && "Invalid color passed to Opponent()");
      return Color::Black; // fallback（unreachable）
  }
}

// 駒の種類
enum class Piece {
  NoPiece,                // 駒なし
  BlackPawn, BlackLance, BlackKnight, BlackSilver, BlackGold, BlackBishop, BlackRook, BlackKing,
  BlackPromotedPawn, BlackPromotedLance, BlackPromotedKnight, BlackPromotedSilver, BlackHorse, BlackDragon,
  WhitePawn, WhiteLance, WhiteKnight, WhiteSilver, WhiteGold, WhiteBishop, WhiteRook, WhiteKing,
  WhitePromotedPawn, WhitePromotedLance, WhitePromotedKnight, WhitePromotedSilver, WhiteHorse, WhiteDragon,
  NumPieces               // 駒の種類数
};

class PieceHelper {
  public:
    static const std::vector<std::string> piece_to_string;
    // 駒を人間が読める文字列に変換
    static std::string ToHumanReadableString(Piece piece);
    static Color ToColor(Piece piece);
    static Piece AsOpponentHandPiece(Piece piece);
    static char ToUsiChar(Piece piece);
    static bool CanPromote(Piece piece);
    static bool CanPutWithoutPromotion(Piece piece_from, int rank_to);
    static Piece AsUnPromoted(Piece piece);
  
  private:
    static const std::array<Piece, static_cast<int>(Piece::NumPieces)> piece_to_opponent_hand_pieces;
};

#endif // LILTANUKI_SRC_PIECE_H_
