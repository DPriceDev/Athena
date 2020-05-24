//
// Created by David Price on 24/05/2020.
//

#ifndef ATHENA_GRID_H
#define ATHENA_GRID_H

#include <array>

namespace AAF {

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

            mGrid.reserve(width*height);
            std::fill(mGrid.begin(), mGrid.begin() + (width * height), nullptr);
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

        [[nodiscard]]
        const auto & getBounds() const {
            return mBounds;
        }

    };
}

#endif //ATHENA_GRID_H
