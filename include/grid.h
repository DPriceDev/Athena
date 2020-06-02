//
// Created by David Price on 24/05/2020.
//

#ifndef ATHENA_GRID_H
#define ATHENA_GRID_H

#include <algorithm>
#include <array>
#include <utility>
#include <vector>

#include "vector.h"

namespace ATA {

    /**
     *
     */
    struct GridParameters {
        long mOriginX, mOriginY;
        long mWidth, mHeight;

        GridParameters(const long &width, const long &height, const long &originX, const long &originY)
            : mOriginX(originX), mOriginY(originY), mWidth(width), mHeight(height) {}
    };

    /**
     *
     */
    struct GridBounds {
        GridBounds(const long &top, const long &right, const long &bottom, const long &left)
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

    private:
        std::array<long, 4> mBounds;
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

        /**
         *
         */
        class row_iterator {
            friend class Grid2D;
            Type *mGridPtr;
            explicit row_iterator(Type *gridPtr) : mGridPtr(gridPtr) {}

        public:
            Type *operator+(const long &offset) const { return mGridPtr + offset; }
            Type *operator-(const long &offset) const { return mGridPtr - offset; }
            Type *operator->() { return mGridPtr; }
            Type &operator*() { return *mGridPtr; }

            bool operator==(const row_iterator &other) const { return this->mGridPtr == other.mGridPtr; }
            bool operator!=(const row_iterator &other) const { return this->mGridPtr != other.mGridPtr; }

            auto operator++() -> row_iterator & {
                mGridPtr += 1;
                return *this;
            }

            auto operator++(int) -> row_iterator {
                auto it = *this;
                return ++it;
            }

            auto operator--() -> row_iterator & {
                mGridPtr -= 1;
                return *this;
            }

            auto operator--(int) -> row_iterator {
                auto it = *this;
                return --it;
            }
        };

        /**
         * Column Iterator
         */
        class column_iterator {
            friend class Grid2D;
            Type *mGridPtr;
            long mWidth;
            explicit column_iterator(Type *gridPtr, long width) : mGridPtr(gridPtr), mWidth(width) {}

        public:
            Type *operator+(const size_t &offset) const { return mGridPtr + (offset * mWidth); }
            Type *operator-(const size_t &offset) const { return mGridPtr - (offset * mWidth); }
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
         */

        Grid2D(const size_t &width, const size_t &height, const long &originX = 0L, const long &originY = 0L)
            : mOriginX(originX), mOriginY(originY),
              mWidth(static_cast<long>(width)), mHeight(static_cast<long>(height)),
              mBounds(mHeight + mOriginY, mOriginX + mWidth, originY, originX) {

            mGrid.resize(width * height);
        }

        /* todo: static assert the size is right? or fill empty spaces? */
        Grid2D(std::initializer_list<Type> list,
               const long &height,
               const long &originX = 0L,
               const long &originY = 0L)
            : mOriginX(originX),
              mOriginY(originY),
              mWidth(static_cast<long>(list.size()) / height),
              mHeight(height),
              mBounds(mHeight + mOriginY, mOriginX + mWidth, originY, originX) {
            mGrid.insert(mGrid.end(), list);
        }

        /* todo: static assert the size is right? or fill empty spaces? */
        /* todo: reverse row input?? */
        Grid2D(std::initializer_list<std::initializer_list<Type>> list, const long &originX = 0L, const long &originY = 0L);

        explicit Grid2D(const GridParameters &gridParameters)
            : mOriginX(gridParameters.mOriginX), mOriginY(gridParameters.mOriginY),
              mWidth(gridParameters.mWidth), mHeight(gridParameters.mHeight),
              mBounds({mOriginY + mHeight, mOriginX + mWidth, mOriginY, mOriginX}) {

            mGrid.resize(static_cast<size_t>(mWidth * mHeight));
        }

        /**
         * Access
         */

        auto operator()(const long &x, const long &y) -> Type & {
            auto yPosition = (y - mOriginY) * mWidth;
            auto xPosition = x - mOriginX;
            return mGrid[static_cast<size_t>(yPosition + xPosition)];
        }

        auto at(const long &x, const long &y) -> Type & {
            if (!isPointInGrid(x, y)) {
                throw std::out_of_range("2D grid");
            }
            return this->operator()(x, y);
        }

        auto at(const std::pair<const long, const long> &pair) -> Type & {
            return this->at(pair.first, pair.second);
        }

