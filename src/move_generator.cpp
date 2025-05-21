#include "direction.h"
#include "move.h"
#include "move_generator.h"
#include "position.h"

std::vector<Move> MoveGenerator::GenerateMoves(const Position& position) {
  std::vector<Move> moves;
  std::vector<Move> non_capture_promotion_moves;
  std::vector<Move> non_capture_non_promotion_moves;

  Color side_to_move = position.side_to_move;
  const auto& board = position.board;
  const auto& hand_pieces = position.hand_pieces;

  for (int file_from = 0; file_from < Position::BOARD_SIZE; file_from++) {
    for (int rank_from = 0; rank_from < Position::BOARD_SIZE; rank_from++) {
      Piece piece_from = board[file_from][rank_from];
      if (piece_from == Piece::NoPiece) {
        // 駒が置かれていないので何もしない
        continue;
      }
      if (PieceHelper::ToColor(piece_from) != side_to_move) {
        // 相手の駒なので何もしない
        continue;
      }

      for (const auto& move_direction : DirectionTypes::move_directions[static_cast<int>(piece_from)]) {
        int max_distance = move_direction.is_long ? 8 : 1;
        int file_to = file_from;
        int rank_to = rank_from;

        for (int distance = 0; distance < max_distance; distance++) {
          file_to += move_direction.dir.df;
          rank_to += move_direction.dir.dr;

          if (file_to < 0 || file_to >= Position::BOARD_SIZE ||
               rank_to < 0 || rank_to >= Position::BOARD_SIZE) {
            // 盤外
            continue;
          }
          Piece piece_to = board[file_to][rank_to];
          if (piece_to != Piece::NoPiece && PieceHelper::ToColor(piece_to) == side_to_move) {
            // 味方の駒がいる
            break;
          }
          if (PieceHelper::CanPromote(piece_from) && (
              (side_to_move == Color::Black && (rank_to <= 2 || rank_from <= 2)) ||
              (side_to_move == Color::White && (rank_to >= 6 || rank_from >= 6)))) {
            
            Move move{file_from, rank_from, piece_from,
                      file_to, rank_to, piece_to,
                      false, true, side_to_move};

            if (piece_to != Piece::NoPiece) {
              // 駒を取る指し手の場合はすぐに返す
              moves.push_back(move);
            } else {
              // 駒を取らない指し手の場合は後で返す
              non_capture_promotion_moves.push_back(move);
            }
          }

          if (PieceHelper::CanPutWithoutPromotion(piece_from, rank_to)) {
            Move move{file_from, rank_from, piece_from,
                      file_to, rank_to, piece_to,
                      false, false, side_to_move};

            if (piece_to != Piece::NoPiece) {
              // 駒を取る指し手の場合はすぐに返す
              moves.push_back(move);
            } else {
              non_capture_non_promotion_moves.push_back(move);
            }
          }
          if (piece_to != Piece::NoPiece) {
            break;
          }
        }
      }
    }
  }
  for (const auto& move : non_capture_promotion_moves) {
    moves.push_back(move);
  }
  for (const auto& move : non_capture_non_promotion_moves) {
    moves.push_back(move);
  }
  Piece min_piece = (side_to_move == Color::Black) ? Piece::BlackPawn : Piece::WhitePawn;
  Piece max_piece = (side_to_move == Color::Black) ? Piece::BlackRook : Piece::WhiteRook;

  for (int pf = static_cast<int>(min_piece); pf <= static_cast<int>(max_piece); ++pf) {
    Piece piece_from = static_cast<Piece>(pf);
    if (hand_pieces[pf] == 0) {
      continue;
    }

    for (int file_to = 0; file_to < Position::BOARD_SIZE; ++file_to) {
      for (int rank_to = 0; rank_to < Position::BOARD_SIZE; ++rank_to) {
        if (board[file_to][rank_to] != Piece::NoPiece) {
          continue;
        }
        if (!PieceHelper::CanPutWithoutPromotion(piece_from, rank_to)) {
          continue;
        }
        if ((piece_from == Piece::BlackPawn || piece_from == Piece::WhitePawn) &&
            MoveGenerator::IsPawnExist(board, file_to, piece_from)) {
          continue;
        }

        moves.push_back(Move{-1, -1, piece_from, file_to, rank_to, Piece::NoPiece,
                        true, false, side_to_move});
      }
    }
  }
  return moves;
}

bool MoveGenerator::IsPawnExist(const Piece board[9][9], int file, Piece pawn) {
  for (int rank = 0; rank < Position::BOARD_SIZE; ++rank) {
    if (board[file][rank] == pawn) {
      return true;
    }
  }
  return false;
}

std::vector<Move> MoveGenerator::GenerateLegalMoves(const Position& position) {
  std::vector<Move> legal_moves;
  auto pseudo_moves = GenerateMoves(position);

  for (const auto& move : pseudo_moves) {
    Position temp_pos = position;
    temp_pos.DoMove(move);

    auto [king_file, king_rank] = temp_pos.FindKing(move.side_to_move);
    if (!temp_pos.IsSquareAttacked(king_file, king_rank, Opponent(position.side_to_move))) {
      legal_moves.push_back(move);
    }
  }
  return legal_moves;
}
