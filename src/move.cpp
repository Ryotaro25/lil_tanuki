#include "move.h"
#include "position.h"
#include "utils/types.h"
#include <cctype>
#include <sstream>
#include <unordered_map>

// 投了・入玉宣言勝ち・無効な指し手を表すための定数
const Move Move::RESIGN = Move(2, 0, Piece::NoPiece, 2, 0, Piece::NoPiece,
                               false, false, Color::Black);

const Move Move::WIN = Move(3, 0, Piece::NoPiece, 3, 0, Piece::NoPiece,
                            false, false, Color::Black);

const Move Move::NONE = Move(4, 0, Piece::NoPiece, 4, 0, Piece::NoPiece,
                             false, false, Color::Black);

static const std::string rank_to_kanji_letters[] = {
  "一", "二", "三", "四", "五", "六", "七", "八", "九"
};

bool Move::operator==(const Move& other) const {
  return file_from == other.file_from &&
         rank_from == other.rank_from &&
         piece_from == other.piece_from &&
         file_to == other.file_to &&
         rank_to == other.rank_to &&
         piece_to == other.piece_to &&
         drop == other.drop &&
         promotion == other.promotion &&
         side_to_move == other.side_to_move;
}

std::string Move::ToString() const {
  std::ostringstream oss;
  oss << (side_to_move == Color::Black ? "▲" : "△");

  // '１' + file_to（全角文字コード）
  const std::vector<std::string> zen_files = {"１", "２", "３", "４", "５", "６", "７", "８", "９"};
  if (file_to >= 0 && file_to < 9) {
    oss << zen_files[file_to];
  }
  // 段（rank）を漢字で
  if (rank_to >= 0 && rank_to < 9) {
    oss << rank_to_kanji_letters[rank_to];
  }
  std::string piece_str = PieceHelper::ToHumanReadableString(piece_from);
  if (!piece_str.empty()) {
    oss << piece_str;
  }

  if (promotion) {
    oss << "成";
  }
  return oss.str();
}

std::string Move::ToUsiString() const {
  if (*this == RESIGN) {
    return "resign";
  }
  if (*this == WIN) {
    return "win";
  }

  std::string usi_string;
  // '1' や 'a' を使って文字コードをUSI用の座標コードに変換
  if (drop) {
    usi_string += std::toupper(PieceHelper::ToUsiChar(piece_from)); // ToUsiChar未実装
    usi_string += "*";
  } else {
    usi_string += static_cast<char>(file_from + '1');
    usi_string += static_cast<char>(rank_from + 'a');
  }

  usi_string += static_cast<char>(file_to + '1');
  usi_string += static_cast<char>(rank_to + 'a');
  if (promotion) {
    usi_string += "+";
  }
  return usi_string;
}

Move Move::FromUsiString(const Position& pos, const std::string& str) {
  if (str == "resign") {
    return Move::RESIGN;
  }
  if (str == "win") {
    return Move::WIN;
  }
  if (str == "none") {
    return Move::NONE;
  }

  Move move;
  if (str[1] == '*') {
    // 駒打ち
    move.file_from = -1;
    move.rank_from = -1;
    move.piece_from = Types::char_to_piece.at(str[0]);

    if (pos.side_to_move == Color::White) {
      move.piece_from = PieceHelper::AsOpponentHandPiece(move.piece_from);
    }
    move.drop = true;
  } else {
    move.file_from = str[0] - '1';
    move.rank_from = str[1] - 'a';
    move.piece_from = pos.board[move.file_from][move.rank_from];
    move.drop = false;
  }

  move.file_to = str[2] - '1';
  move.rank_to = str[3] - 'a';
  move.piece_to = pos.board[move.file_to][move.rank_to];
  move.promotion = str.length() == 5;
  move.side_to_move = pos.side_to_move;
  return move;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
  return os << move.ToString();
}

namespace std {
  template<>
  struct hash<Move> {
    std::size_t operator()(const Move& m) const {
      std::size_t seed = 0;
      auto hash_combine = [](std::size_t& seed, auto val) {
        seed ^= std::hash<decltype(val)>{}(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      };

      hash_combine(seed, m.file_from);
      hash_combine(seed, m.rank_from);
      hash_combine(seed, static_cast<int>(m.piece_from));
      hash_combine(seed, m.file_to);
      hash_combine(seed, m.rank_to);
      hash_combine(seed, static_cast<int>(m.piece_to));
      hash_combine(seed, m.drop);
      hash_combine(seed, m.promotion);
      hash_combine(seed, static_cast<int>(m.side_to_move));
      return seed;
    }
  };
}
