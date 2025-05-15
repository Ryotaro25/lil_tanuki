#include "position.h"
#include "utils/types.h"

#include <cstdlib>  // std::atoi
#include <cstring>
#include <iostream>
#include <sstream>

Position::Position() {
  // 手番
  side_to_move = Color::Black;
  // 手数
  play = 0;
  // 盤面の状態
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = Piece::NoPiece;
    }
  }
  // 持ち駒（各駒の枚数）
  for (int i = 0; i < static_cast<int>(Piece::NumPieces); i++) {
    hand_pieces[i] = 0;
  }
};

std::string Position::ToString() const {
  std::ostringstream writer;
  writer << "+----+----+----+----+----+----+----+----+----+" << std::endl;

  // file: 将棋盤では、横方向の列、rank: 将棋盤では、縦方向の行
  for (int rank = 0; rank < BOARD_SIZE; rank++) {
    writer << "|";
    for (int file = BOARD_SIZE - 1; file >= 0; file--) {
      writer << PieceHelper::ToHumanReadableString(board[file][rank]);
      writer << "|";
    }
    writer << std::endl;
    writer << "+----+----+----+----+----+----+----+----+----+" << std::endl;
  }

  writer << "先手 持ち駒: ";
  for (int piece = static_cast<int>(Piece::BlackPawn); piece < static_cast<int>(Piece::WhitePawn); piece++) {
    for (int i = 0; i < hand_pieces[piece]; i++) {
      writer << PieceHelper::ToHumanReadableString(static_cast<Piece>(piece)).front();
    }
  }
  writer << " , 後手 持ち駒: ";
  for (int piece = static_cast<int>(Piece::WhitePawn); piece < static_cast<int>(Piece::NumPieces); piece++) {
    for (int i = 0; i < hand_pieces[piece]; ++i) {
      writer << PieceHelper::ToHumanReadableString(static_cast<Piece>(piece)).front();
    }
  }
  writer << std::endl;

  writer << "手番 = " << (side_to_move == Color::Black ? "先手" : "後手") << std::endl;
  return writer.str();
}

// static const std::vector<std::string> piece_to_string = {
//   "　　", " 歩 ", " 香 ", " 桂 ", " 銀 ", " 金 ", " 角 ", " 飛 ", " 王 ",
//   " と ", " 杏 ", " 圭 ", " 全 ", " 馬 ", " 龍 ",
//   "歩↓", "香↓", "桂↓", "銀↓", "金↓", "角↓", "飛↓", "王↓",
//   "と↓", "杏↓", "圭↓", "全↓", "馬↓", "龍↓"
// };

std::ostream& operator<<(std::ostream& os, const Position& position) {
  return os << position.ToString();
};

const std::string Position::StartposSfen = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";

void Position::Set(const std::string& sfen) {
  side_to_move = Color::Black;
  // std::memset(board, 0, sizeof(board));
  // std::memset(hand_pieces, 0, sizeof(hand_pieces));
  // 盤面の状態
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      board[i][j] = Piece::NoPiece;
    }
  }
  // 持ち駒（各駒の枚数）
  for (int i = 0; i < static_cast<int>(Piece::NumPieces); i++) {
    hand_pieces[i] = 0;
  }
  play = 1;

  int file = BOARD_SIZE - 1;
  int rank = 0;
  int index = 0;
  bool promotion = false;

  while (true) {
    char ch = sfen[index++];
    if (ch == ' ') {
      break;
    }
    if (ch == '/') {
      rank++;
      file = BOARD_SIZE - 1;
    } else if (ch == '+') {
      promotion = true;
    } else if (std::isdigit(ch)) {
      int empty = ch - '0';
      while (empty-- > 0) {
        board[file--][rank] = Piece::NoPiece;
      }
    } else {
      Piece piece = Types::char_to_piece[static_cast<unsigned char>(ch)];
      assert(piece != Piece::NoPiece);
      if (promotion) {
        board[file--][rank] = Types::AsPromoted(piece);
      } else {
        board[file--][rank] = piece;
      }
      promotion = false;
    }
  }

  // 手番
  if (sfen[index++] == 'b') {
    side_to_move = Color::Black;
  } else {
    side_to_move = Color::White;
  }
  index++;

  int count = 0;
  while (true) {
    char ch = sfen[index++];
    if (ch == ' ') {
      break;
    }
    if (ch == '-') {
      continue;
    }
    if (std::isdigit(ch)) {
      count = count * 10 + (ch - '0');
      continue;
    }
    Piece piece = Types::char_to_piece[static_cast<unsigned char>(ch)];
    assert(piece != Piece::NoPiece);
    hand_pieces[static_cast<int>(piece)] += std::max(1, count);
    count = 0;
  }
  play = std::atoi(sfen.c_str() + index);
};
