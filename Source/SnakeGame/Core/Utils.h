// Snake Game, Copyright moonabyss. Al Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnakeGame/Core/Types.h"

namespace SnakeGame
{
class IPositionRandomizer
{
public:
    virtual bool generatePosition(const Dim& dim, const TArray<CellType>& cells, Position& position) const = 0;
    virtual ~IPositionRandomizer() = default;
};

class PositionRandomizer : public IPositionRandomizer
{
public:
    virtual bool generatePosition(const Dim& dim, const TArray<CellType>& cells, Position& position) const override
    {
        const auto gridSize = dim.width * dim.height;
        const int32 startIndex = dim.width;
        const int32 endIndex = gridSize - 1 - dim.width;
        const int32 index = FMath::RandRange(startIndex, endIndex);

        for (int32 i = index; i < endIndex; ++i)
        {
            if (cells[i] == CellType::Empty)
            {
                position = indexToPos(i, dim);
                return true;
            }
        }

        for (int32 i = startIndex; i < index; ++i)
        {
            if (cells[i] == CellType::Empty)
            {
                position = indexToPos(i, dim);
                return true;
            }
        }

        return false;
    }

private:
    FORCEINLINE Position indexToPos(uint32 index, const Dim& dim) const { return Position(index % dim.width, index / dim.width); }
};

using IPositionRandomizerPtr = TSharedPtr<IPositionRandomizer>;

}  // namespace SnakeGame
