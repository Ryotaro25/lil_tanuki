#include "types.h"
#include <iostream>
std::vector<Piece> Types::char_to_piece(128, Piece::NoPiece);
std::vector<Piece> Types::non_promoted_to_promoted(static_cast<int>(Piece::NumPieces), Piece::NoPiece);
std::vector<char> Types::piece_to_char(static_cast<int>(Piece::NumPieces), '\0');

void Types::Initialize() {
  non_promoted_to_promoted[static_cast<int>(Piece::BlackPawn)] = Piece::BlackPromotedPawn;
  non_promoted_to_promoted[static_cast<int>(Piece::BlackLance)] = Piece::BlackPromotedLance;
  non_promoted_to_promoted[static_cast<int>(Piece::BlackKnight)] = Piece::BlackPromotedKnight;
  non_promoted_to_promoted[static_cast<int>(Piece::BlackSilver)] = Piece::BlackPromotedSilver;
  non_promoted_to_promoted[static_cast<int>(Piece::BlackBishop)] = Piece::BlackHorse;
  non_promoted_to_promoted[static_cast<int>(Piece::BlackRook)] = Piece::BlackDragon;
  non_promoted_to_promoted[static_cast<int>(Piece::WhitePawn)] = Piece::WhitePromotedPawn;
  non_promoted_to_promoted[static_cast<int>(Piece::WhiteLance)] = Piece::WhitePromotedLance;
  non_promoted_to_promoted[static_cast<int>(Piece::WhiteKnight)] = Piece::WhitePromotedKnight;
  non_promoted_to_promoted[static_cast<int>(Piece::WhiteSilver)] = Piece::WhitePromotedSilver;
  non_promoted_to_promoted[static_cast<int>(Piece::WhiteBishop)] = Piece::WhiteHorse;
  non_promoted_to_promoted[static_cast<int>(Piece::WhiteRook)] = Piece::WhiteDragon;

  char_to_piece['K'] = Piece::BlackKing;
  char_to_piece['k'] = Piece::WhiteKing;
  char_to_piece['R'] = Piece::BlackRook;
  char_to_piece['r'] = Piece::WhiteRook;
  char_to_piece['B'] = Piece::BlackBishop;
  char_to_piece['b'] = Piece::WhiteBishop;
  char_to_piece['G'] = Piece::BlackGold;
  char_to_piece['g'] = Piece::WhiteGold;
  char_to_piece['S'] = Piece::BlackSilver;
  char_to_piece['s'] = Piece::WhiteSilver;
  char_to_piece['N'] = Piece::BlackKnight;
  char_to_piece['n'] = Piece::WhiteKnight;
  char_to_piece['L'] = Piece::BlackLance;
  char_to_piece['l'] = Piece::WhiteLance;
  char_to_piece['P'] = Piece::BlackPawn;
  char_to_piece['p'] = Piece::WhitePawn;

  piece_to_char[static_cast<int>(Piece::BlackKing)] = 'K';
  piece_to_char[static_cast<int>(Piece::WhiteKing)] = 'k';
  piece_to_char[static_cast<int>(Piece::BlackRook)] = 'R';
  piece_to_char[static_cast<int>(Piece::WhiteRook)] = 'r';
  piece_to_char[static_cast<int>(Piece::BlackBishop)] = 'B';
  piece_to_char[static_cast<int>(Piece::WhiteBishop)] = 'b';
  piece_to_char[static_cast<int>(Piece::BlackGold)] = 'G';
  piece_to_char[static_cast<int>(Piece::WhiteGold)] = 'g';
  piece_to_char[static_cast<int>(Piece::BlackSilver)] = 'S';
  piece_to_char[static_cast<int>(Piece::WhiteSilver)] = 's';
  piece_to_char[static_cast<int>(Piece::BlackKnight)] = 'N';
  piece_to_char[static_cast<int>(Piece::WhiteKnight)] = 'n';
  piece_to_char[static_cast<int>(Piece::BlackLance)] = 'L';
  piece_to_char[static_cast<int>(Piece::WhiteLance)] = 'l';
  piece_to_char[static_cast<int>(Piece::BlackPawn)] = 'P';
  piece_to_char[static_cast<int>(Piece::WhitePawn)] = 'p';
}

Piece Types::AsPromoted(Piece piece) {
  assert(non_promoted_to_promoted[static_cast<int>(piece)] != Piece::NoPiece);
  return non_promoted_to_promoted[static_cast<int>(piece)];
}
