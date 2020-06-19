//
// Created by urban on 15/06/2020.
//

#ifndef HESTIA_ROGUELIKE_RANGE_H
#define HESTIA_ROGUELIKE_RANGE_H

namespace ATA {
    template<class Type>
    class Range {
        Type mMaximum;
        Type mMinimum;

    public:
        Range(const Type &minimum, const Type &maximum) : mMinimum(minimum), mMaximum(maximum) {}

        template<class ValueType>
        bool inRange(const ValueType &value) const {
            return (value - mMaximum) * (value - mMinimum) <= 0;
        }
    };
}

#endif//HESTIA_ROGUELIKE_RANGE_H
