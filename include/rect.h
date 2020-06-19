//
// Created by David Price on 16/05/2020.
//

#ifndef HESTIA_ROGUELIKE_DEPENDS_HGE_MATHS_RECT_H
#define HESTIA_ROGUELIKE_DEPENDS_HGE_MATHS_RECT_H

#include "vector.h"

namespace ATA {

    /**
     * Rect Templated Class
     */
    template<class Type>
    class Rect {
        Vector2<Type> mPosition;
        Vector2<Type> mSize;

    public:
        Rect(Vector2<Type> position, Vector2<Type> size) : mPosition(position), mSize(size) {}
        Rect(Type positionX, Type positionY, Type sizeX, Type sizeY)
            : mPosition(Vector2<Type>{positionX, positionY}), mSize(Vector2<Type>{sizeX, sizeY}) {}
        Rect(Type sizeX, Type sizeY) : mPosition(Vector2<Type>()), mSize(Vector2<Type>{sizeX, sizeY}) {}


        Vector2<Type> position() {
            return mPosition;
        }

        Vector2<Type> size() {
            return mSize;
        }

        [[nodiscard]] Vector2<Type> bottomLeft() const {
            return mPosition;
        }

        [[nodiscard]] Vector2<Type> bottomRight() const {
            return {mPosition.x + mSize.x, mPosition.y};
        }

        [[nodiscard]] Vector2<Type> topLeft() const {
            return {mPosition.x, mPosition.y + mSize.y};
        }

        [[nodiscard]] Vector2<Type> topRight() const {
            return {mPosition.x + mSize.x, mPosition.y + mSize.y};
        }

        [[nodiscard]] std::array<Vector2<Type>, 4> vertices() const {
            return std::array<Vector2<Type>, 4>{
                    topLeft(), topRight(), bottomRight(), bottomLeft()};
        }

        [[nodiscard]] bool isOverlapping(const Rect &other) const {
            if (this->topLeft().x >= other.bottomRight().x
                || other.topLeft().x >= this->bottomRight().x) {
                return false;
            }

            return !(this->topLeft().y <= other.bottomRight().y
                     || other.topLeft().y <= this->bottomRight().y);
        }

        [[nodiscard]] Vector2<double> midpoint() const {
            return Vector2<double>(mPosition.x + (mSize.x / 2), mPosition.y + (mSize.y / 2));
        }

        [[nodiscard]] double area() const {
            return mSize.x * mSize.y;
        }
    };

}// namespace ATA

#endif//HESTIA_ROGUELIKE_DEPENDS_HGE_INCLUDE_MATHS_RECT_H
