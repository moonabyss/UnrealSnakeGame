// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace SnakeGame
{
struct Dim
{
    uint32 width;
    uint32 height;
};

struct Position
{
    // clang-format off
    Position(uint32 inX, uint32 inY) : x(inX), y(inY) {}
    // clang-format on
    uint32 x;
    uint32 y;

    FORCEINLINE Position& operator+=(const Position& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    static Position Zero;
};

struct Input
{
    int8 x;
    int8 y;

    FORCEINLINE bool opposite(const Input& rhs) const  //
    {
        return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
    }

    static Input Default;
};

enum class CellType
{
    Empty = 0,
    Wall,
    Snake
    // Food
};

struct Settings
{
    Dim gridDims{40, 10};
    struct Snake
    {
        uint32 defaultSize{4};
        Position startPosition{Position::Zero};
    } snake;
    float gameSpeed{1.0f};
};

using TPositionPtr = TDoubleLinkedList<Position>::TDoubleLinkedListNode;

class TSnakeList : public TDoubleLinkedList<Position>
{
public:
    void MoveTail(TPositionPtr* tail, TPositionPtr* head, const Position& pos)
    {
        RemoveNode(tail);
        InsertNode(pos, head);
    }
};
}  // namespace SnakeGame
