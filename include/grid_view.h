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

        /**
         * Iterator Class
         */
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

        /**
         * Row Iterator Class
         */
        class row_iterator {
            friend class GridView;
            Type *mGridPtr;
            explicit row_iterator(Type *gridPtr) : mGridPtr(gridPtr) {}

        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = Type;
            using difference_type = int;
            using pointer = Type*;
            using reference = Type&;

            Type *operator+(const long &offset) const { return mGridPtr + offset; }
            Type *operator-(const long &offset) const { return mGridPtr - offset; }
            Type *operator->() { return mGridPtr; }
            Type &operator*() { return *mGridPtr; }

            bool operator==(const row_iterator &other) const { return this->mGridPtr == other.mGridPtr; }
            bool operator!=(const row_iterator &other) const { return this->mGridPtr != other.mGridPtr; }

            auto operator++() -> row_iterator & {
                ++mGridPtr;
                return *this;
            }

            auto operator++(int) -> row_iterator {
                auto it = *this;
                return ++it;
            }

            auto operator--() -> row_iterator & {
                --mGridPtr;
                return *this;
            }

            auto operator--(int) -> row_iterator {
                auto it = *this;
                return --it;
            }
        };

        /**
         * Column Iterator Class
         */
        class column_iterator {
            friend class GridView;
            Type *mGridPtr;
            long mWidth;
            explicit column_iterator(Type *gridPtr, long width) : mGridPtr(gridPtr), mWidth(width) {}

        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = Type;
            using difference_type = int;
            using pointer = Type*;
            using reference = Type&;

            Type *operator+(const size_t &offset) const { return mGridPtr + (offset * static_cast<size_t>(mWidth)); }
            Type *operator-(const size_t &offset) const { return mGridPtr - (offset * static_cast<size_t>(mWidth)); }
            Type *operator->() { return mGridPtr; }
            Type &operator*() { return *mGridPtr; }

            bool operator==(const column_iterator &other) { return this->mGridPtr == other.mGridPtr; }
            bool operator!=(const column_iterator &other) { return this->mGridPtr != other.mGridPtr; }

            auto operator++() -> column_iterator & {
                mGridPtr += mWidth;
                return *this;
            }

            auto operator++(int) -> column_iterator {
                auto it = *this;
                return ++it;
            }

            auto operator--() -> column_iterator & {
                mGridPtr -= mWidth;
                return *this;
            }

            auto operator--(int) -> column_iterator {
                auto it = *this;
                return --it;
            }

            auto row() -> row_iterator {
                return row_iterator(mGridPtr);
            }
        };

        /**
         * Constructors
         * todo: add init for an array or vector along with size? uncouples from grid class specifically
         */
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
         * Accessors
         */

        auto operator()(const long &x, const long &y) -> Type & {
            return *(mGridPtr + x + (y * mGridWidth));
        }

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

        auto columnBegin(const long &column = 0) -> column_iterator {
            return column_iterator(mGridPtr + column, mGridWidth);
        }
        auto columnEnd(const long &column = 0) -> column_iterator {
            return column_iterator(mGridPtr + (mGridWidth * mViewHeight) + column, mGridWidth);
        }
        auto columnFront(const long &column = 0) -> Type & {
            return this->operator()(column, 0);
        }
        auto columnBack(const long &column = 0) -> Type & {
            return this->operator()(column, mViewHeight - 1);
        }
        auto column(const long &column = 0, const long &row = 0) -> column_iterator {
            return column_iterator(mGridPtr + column + (row * mGridWidth), mGridWidth);
        }

        auto columnBegin(const long &column = 0) const -> column_iterator { return this->columnBegin(column); }
        auto columnEnd(const long &column = 0) const -> column_iterator { return this->columnEnd(column); }
        auto column(const long &column = 0, const long &row = 0) const -> column_iterator { return this->column(column, row); }

        template<class index>
        auto column(const Vector2<index> &index2d) -> column_iterator { return column(index2d.x, index2d.y); }
        template<class index>
        auto column(const Vector2<index> &index2d) const -> column_iterator { return column(index2d.x, index2d.y); }

        auto rowBegin(const long &row = 0) -> row_iterator {
            return row_iterator(mGridPtr + (row * mGridWidth));
        }
        auto rowEnd(const long &row = 0) -> row_iterator {
            return row_iterator(mGridPtr + mViewWidth + (row * mGridWidth));
        }
        auto rowFront(const long &row = 0) -> Type & {
            return this->operator()(0, row);
        }
        auto rowBack(const long &row = 0) -> Type & {
            return this->operator()(mViewWidth - 1, row);
        }
        auto row(const long &column = 0, const long &row = 0) -> row_iterator {
            return row_iterator(mGridPtr + column + (row * mGridWidth));
        }

        auto rowBegin(const long &row = 0) const -> row_iterator { return this->rowBegin(row); }
        auto rowEnd(const long &row = 0) const -> row_iterator { return this->rowEnd(row); }
        auto row(const long &row = 0, const long &column = 0) const -> row_iterator { return this->row(row, column); }

        template<class index>
        auto row(const Vector2<index> &index2d) -> row_iterator { return row(index2d.x, index2d.y); }
        template<class index>
        auto row(const Vector2<index> &index2d) const -> row_iterator { return row(index2d.x, index2d.y); }
    };
}// namespace ATA

#endif//ATHENA_INCLUDE_GRID_VIEW_H
