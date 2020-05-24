//
// Created by David Price on 23/05/2020.
//

#ifndef ATHENA_ATHENA_FUNCTIONS_H
#define ATHENA_ATHENA_FUNCTIONS_H

namespace ATA {

    /**
     * Transform If
     * Transforms the range of input iterators from first to last; however, it
     * will only transform an input iterator if it meets the specific predicate.
     *
     * @tparam InputIterator
     * @tparam OutputIterator
     * @tparam UnaryOperator
     * @tparam UnaryPredicate
     * @param first
     * @param last
     * @param result
     * @param operation
     * @param predicate
     * @return
     */
    template<class InputIterator, class OutputIterator, class UnaryOperator, class UnaryPredicate>
    OutputIterator transform_if (InputIterator first, InputIterator last,
                                 OutputIterator result, UnaryOperator operation,
                                 UnaryPredicate predicate) {
        while(first != last) {
            if(predicate(*first)) {
                *result = operation(*first);
                ++result;
            }
            ++first;
        }
        return result;
    }
}

#endif //ATHENA_ATHENA_FUNCTIONS_H
