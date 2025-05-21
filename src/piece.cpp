#include "piece.h"
#include "utils/types.h"
const std::vector<std::string> PieceHelper::piece_to_string = {
  "　　",
  " 歩 ", " 香 ", " 桂 ", " 銀 ", " 金 ", " 角 ", " 飛 ", " 王 ",
  " と ", " 杏 ", " 圭 ", " 全 ", " 馬 ", " 龍 ",
  " 歩↓", " 香↓", " 桂↓", " 銀↓", " 金↓", " 角↓", " 飛↓", " 王↓",
  " と↓", " 杏↓", " 圭↓", " 全↓", " 馬↓", " 龍↓",
  ""  // 最後は"" (null相当)
};

const std::array<Piece, static_cast<int>(Piece::NumPieces)> PieceHelper::piece_to_opponent_hand_pieces = {
  Piece::NoPiece,
  Piece::WhitePawn, Piece::WhiteLance, Piece::WhiteKnight, Piece::WhiteSilver, Piece::WhiteGold, Piece::WhiteBishop, Piece::WhiteRook, Piece::NoPiece,
  Piece::WhitePawn, Piece::WhiteLance, Piece::WhiteKnight, Piece::WhiteSilver, Piece::WhiteBishop, Piece::WhiteRook,
  Piece::BlackPawn, Piece::BlackLance, Piece::BlackKnight, Piece::BlackSilver, Piece::BlackGold, Piece::BlackBishop, Piece::BlackRook, Piece::NoPiece,
  Piece::BlackPawn, Piece::BlackLance, Piece::BlackKnight, Piece::BlackSilver, Piece::BlackBishop, Piece::BlackRook,
  // Piece::NumPieces // 最後の NumPieces 用
};

std::string PieceHelper::ToHumanReadableString(Piece piece) {
  int index = static_cast<int>(piece);
  assert(index >= 0 && index < static_cast<int>(PieceHelper::piece_to_string.size()) && 
         !PieceHelper::piece_to_string[index].empty() && "Invalid Piece");
  return PieceHelper::piece_to_string[index];
}

Color PieceHelper::ToColor(Piece piece) {
  int p = static_cast<int>(piece);
  assert(p >= static_cast<int>(Piece::BlackPawn) && p < static_cast<int>(Piece::NumPieces));
  return p < static_cast<int>(Piece::WhitePawn) ? Color::Black : Color::White;
}

Piece PieceHelper::AsOpponentHandPiece(Piece piece) {
  int index = static_cast<int>(piece);
  assert(index >= 0 && index < static_cast<int>(Piece::NumPieces));
  assert(piece_to_opponent_hand_pieces[index] != Piece::NoPiece);
  return piece_to_opponent_hand_pieces[index];
}

char PieceHelper::ToUsiChar(Piece piece) {
  int index = static_cast<int>(piece);
  assert(index >= 0 && index < static_cast<int>(Piece::NumPieces));
  assert(Types::piece_to_char[index] != '\0');
  return Types::piece_to_char[index];
}

bool PieceHelper::CanPromote(Piece piece) {
  return Types::non_promoted_to_promoted[static_cast<int>(piece)] != Piece::NoPiece;
}

bool PieceHelper::CanPutWithoutPromotion(Piece piece_from, int rank_to) {
  using P = Piece;

  return (piece_from == P::BlackPawn && rank_to >= 2) || 
         (piece_from == P::BlackLance && rank_to >= 2) || 
         (piece_from == P::BlackKnight && rank_to >= 3) ||
         (piece_from == P::WhitePawn && rank_to <= 8) ||
         (piece_from == P::WhiteLance && rank_to <= 8) ||
         (piece_from == P::WhiteKnight && rank_to <= 7) ||
         (piece_from != P::BlackPawn &&
          piece_from != P::BlackLance &&
          piece_from != P::BlackKnight &&
          piece_from != P::WhitePawn &&
          piece_from != P::WhiteLance &&
          piece_from != P::WhiteKnight);
}

Piece PieceHelper::AsUnPromoted(Piece piece) {
    switch (piece) {
      case Piece::BlackPromotedPawn:    return Piece::BlackPawn;
      case Piece::BlackPromotedLance:   return Piece::BlackLance;
      case Piece::BlackPromotedKnight:  return Piece::BlackKnight;
      case Piece::BlackPromotedSilver:  return Piece::BlackSilver;
      case Piece::BlackHorse:      return Piece::BlackBishop;
      case Piece::BlackDragon:     return Piece::BlackRook;

      case Piece::WhitePromotedPawn:    return Piece::WhitePawn;
      case Piece::WhitePromotedLance:   return Piece::WhiteLance;
      case Piece::WhitePromotedKnight:  return Piece::WhiteKnight;
      case Piece::WhitePromotedSilver:  return Piece::WhiteSilver;
      case Piece::WhiteHorse:      return Piece::WhiteBishop;
      case Piece::WhiteDragon:     return Piece::WhiteRook;

      default:
        return piece; // 成駒でなければそのまま返す
    }
  }

