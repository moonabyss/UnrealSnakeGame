// Snake Game, Copyright moonabyss. Al Rights Reserved.

#include "SnakeGame/Core/Food.h"

using namespace SnakeGame;

void SnakeGame::Food::setPosition(const Position& position)
{
    m_position = position;
}

Position SnakeGame::Food::position() const
{
    return m_position;
}
