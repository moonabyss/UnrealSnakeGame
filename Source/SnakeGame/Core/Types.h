// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Containers/List.h"

namespace SnakeGame
{
struct Dim
{
    uint32 width;
    uint32 height;

    FORCEINLINE bool operator==(const Dim& rhs) const { return width == rhs.width && height == rhs.height; }
};

struct Position
{
    // clang-format off
    Position(uint32 inX, uint32 inY) : x(inX), y(inY) {}
    Position(const Position& position = Position::Zero) : x(position.x), y(position.y) {}
    // clang-format on
    uint32 x;
    uint32 y;

    FORCEINLINE Position& operator+=(const Position& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    FORCEINLINE bool operator==(const Position& rhs) const { return x == rhs.x && y == rhs.y; }

    const static Position Zero;
};

struct Input
{
    int8 x;
    int8 y;

    FORCEINLINE bool opposite(const Input& rhs) const  //
    {
        return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
    }

    const static Input Default;
};

enum class CellType
{
    Empty = 0,
    Wall,
    Snake,
    Food
};

struct Settings
{
    Dim gridDims{10, 10};
    struct Snake
    {
        uint32 defaultSize{4};
        Position startPosition{Position::Zero};
    } snake;
    float gameSpeed{1.0f};
};

using TSnakeList = TDoubleLinkedList<Position>;
using TPositionPtr = TSnakeList::TDoubleLinkedListNode;

enum class GameplayEvent
{
    GameOver = 0,
    GameCompleted,
    FoodTaken
};

using GameplayEventCallback = TFunction<void(GameplayEvent)>;

}  // namespace SnakeGame
