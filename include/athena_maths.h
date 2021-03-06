//
// Created by David Price on 10/06/2020.
//

#ifndef ATHENA_ATHENA_MATHS_H
#define ATHENA_ATHENA_MATHS_H

#include <optional>

#include "vector.h"

namespace ATA {

//    template<class Type>
//    auto lineIntersection(Vector2<Type> LineStartA, Vector2<Type> LineFinishA,
//                          Vector2<Type> LineStartB, Vector2<Type> LineFinishB ) -> std::optional<Vector2<Type>> {
//
//        // Line AB represented as a1x + b1y = c1
//        double a1 = LineFinishA.y - LineStartA.y;
//        double b1 = LineStartA.x - LineFinishA.x;
//        double c1 = a1*(LineStartA.x) + b1*(LineStartA.y);
//
//        // Line CD represented as a2x + b2y = c2
//        double a2 = LineFinishB.y - LineStartB.y;
//        double b2 = LineStartB.x - LineFinishB.x;
//        double c2 = a1*(LineStartB.x) + b1*(LineStartB.y);
//
//        double determinant = a1*b2 - a2*b1;
//
//        if (determinant == 0)
//        {
//            return Vector2<Type>(0, 0);
//        }
//        else
//        {
//            Type x = static_cast<Type>((b2*c1 - b1*c2) / determinant);
//            Type y = static_cast<Type>((a1*c2 - a2*c1) / determinant);
//            return Vector2<Type>(x, y);
//        }
//    }
}

#endif//ATHENA_ATHENA_MATHS_H
