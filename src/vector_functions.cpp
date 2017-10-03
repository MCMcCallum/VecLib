//
// Created by: Matt C. McCallum
// 4th June 2017
//
// Utility functions for vectorised operations in C++ - implementation.
//

// In Module includes
#include "vector_functions.h"

// Thirdparty includes
#include "ipp/ipps.h"
#include "ipp/ippvm.h"

// Std Lib includes
#include <assert.h>

namespace cupcake
{

namespace veclib
{
    
void vec_mult_const_in_place( float* input1, float multiplier, size_t length )
///
/// Multiplies each element in input of length by a constant multiplier.
///
/// @param input1
///  Pointer to the first element in a contiguous block of memory containing the vector to be multiplied.
///
/// @param multiplier
///  The constant by which to multiply ever element in the input.
///
/// @param length
///  The number of elements in the input vector.
///
{
    
    IppStatus err = ippsMulC_32f_I( static_cast< Ipp32f >( multiplier ),
                                    static_cast< Ipp32f* >( input1 ),
                                    static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error multiplying by constant
    
}

void vec_mult( const float* input1, const float* input2, float* output, size_t length )
///
/// Performs element-wise multiplication of two vectors into an output vector.
///
/// @param input1
///  The first factor in multiplication.
///
/// @param input2
///  The second factor in multiplication.
///
/// @param output
///  A vector to be filled with the element-wise product of input1 and input2.
///
/// @param length
///  The length of all vectors - input1, input2 and output.
///
{
    
    IppStatus err = ippsMul_32f( static_cast< const Ipp32f* >( input1 ),
                                 static_cast< const Ipp32f* >( input2 ),
                                 static_cast< Ipp32f* >( output ),
                                 static_cast< Ipp32s >( length ) );
    
    assert( err==ippStsNoErr ); // Error multiplying vectors.
    
}
    
void vec_mult_in_place( const float* input1, float* input2, size_t length )
///
/// Performs element-wise multiplication of two vectors and leaves the output
/// in the second vector.
///
/// @param input1
///  The first factor in multiplication
///
/// @param input2
///  On input: The second factor in multiplication.
///  On output: The result of multiplication.
///
/// @param length
///  The number of elements in both input1 and input2.
///
{
 
    IppStatus err = ippsMul_32f_I( static_cast< const Ipp32f* >( input1 ),
                                   static_cast< Ipp32f* >( input2 ),
                                   static_cast< Ipp32s >( length ) );
    
    assert( err==ippStsNoErr ); // Error multiplying vectors.
    
}
    
void vec_add_constant( float* input1, float constant, size_t length )
///
/// Adds a single constant value to all elements in the input vector.
///
/// @param input1
///  A pointer to the first element of a vector in which all elements
///  are to be multiplied by a constant.
///
/// @param constant
///  The value by which to multiply every element in the input vector.
///
/// @param length
///  The numebr of elements in the input vector.
///
{
    
    IppStatus err = ippsAddC_32f_I( static_cast< Ipp32f >( constant ),
                                    static_cast< Ipp32f* >( input1 ),
                                    static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error adding constant.
    
}

void vec_add_in_place( const float* input1, float* input2_output, size_t length )
///
/// Adds two vectors element-wise and leaves the output in the second vector argument.
///
/// @param input1
///  Pointer to the first element in a vector to be added to the second element-wise. This vector remains unmodified.
///
/// @param input2_output
///  Pointer to the first element in a second vector to be added to the first element-wise. This is replaced by the output.
///
/// @param length
///  The number of elements in both input vectors
///
{
   
    IppStatus err = ippsAdd_32f_I( static_cast< const Ipp32f* >( input1 ),
                                   static_cast< Ipp32f* >( input2_output ),
                                   static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error adding vectors.
    
}
    
void vec_sub_constant( float* input, float constant, size_t length )
///
/// Subtract a constant from every element in the input vector.
///
/// @param input
///  A pointer to the first element of a contiguous block of memory containing the vector to which a constant is
///  to be subtracted from each element.
///
/// @param constant
///  The number to subtract from each value in the input vector.
///
/// @param length
///  The number of elements in the input vector.
///
{
    IppStatus err = ippsSubC_32f_I( static_cast< Ipp32f >( constant ),
                                    static_cast< Ipp32f* >( input ),
                                    static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error adding constant.
}
    
void vec_sub( const float* input1, const float* input2, float* output, size_t length )
///
/// Subtract one input vector from another elmentwise. Specifically:
///
///     output = input1 - input2
///
/// @param input1
///  A pointer to the first element in the vector for which the second input is to be subtracted
///  from element-wise.
///
/// @param input2
///  A pointer to the first element in the vector that is to be subtracted from the first input.
///
/// @param output
///  The result of the element-wise subtraction of input2 from input1.
///
/// @param length
///  The number of elements in all inputs and in the output.
///
{
    
    IppStatus err = ippsSub_32f( static_cast< const Ipp32f* >( input2 ),
                                 static_cast< const Ipp32f* >( input1 ),
                                 static_cast< Ipp32f* >( output ),
                                 static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error subtracting vectors.
    
}
    
void vec_sub_in_place( float* input1, const float* input2, size_t length )
///
/// Subtract one input vector from another elmentwise, and leave the result in the first vector. Specifically:
///
///     input1 = input1 - input2
///
/// @param input1
///  On input: A pointer to the first element in the vector for which the second input is to be subtracted
///  from element-wise.
///  On output: The result of input1 - input2; element-wise.
///
/// @param input2
///  A pointer to the first element of a vector to be subtracted from input1, element-wise.
///
/// @param length
///  The number of elements in input1 and input2.
///
{
    
    IppStatus err = ippsSub_32f_I( static_cast< const Ipp32f* >( input2 ),
                                   static_cast< Ipp32f* >( input1 ),
                                   static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error subtracting vectors.
    
}
    
void vec_negative_halfwave_rectify( float* input, size_t length )
///
/// Sets all positive values of an input vector to 0.0;
///
/// @param input
///  The data to be half-wave rectified.
///
/// @param length
///  The number of elements in input1.
///
{
    
    IppStatus err = ippsThreshold_GT_32f_I( static_cast< Ipp32f* >( input ),
                                            static_cast< int >( length ),
                                            0.0 );
    
    assert( err==ippStsNoErr ); // Error limiting positive values
    
}
    
void vec_zero_magnitudes_greater_than_abs( float* input, float threshold, size_t length )
///
/// Sets all values in a vector with an amplitude greater than the given threshold to zero.
///
/// @param input
///  A pointer to the first element of a vector to be zeroed at values greater than a given
///  amplitude.
///
/// @param threshold
///  A positive amplitude threshold that defines which values in input1 are set to 0.0.
///
/// @param length
///  The number of elements in input1.
///
{
    
    assert( threshold>0.0 );
    
    IppStatus err = ippsThreshold_LTValGTVal_32f_I( static_cast< Ipp32f* >( input ),
                                                    static_cast< int >( length ),
                                                    static_cast< Ipp32f >( -threshold ),
                                                    0.0,
                                                    static_cast< Ipp32f >( threshold ),
                                                    0.0 );
    
    assert( err==ippStsNoErr ); // Error zeroing values
    
}
    
void vec_zero_values_less_than( float* input, float threshold, size_t length )
///
///
///
{
    
    IppStatus err = ippsThreshold_LTVal_32f_I( static_cast< Ipp32f* >( input ),
                                               static_cast< int >( length ),
                                               static_cast< Ipp32f >( threshold ),
                                               0.0 );
    
    assert( err==ippStsNoErr ); // Error zeroing values
    
}
    
void vec_fractional_part( const float* input, float* output, size_t length )
///
/// Take the fractional part of all elements in the input vector and place them in an output
/// vector. That is, all values in the output have an amplitude less than 1.
///
/// @param input
///  A pointer to the first element in the input vector to take the fractional part of.
///
/// @param output
///  A pointer to position in memory to which to write the fractional part of all elements in the
///  input vector.
///
/// @param length
///  The number of elements in the input/output vectors.
///
{
    
    IppStatus err = ippsFrac_32f( static_cast< const Ipp32f* >( input ),
                                  static_cast< Ipp32f* >( output ),
                                  static_cast< Ipp32s >( length ) );
    
    assert( err==ippStsNoErr ); // Error finding fractional part.
    
}
    
void vec_zero( float* vec, size_t length )
///
/// Sets all elements in a contiguous vector to 0.
///
/// @param vec
///  Pointer to the first element in a vector to be zeroed.
///
/// @param length
///  The number of elements in the input vector ot be zeroed.
///
{
    
    IppStatus err = ippsZero_32f( static_cast< Ipp32f* >( vec ), static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error zeroing vector.
    
}
    
void vec_copy( const float* vec_source, float* vec_dest, size_t length )
///
/// Copy from element-wise one vector to another.
///
/// @param vec_source
///  Pointer to the first element in a first vector to be copied into the second.
///
/// @param vec_dest
///  Pointer to the first element in a second vector to write each fo the elements of the first
///  vector into.
///
/// @param length
///  The number of elements to be copied from one vector to another.
///
{
    
    IppStatus err = ippsCopy_32f( static_cast< const Ipp32f* >( vec_source ),
                                  static_cast< Ipp32f* >( vec_dest ),
                                  static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error copying vector.
    
}
    
} // namespace veclib

} // namespace cupcake
