#include "position.h"
#include "utils/types.h"
#include "direction.h"

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

void Position::PutPiece(int file, int rank, Piece piece) {
  assert(file >= 0 && file < BOARD_SIZE);
  assert(rank >= 0 && rank < BOARD_SIZE);
  assert(board[file][rank] == Piece::NoPiece);
  board[file][rank] = piece;
};

void Position::RemovePiece(int file, int rank) {
  assert(file >= 0 && file < BOARD_SIZE);
  assert(rank >= 0 && rank < BOARD_SIZE);
  assert(board[file][rank] != Piece::NoPiece);
  board[file][rank] = Piece::NoPiece;
};

void Position::PutHandPiece(Piece piece) {
  int index = static_cast<int>(piece);
  assert(index >= 0 && index < static_cast<int>(Piece::NumPieces));
  hand_pieces[index]++;
};

void Position::RemoveHandPiece(Piece piece) {
  int index = static_cast<int>(piece);
  assert(index >= 0 && index < static_cast<int>(Piece::NumPieces));
  assert(hand_pieces[index] > 0);
  hand_pieces[index]--;
};

void Position::DoMove(const Move& move) {
  assert(side_to_move == move.side_to_move);
  assert(move.drop || board[move.file_from][move.rank_from] == move.piece_from);
  assert(move.drop || board[move.file_to][move.rank_to] == move.piece_to);

  // 相手の駒を取る
  if (move.piece_to != Piece::NoPiece) {
    RemovePiece(move.file_to, move.rank_to);
    PutHandPiece(PieceHelper::AsOpponentHandPiece(move.piece_to));
  }

  if (move.drop) {
    // 持ち駒を打つ
    RemoveHandPiece(move.piece_from);
  } else {
    // 盤面の駒を移動
    RemovePiece(move.file_from, move.rank_from);
  }

  Piece final_piece = move.promotion ? Types::AsPromoted(move.piece_from) : move.piece_from;
  PutPiece(move.file_to, move.rank_to, final_piece);
  side_to_move = (side_to_move == Color::Black) ? Color::White : Color::Black;
  play++;
  last_move = move;
};

void Position::UndoMove(const Move& move) {
  assert(side_to_move != move.side_to_move);
  play--;
  side_to_move = (side_to_move == Color::Black ? Color::White : Color::Black);

  RemovePiece(move.file_to, move.rank_to);
  if (move.drop) {
    // 持ち駒を打った場合 → 盤面から取り除き、持ち駒に戻す
    PutHandPiece(move.piece_from);
  } else {
    // 盤面の駒を元の位置に戻す
    PutPiece(move.file_from, move.rank_from, move.piece_from);
  }

  if (move.piece_to != Piece::NoPiece) {
    // 取った駒を持ち駒から取り除き、盤面に戻す
    RemoveHandPiece(PieceHelper::AsOpponentHandPiece(move.piece_to));
    PutPiece(move.file_to, move.rank_to, move.piece_to);
   }
};

std::pair<int, int> Position::FindKing(Color color) {
  for (int file = 0; file < BOARD_SIZE; ++file) {
    for (int rank = 0; rank < BOARD_SIZE; ++rank) {
      Piece p = board[file][rank];
      if ((color == Color::Black && p == Piece::BlackKing) ||
          (color == Color::White && p == Piece::WhiteKing)) {
        return {file, rank};
      }
    }
  }
  return {-1, -1}; // エラー値
}

bool Position::IsSquareAttacked(int file, int rank, Color by_color) {
  // 各マスから、その駒が(file, rank)を攻撃できるかを判定
  for (int f = 0; f < BOARD_SIZE; f++) {
    for (int r = 0; r < BOARD_SIZE; r++) {
      Piece attacker = board[f][r];
      if (attacker == Piece::NoPiece || PieceHelper::ToColor(attacker) != by_color) {
        continue;
      }
        
      // attacker の動きが (file, rank) に届くか？
      for (const auto& md : DirectionTypes::move_directions[static_cast<int>(attacker)]) {
        int ff = f;
        int rr = r;
        int max_dist = md.is_long ? 8 : 1;
        for (int d = 0; d < max_dist; ++d) {
          ff += md.dir.df;
          rr += md.dir.dr;
          if (ff < 0 || ff >= BOARD_SIZE || rr < 0 || rr >= BOARD_SIZE) {
            break;
          }

          if (ff == file && rr == rank) {
            return true;
          }

           // 駒で遮られる
          if (board[ff][rr] != Piece::NoPiece) {
            break;
          }
        }
      }
    }
  }
  return false;
}

