//
// Created by David Price on 02/06/2020.
//

#ifndef ATHENA_INCLUDE_GRID_VIEW_H
#define ATHENA_INCLUDE_GRID_VIEW_H

#include "grid.h"

namespace ATA {

    template<class Type>
    class GridView {
        Type *mGridPtr;
        long mGridWidth;
        long mViewWidth;
        long mViewHeight;

    public:
        class iterator {
            friend class GridView;
            Type *mGridPtr;
            long mCurrentX;
            long mGridWidth;
            long mViewWidth;

            iterator(Type *gridPtr, long x, long viewWidth, long gridWidth)
                : mGridPtr(gridPtr), mCurrentX(x), mGridWidth(gridWidth), mViewWidth(viewWidth) {}

        public:
            Type *operator+(const long &offset) const {
                return mGridPtr + (((offset) / mViewWidth) * mGridWidth) + (offset % mViewWidth);
            }

            Type *operator-(const long &offset) const {

                return mGridPtr - (((offset) / mViewWidth) * mGridWidth) - (offset % mViewWidth);
            }

            Type *operator->() { return mGridPtr; }
            Type &operator*() { return *mGridPtr; }

            bool operator==(const iterator &other) const { return this->mGridPtr == other.mGridPtr; }
            bool operator!=(const iterator &other) const { return this->mGridPtr != other.mGridPtr; }

            auto operator++() -> iterator & {
                if (mCurrentX == mViewWidth - 1) {
                    mGridPtr += mGridWidth - mViewWidth + 1;
                    mCurrentX = 0;
                } else {
                    mGridPtr += 1;
                    ++mCurrentX;
                }
                return *this;
            }

            auto operator++(int) -> iterator {
                auto it = *this;
                return ++it;
            }

            auto operator--() -> iterator & {
                if (mCurrentX == 0) {
                    mGridPtr -= mGridWidth - mViewWidth + 1;
                    mCurrentX = mViewWidth - 1;
                } else {
                    mGridPtr -= 1;
                    --mCurrentX;
                }
                return *this;
            }

            auto operator--(int) -> iterator {
                auto it = *this;
                return --it;
            }
        };

        template<class Index>
        GridView(Grid2D<Type> &grid, const Vector2<Index> &bottomLeft, const Vector2<Index> &topRight)
            : mGridWidth(grid.size().x),
              mViewWidth((topRight.x - bottomLeft.x) + 1),
              mViewHeight((topRight.y - bottomLeft.y) + 1) {
            mGridPtr = grid.data() + ((bottomLeft.y - grid.origin().y) * mGridWidth) + bottomLeft.x - grid.origin().x;
        }

        GridView(Grid2D<Type> &grid,
                 const long &bottomLeftX, const long &bottomLeftY,
                 const long &topRightX, const long &topRightY)
            : mGridWidth(grid.size().x),
              mViewWidth(topRightX - bottomLeftX + 1),
              mViewHeight(topRightY - bottomLeftY + 1) {
            mGridPtr = grid.data() + ((bottomLeftY * mGridWidth) + bottomLeftX - grid.origin().x);
        }

        explicit GridView(Grid2D<Type> &grid)
            : mGridPtr(grid.data()),
              mGridWidth(grid.size().x),
              mViewWidth(grid.size().x),
              mViewHeight(grid.size().y) {}

        /**
         * Iterators
         */
        auto begin() -> iterator {
            return iterator(mGridPtr, 0, mViewWidth, mGridWidth);
        }

        auto end() -> iterator {
            auto endPtr = mGridPtr + (mGridWidth * mViewHeight);
            return iterator(endPtr, 0, mViewWidth, mGridWidth);
        }

        auto begin() const { return begin(); }
        auto end() const { return end(); }
    };
}// namespace ATA

#endif//ATHENA_INCLUDE_GRID_VIEW_H
