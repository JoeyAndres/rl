/* 
 * File:   NDimensionalVector.h
 * Author: jandres
 *
 * Created on June 9, 2014, 8:38 AM
 */

#ifndef NDIMENSIONALVECTOR_H
#define	NDIMENSIONALVECTOR_H

#include <vector>
#include <cstdint>

/**
 * NDimensionalVector
 * 
 * For representing multidimensional array.
 *  */
template<size_t dim, typename D>
struct NDimensionalVector {
    typedef std::vector<typename NDimensionalVector<dim - 1, D>::nArray > nArray;    
};

template<typename D>
struct NDimensionalVector<0, D> {
    typedef D nArray;
};

#endif	/* NDIMENSIONALVECTOR_H */

