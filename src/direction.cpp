#include "direction.h"

const Direction Types::up_left(+1, -1);
const Direction Types::up(0, -1);
const Direction Types::up_right(-1, -1);
const Direction Types::left(+1, 0);
const Direction Types::right(-1, 0);
const Direction Types::down_left(+1, +1);
const Direction Types::down(0, +1);
const Direction Types::down_right(-1, +1);

const std::vector<std::vector<MoveDirection>> Types::move_directions = {
  { // NoPiece
  },
  {
    // BlackPawn 歩
    MoveDirection(Types::up)
  },
  {
    // BlackLance 香
    MoveDirection(Types::up, true)
  },
  {
    // BlackKnight 桂
    MoveDirection(Direction(+1, -2)),
    MoveDirection(Direction(-1, -2))
  },
  {
    // BlackSilver 銀
    MoveDirection(Types::up_left),
    MoveDirection(Types::up),
    MoveDirection(Types::up_right),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // BlackGold 金
    MoveDirection(Types::up),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // BlackBishop 角
    MoveDirection(Types::up_left, true),
    MoveDirection(Types::up_right, true),
    MoveDirection(Types::down_left, true),
    MoveDirection(Types::down_right, true)
  },
  {
    // BlackRook 飛
    MoveDirection(Types::up, true),
    MoveDirection(Types::left, true),
    MoveDirection(Types::right, true),
    MoveDirection(Types::down, true)
  },
  {
    // BlackKing 王
    MoveDirection(Types::up),
    MoveDirection(Types::up_left),
    MoveDirection(Types::up_right),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // BlackPromotedPawn と
    MoveDirection(Types::up),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // BlackPromotedLance 杏
    MoveDirection(Types::up),
    MoveDirection(Types::left), 
    MoveDirection(Types::right),
    MoveDirection(Types::down), 
    MoveDirection(Types::down_left), 
    MoveDirection(Types::down_right)
  },
  {
    // BlackPromotedKnight 圭
    MoveDirection(Types::up),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left), 
    MoveDirection(Types::down_right)
  },
  {
    // BlackPromotedSilver 全
    MoveDirection(Types::up), 
    MoveDirection(Types::left), 
    MoveDirection(Types::right),
    MoveDirection(Types::down), 
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // BlackHorse 馬
    MoveDirection(Types::up_left, true),
    MoveDirection(Types::up_right, true),
    MoveDirection(Types::down_left, true), 
    MoveDirection(Types::down_right, true),
    MoveDirection(Types::up), 
    MoveDirection(Types::left),
    MoveDirection(Types::right), 
    MoveDirection(Types::down)
  },
  {
    // BlackDragon 龍
    MoveDirection(Types::up, true),
    MoveDirection(Types::left, true),
    MoveDirection(Types::right, true),
    MoveDirection(Types::down, true),
    MoveDirection(Types::up_left),
    MoveDirection(Types::up_right),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // WhitePawn
    MoveDirection(Types::up)
  },
  {
    // WhiteLance
    MoveDirection(Types::up, true)
  },
  {
    // WhiteKnight
    MoveDirection(Direction(+1, -2)),
    MoveDirection(Direction(-1, -2))
  },
  {
    // WhiteSilver
    MoveDirection(Types::up_left),
    MoveDirection(Types::up),
    MoveDirection(Types::up_right),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // WhiteGold
    MoveDirection(Types::up),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // WhiteBishop
    MoveDirection(Types::up_left, true),
    MoveDirection(Types::up_right, true),
    MoveDirection(Types::down_left, true),
    MoveDirection(Types::down_right, true)
  },
  {
    // WhitekRook
    MoveDirection(Types::up, true),
    MoveDirection(Types::left, true),
    MoveDirection(Types::right, true),
    MoveDirection(Types::down, true)
  },
  {
    // WhiteKing
    MoveDirection(Types::up),
    MoveDirection(Types::up_left),
    MoveDirection(Types::up_right),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // WhitePromotedPawn
    MoveDirection(Types::up),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // WhitePromotedLance
    MoveDirection(Types::up),
    MoveDirection(Types::left), 
    MoveDirection(Types::right),
    MoveDirection(Types::down), 
    MoveDirection(Types::down_left), 
    MoveDirection(Types::down_right)
  },
  {
    // WhitePromotedKnight
    MoveDirection(Types::up),
    MoveDirection(Types::left),
    MoveDirection(Types::right),
    MoveDirection(Types::down),
    MoveDirection(Types::down_left), 
    MoveDirection(Types::down_right)
  },
  {
    // WhitePromotedSilver
    MoveDirection(Types::up), 
    MoveDirection(Types::left), 
    MoveDirection(Types::right),
    MoveDirection(Types::down), 
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // WhiteHorse
    MoveDirection(Types::up_left, true),
    MoveDirection(Types::up_right, true),
    MoveDirection(Types::down_left, true), 
    MoveDirection(Types::down_right, true),
    MoveDirection(Types::up), 
    MoveDirection(Types::left),
    MoveDirection(Types::right), 
    MoveDirection(Types::down)
  },
  {
    // WhiteDragon
    MoveDirection(Types::up, true),
    MoveDirection(Types::left, true),
    MoveDirection(Types::right, true),
    MoveDirection(Types::down, true),
    MoveDirection(Types::up_left),
    MoveDirection(Types::up_right),
    MoveDirection(Types::down_left),
    MoveDirection(Types::down_right)
  },
  {
    // NumPieces
  }
};
