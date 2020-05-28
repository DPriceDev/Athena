//
// Created by David Price on 24/05/2020.
//

#ifndef ATHENA_GRID_H
#define ATHENA_GRID_H

#include <algorithm>
#include <vector>
#include <array>
#include <tuple>
#include <utility>

#include "vector.h"

namespace ATA {

    /**
     *
     */
    struct GridParameters {
        long mOriginX, mOriginY;
        long mWidth, mHeight;

        GridParameters(const std::size_t width, const std::size_t height, const long originX, const long originY)
                : mOriginX(originX), mOriginY(originY), mWidth(width), mHeight(height) {}
    };

    /**
     *
     */
    struct GridBounds {
        std::array<long, 4> mBounds;

        GridBounds(const long top, const long right, const long bottom, const long left)
            : mBounds({top, right, bottom, left}) {}

        [[nodiscard]] auto top() const -> long {
            return mBounds[0];
        }
        [[nodiscard]] auto right() const -> long {
            return mBounds[1];
        }
        [[nodiscard]] auto bottom() const -> long {
            return mBounds[2];
        }
        [[nodiscard]] auto left() const -> long {
            return mBounds[3];
        }
    };

    /**
     *
     * @tparam Type
     */
    template<class Type>
    class Grid2D {
        std::vector<Type> mGrid;
        long mOriginX, mOriginY;
        long mWidth, mHeight;
        GridBounds mBounds;

    public:
        using iterator = typename std::vector<Type>::iterator;
        using const_iterator = typename std::vector<Type>::const_iterator;

//        class column_iterator {
//
//        };
//
//        class row_iterator {
//
//        };
//
//        class const_column_iterator {
//
//        };
//
//        class const_row_iterator {
//
//        };

        Grid2D(long width, long height, long originX = 0L, long originY = 0L)
            : mOriginX(originX), mOriginY(originY), mWidth(width), mHeight(height),
              mBounds(mHeight + mOriginY, mOriginX + mWidth, originY, originX) {

            mGrid.resize(width * height);
        }

        explicit Grid2D(GridParameters gridParameters)
            : mOriginX(gridParameters.mOriginX), mOriginY(gridParameters.mOriginY),
              mWidth(gridParameters.mWidth), mHeight(gridParameters.mHeight),
              mBounds({mOriginY + mHeight, mOriginX + mWidth, mOriginY, mOriginX}) {

            mGrid.resize(mWidth * mHeight);
        }

        auto operator()(long x, long y) -> Type & {
            auto yPosition = (y - mOriginY) * mWidth;
            auto xPosition = x - mOriginX;
            return mGrid[yPosition + xPosition];
        }

        auto at(long x, long y) -> Type & {
            if (x >= mOriginX && y >= mOriginY && x < mOriginX + mWidth && y <= mOriginY + mHeight) {
                return this->operator()(x, y);
            } else {
                throw std::out_of_range("2D grid");
            }
        }

        auto at(std::pair<long, long> pair) -> Type & {
            return this->at(pair.first, pair.second);
        }

        template<class Index>
        auto at(Vector2<Index> index) -> Type & {
            return this->at(index.x, index.y);
        }

        auto begin() -> iterator {
            return mGrid.begin();
        }

        auto begin() const -> const_iterator {
            return mGrid.begin();
        }

        auto end() -> iterator {
            return mGrid.end();
        }

        auto end() const -> const_iterator {
            return mGrid.begin();
        }

        [[nodiscard]] auto getBounds() const -> const GridBounds & {
            return mBounds;
        }

        [[nodiscard]] auto isPointInGrid(long x, long y) const -> bool {
            return x >= mBounds.left()
                   && x <= mBounds.right() - 1
                   && y >= mBounds.bottom()
                   && y <= mBounds.top()- 1;
        }

        [[nodiscard]] auto size() const -> std::pair<std::size_t, std::size_t> {
            return std::make_pair(mWidth, mHeight);
        }

        [[nodiscard]] auto origin() const -> std::pair<long, long> {
            return std::make_pair(mOriginX, mOriginY);
        }

        [[nodiscard]] auto gridParameters() const -> GridParameters {
            return GridParameters(mWidth, mHeight, mOriginX, mOriginY);
        }
    };
}// namespace ATA

#endif//ATHENA_GRID_H
