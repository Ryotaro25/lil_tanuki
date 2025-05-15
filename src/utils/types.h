#ifndef LILTANUKI_SRC_UTIL_TYPES_H_
#define LILTANUKI_SRC_UTIL_TYPES_H_

#include <array>
#include <cassert>
#include "../piece.h"

class Types {
  public:
    static void Initialize();
    static Piece AsPromoted(Piece piece);
    static std::vector<Piece> char_to_piece;
    static std::vector<Piece> non_promoted_to_promoted;
    static std::vector<char> piece_to_char;
};

#endif
