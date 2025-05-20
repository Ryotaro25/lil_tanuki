#ifndef LILTANUKI_SRC_UTIL_DIRECTION_H_
#define LILTANUKI_SRC_UTIL_DIRECTION_H_
#include <vector>
struct Direction {
  int df;
  int dr;

  constexpr Direction(int df, int dr) : df(df), dr(dr) {}
};

struct MoveDirection {
  Direction dir;
  bool is_long;

  constexpr MoveDirection(Direction dir, bool is_long = false) : dir(dir), is_long(is_long) {} 
};

class DirectionTypes {
  public:
    static const std::vector<std::vector<MoveDirection>> move_directions;

  private:
    static const Direction up_left;
    static const Direction up;
    static const Direction up_right;
    static const Direction left;
    static const Direction right;
    static const Direction down_left;
    static const Direction down;
    static const Direction down_right;
};

#endif // LILTANUKI_SRC_POSITION_H_
