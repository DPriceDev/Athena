//
// Created by David Price on 23/05/2020.
//

#ifndef ATHENA_ATHENA_FUNCTIONS_H
#define ATHENA_ATHENA_FUNCTIONS_H

namespace ATA {

    template<class InputIterator, class OutputIterator, class UnaryOperator,
             class UnaryPredicate>
    OutputIterator transform_if(InputIterator first,
                                InputIterator last,
                                OutputIterator result,
                                UnaryOperator operation,
                                UnaryPredicate predicate) {
        for(; first != last; ++first) {
            if (predicate(*first)) {
                *result = operation(*first);
                ++result;
            }
        }
        return result;
    }

    template<class InputIterator1, class InputIterator2, class OutputIterator,
             class BinaryOperator, class BinaryPredicate>
    OutputIterator transform_if(InputIterator1 first1,
                                InputIterator1 last1,
                                InputIterator2 first2,
                                OutputIterator result,
                                BinaryOperator operation,
                                BinaryPredicate predicate) {

        for(; first1 != last1; ++first1, ++first2) {
            if (predicate(*first1, *first2)) {
                *result = operation(*first1, *first2);
                ++result;
            }
        }
        return result;
    }
}// namespace ATA

#endif//ATHENA_ATHENA_FUNCTIONS_H
