//
// Created by: Matt C. McCallum
// 4th June 2017
//
// Utility functions for FFT operations in C++ - implementation.
//

#ifndef CUPCAKE_VEC_LIB_FFT_H
#define CUPCAKE_VEC_LIB_FFT_H

// In Module includes
// None.

// Thirdparty includes
#include "ipp/ipps.h"

// Std Lib includes
#include <complex>
#include <stdlib.h>

namespace cupcake
{

namespace veclib
{

///
/// FFT Configuration
///
struct FFTConfig
{
    size_t FFTSize;             // -> The theoretical length of the FFT operation.
    size_t FFTSizeLog2;         // -> Log base 2 of the theoretical length of the FFT operation.
    size_t FFTOutputSize;       // -> The length of the array of complex floats at the output of the FFT.
    IppsFFTSpec_R_32f* FFTSpec;
    Ipp8u* FFTSpecBuffer;
    Ipp8u* FFTWorkingBuffer;
};
    
static constexpr inline size_t get_output_FFT_size( size_t FFTSize ) { return FFTSize/2 + 1; };
    
void make_FFT( size_t FFTSize, FFTConfig& config );

void destroy_FFT( FFTConfig& config );

void FFT_not_in_place( const float* input, std::complex< float >* output, FFTConfig& config );

void IFFT_not_in_place( const std::complex< float >* input, float* output, FFTConfig& config );
    
///
/// Operations on the FFT
///
void spectral_magnitude( const std::complex< float >* input, float* output, size_t length );
    
void phase_spectra( const std::complex< float >* input, float* output, size_t length );
    
void cart_to_polar( const std::complex< float >* input, float* magnitude, float* phase, size_t length );

} // namespace veclib
    
} // namespace cupcake

#endif // CUPCAKE_VEC_LIB_FFT_H
