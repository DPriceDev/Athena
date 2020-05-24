//
// Created by David Price on 24/05/2020.
//

#ifndef ATHENA_GRID_H
#define ATHENA_GRID_H

#include <array>
#include <utility>
#include <algorithm>

namespace ATA {

    template<class Type>
    class Grid2D {
        std::vector<Type> mGrid;
        long mOriginX, mOriginY;
        long mWidth, mHeight;
        std::array<long, 4> mBounds;

    public:
        Grid2D(long width, long height, long originX = 0L, long originY = 0L)
            : mOriginX(originX), mOriginY(originY), mWidth(width), mHeight(height),
              mBounds({ originY + height, originX + width, originY, originX }){

            mGrid.resize(width*height);
            std::fill_n(mGrid.begin(), (width * height), nullptr);
        }

        explicit Grid2D(std::tuple<long, long, long, long> gridParameters)
                : mOriginX(std::get<2>(gridParameters)), mOriginY(std::get<3>(gridParameters)),
                  mWidth(std::get<0>(gridParameters)), mHeight(std::get<1>(gridParameters)),
                  mBounds({ mOriginY + mHeight, mOriginX + mWidth, mOriginY, mOriginX }){

            mGrid.resize(std::get<0>(gridParameters) * std::get<1>(gridParameters));
            std::fill_n(mGrid.begin(), (mWidth * mHeight), Type());
        }

        Type& operator()(long x, long y) {
            auto yPosition = (y - mOriginY) * mWidth;
            auto xPosition = x - mOriginX;
            return mGrid[yPosition + xPosition];
        }

        Type& at(long x, long y) {
            if(x >= mOriginX && y >= mOriginY
            && x < mOriginX + mWidth && y <= mOriginY + mHeight ) {
                return this->operator()(x, y);
            } else {
                throw std::out_of_range("2D grid");
            }
        }

        Type& at(std::pair<long, long> pair) {
            return this->at(pair.first, pair.second);
        }

        [[nodiscard]]
        const auto & getBounds() const {
            return mBounds;
        }

        [[nodiscard]]
        bool isPointInGrid(long x, long y) const {
            return x >= mOriginX && x < mOriginX + mWidth - 1
                && y >= mOriginY && y < mOriginY + mHeight - 1;
        }

        [[nodiscard]]
        const auto & size() const {
            return std::make_pair(mWidth, mHeight);
        }

        [[nodiscard]]
        const auto & origin() const {
            return std::make_pair(mOriginX, mOriginY);
        }

        [[nodiscard]]
        auto gridParameters() const {
            return std::make_tuple(mWidth, mHeight, mOriginX, mOriginY);
        }
    };
}

#endif //ATHENA_GRID_H
