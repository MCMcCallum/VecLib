//
// Created by: Matt C. McCallum
// 4th June 2017
//
// Utility functions for vectorised operations in C++.
//

#ifndef CUPCAKE_VEC_LIB_VECTOR_FUNCTIONS_H
#define CUPCAKE_VEC_LIB_VECTOR_FUNCTIONS_H

// In module includes
// None.

// Thirdparty includes
// None.

// Std Lib includes
#include <stdlib.h>

namespace cupcake
{

namespace veclib
{
    
///
/// Elementwise vector operations.
///
void vec_mult_const_in_place( float* input1, float multiplier, size_t length );
    
void vec_mult( const float* input1, const float* input2, float* output, size_t length );
    
void vec_mult_in_place( const float* input1, float* input2, size_t length );
    
void vec_add_constant( float* input1, float constant, size_t length );
    
void vec_add_in_place( const float* input1, float* input2_output, size_t length );
    
void vec_sub_constant( float* input1, float constant, size_t length );
    
void vec_sub( const float* input1, const float* input2, float* output, size_t length );
    
void vec_sub_in_place( float* input1, const float* input2, size_t length );
    
void vec_negative_halfwave_rectify( float* input, size_t length );
    
void vec_zero_magnitudes_greater_than_abs( float* input, float threshold, size_t length );

void vec_zero_values_less_than( float* input, float threshold, size_t length );
    
void vec_fractional_part( const float* input, float* output, size_t length );
    
///
/// Vector intialization functions
///
void vec_zero( float* vec, size_t length );
    
void vec_copy( const float* vec_source, float* vec_dest, size_t length );

} // namespace veclib

} // namespace cupcake

#endif // CUPCAKE_VEC_LIB_VECTOR_FUNCTIONS_H