        template<class Index>
        auto at(const Vector2<Index> &index) -> Type & {
            return this->at(index.x, index.y);
        }

        /**
         * Iterators
         */

        auto begin() -> iterator { return mGrid.begin(); }
        auto begin() const -> const_iterator { return mGrid.begin(); }
        auto end() -> iterator { return mGrid.end(); }
        auto end() const -> const_iterator { return mGrid.begin(); }

        auto columnBegin(const long &column = 0) -> column_iterator {
            return column_iterator(mGrid.data() + column - mOriginX, mWidth);
        }
        auto columnEnd(const long &column = 0) -> column_iterator {
            return column_iterator(mGrid.data() + (mWidth * mHeight) + column - mOriginX, mWidth);
        }
        auto columnFront(const long &column = 0) -> Type & {
            return this->operator()(column, 0);
        }
        auto columnBack(const long &column = 0) -> Type & {
            return this->operator()(column, mHeight - 1);
        }
        auto column(const long &column = 0, const long &row = 0) -> column_iterator {
            return column_iterator(mGrid.data() + column - mOriginX + ((row - mOriginY) * mWidth), mWidth);
        }

        auto columnBegin(const long &column = 0) const -> column_iterator { return this->columnBegin(column); }
        auto columnEnd(const long &column = 0) const -> column_iterator { return this->columnEnd(column); }
        auto column(const long &column = 0, const long &row = 0) const -> column_iterator { return this->column(column, row); }

        template<class index>
        auto column(const Vector2<index> &index2d) -> column_iterator { return column(index2d.x, index2d.y); }
        template<class index>
        auto column(const Vector2<index> &index2d) const -> column_iterator { return column(index2d.x, index2d.y); }

        auto rowBegin(const long &row = 0) -> row_iterator {
            return row_iterator(mGrid.data() + ((row - mOriginY) * mWidth));
        }
        auto rowEnd(const long &row = 0) -> row_iterator {
            return row_iterator(mGrid.data() + mWidth + ((row - mOriginY) * mWidth));
        }
        auto rowFront(const long &row = 0) -> Type & {
            return this->operator()(0, row);
        }
        auto rowBack(const long &row = 0) -> Type & {
            return this->operator()(mWidth - 1, row);
        }
        auto row(const long &column = 0, const long &row = 0) -> row_iterator {
            return row_iterator(mGrid.data() + column - mOriginX + ((row - mOriginY) * mWidth));
        }

        auto rowBegin(const long &row = 0) const -> row_iterator { return this->rowBegin(row); }
        auto rowEnd(const long &row = 0) const -> row_iterator { return this->rowEnd(row); }
        auto row(const long &row = 0, const long &column = 0) const -> row_iterator { return this->row(row, column); }

        template<class index>
        auto row(const Vector2<index> &index2d) -> row_iterator { return row(index2d.x, index2d.y); }
        template<class index>
        auto row(const Vector2<index> &index2d) const -> row_iterator { return row(index2d.x, index2d.y); }

        /**
         * Parameters
         */

        auto data() -> Type * {
            return mGrid.data();
        }

        [[nodiscard]] auto getBounds() const -> const GridBounds & {
            return mBounds;
        }

        [[nodiscard]] auto isPointInGrid(const long &x, const long &y) const -> bool {
            return x >= mBounds.left()
                   && x <= mBounds.right() - 1
                   && y >= mBounds.bottom()
                   && y <= mBounds.top() - 1;
        }

        [[nodiscard]] auto size() const -> Vector2<long> {
            return Vector2<long>(mWidth, mHeight);
        }

        [[nodiscard]] auto origin() const -> Vector2<long> {
            return Vector2<long>(mOriginX, mOriginY);
        }

        [[nodiscard]] auto gridParameters() const -> GridParameters {
            return GridParameters(mWidth, mHeight, mOriginX, mOriginY);
        }
    };
    template<class Type>
    Grid2D<Type>::Grid2D(std::initializer_list<std::initializer_list<Type>> list, const long &originX, const long &originY)
        : mOriginX(originX), mOriginY(originY),
          mWidth(static_cast<long>(list.begin()->size())), mHeight(static_cast<long>(list.size())),
          mBounds(mHeight + mOriginY, mOriginX + mWidth, originY, originX) {

        for (const auto &rowList : list) {
            mGrid.insert(mGrid.end(), rowList);
        }
    }
}// namespace ATA

#endif//ATHENA_GRID_H
