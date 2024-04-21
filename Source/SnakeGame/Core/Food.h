// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Core/Types.h"

namespace SnakeGame
{

class SNAKEGAME_API Food
{
public:
    Food() = default;

    /**
     * Sets food position
     * @param position  position on the grid
     */
    void setPosition(const Position& position);

    /**
     * Returns food position
     * @return Position  food position
     */
    Position position() const;

private:
    Position m_position{Position::Zero};
};
}  // namespace SnakeGame
