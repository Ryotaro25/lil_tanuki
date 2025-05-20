#include "direction.h"

const Direction DirectionTypes::up_left(+1, -1);
const Direction DirectionTypes::up(0, -1);
const Direction DirectionTypes::up_right(-1, -1);
const Direction DirectionTypes::left(+1, 0);
const Direction DirectionTypes::right(-1, 0);
const Direction DirectionTypes::down_left(+1, +1);
const Direction DirectionTypes::down(0, +1);
const Direction DirectionTypes::down_right(-1, +1);

const std::vector<std::vector<MoveDirection>> DirectionTypes::move_directions = {
  { // NoPiece
  },
  {
    // BlackPawn 歩
    MoveDirection(DirectionTypes::up)
  },
  {
    // BlackLance 香
    MoveDirection(DirectionTypes::up, true)
  },
  {
    // BlackKnight 桂
    MoveDirection(Direction(+1, -2)),
    MoveDirection(Direction(-1, -2))
  },
  {
    // BlackSilver 銀
    MoveDirection(DirectionTypes::up_left),
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::up_right),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackGold 金
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackBishop 角
    MoveDirection(DirectionTypes::up_left, true),
    MoveDirection(DirectionTypes::up_right, true),
    MoveDirection(DirectionTypes::down_left, true),
    MoveDirection(DirectionTypes::down_right, true)
  },
  {
    // BlackRook 飛
    MoveDirection(DirectionTypes::up, true),
    MoveDirection(DirectionTypes::left, true),
    MoveDirection(DirectionTypes::right, true),
    MoveDirection(DirectionTypes::down, true)
  },
  {
    // BlackKing 王
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::up_left),
    MoveDirection(DirectionTypes::up_right),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackPromotedPawn と
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackPromotedLance 杏
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left), 
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down), 
    MoveDirection(DirectionTypes::down_left), 
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackPromotedKnight 圭
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left), 
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackPromotedSilver 全
    MoveDirection(DirectionTypes::up), 
    MoveDirection(DirectionTypes::left), 
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down), 
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // BlackHorse 馬
    MoveDirection(DirectionTypes::up_left, true),
    MoveDirection(DirectionTypes::up_right, true),
    MoveDirection(DirectionTypes::down_left, true), 
    MoveDirection(DirectionTypes::down_right, true),
    MoveDirection(DirectionTypes::up), 
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right), 
    MoveDirection(DirectionTypes::down)
  },
  {
    // BlackDragon 龍
    MoveDirection(DirectionTypes::up, true),
    MoveDirection(DirectionTypes::left, true),
    MoveDirection(DirectionTypes::right, true),
    MoveDirection(DirectionTypes::down, true),
    MoveDirection(DirectionTypes::up_left),
    MoveDirection(DirectionTypes::up_right),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhitePawn
    MoveDirection(DirectionTypes::up)
  },
  {
    // WhiteLance
    MoveDirection(DirectionTypes::up, true)
  },
  {
    // WhiteKnight
    MoveDirection(Direction(+1, -2)),
    MoveDirection(Direction(-1, -2))
  },
  {
    // WhiteSilver
    MoveDirection(DirectionTypes::up_left),
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::up_right),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhiteGold
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhiteBishop
    MoveDirection(DirectionTypes::up_left, true),
    MoveDirection(DirectionTypes::up_right, true),
    MoveDirection(DirectionTypes::down_left, true),
    MoveDirection(DirectionTypes::down_right, true)
  },
  {
    // WhitekRook
    MoveDirection(DirectionTypes::up, true),
    MoveDirection(DirectionTypes::left, true),
    MoveDirection(DirectionTypes::right, true),
    MoveDirection(DirectionTypes::down, true)
  },
  {
    // WhiteKing
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::up_left),
    MoveDirection(DirectionTypes::up_right),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhitePromotedPawn
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhitePromotedLance
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left), 
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down), 
    MoveDirection(DirectionTypes::down_left), 
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhitePromotedKnight
    MoveDirection(DirectionTypes::up),
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down),
    MoveDirection(DirectionTypes::down_left), 
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhitePromotedSilver
    MoveDirection(DirectionTypes::up), 
    MoveDirection(DirectionTypes::left), 
    MoveDirection(DirectionTypes::right),
    MoveDirection(DirectionTypes::down), 
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // WhiteHorse
    MoveDirection(DirectionTypes::up_left, true),
    MoveDirection(DirectionTypes::up_right, true),
    MoveDirection(DirectionTypes::down_left, true), 
    MoveDirection(DirectionTypes::down_right, true),
    MoveDirection(DirectionTypes::up), 
    MoveDirection(DirectionTypes::left),
    MoveDirection(DirectionTypes::right), 
    MoveDirection(DirectionTypes::down)
  },
  {
    // WhiteDragon
    MoveDirection(DirectionTypes::up, true),
    MoveDirection(DirectionTypes::left, true),
    MoveDirection(DirectionTypes::right, true),
    MoveDirection(DirectionTypes::down, true),
    MoveDirection(DirectionTypes::up_left),
    MoveDirection(DirectionTypes::up_right),
    MoveDirection(DirectionTypes::down_left),
    MoveDirection(DirectionTypes::down_right)
  },
  {
    // NumPieces
  }
};
