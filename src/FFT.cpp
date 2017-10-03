//
// Created by: Matt C. McCallum
// 4th June 2017
//
// Utility functions for FFT operations in C++ - implementation.
//

// In Module includes
#include "FFT.h"

// Thirdparty includes
#include "ipp/ippcore.h"
#include "ipp/ippvm.h"

// Std Lib includes
#include <assert.h>

namespace cupcake
{

namespace veclib
{

void make_FFT( size_t FFTSize, FFTConfig& config )
///
/// Function for initialising an FFT object to be later used as an FFT configuration.
///
/// @param FFTSize
///  The length of the FFT output - this must be a power of 2.
///
/// @param FFTConfig
///  An uninitialised FFTConfig object that will be filled out by this function.
///
{
    // Set FFT sizes (Find what power of 2 is greater or equal to FFTSize for order.)
    config.FFTSize = FFTSize;
    config.FFTSizeLog2 = 0;
    config.FFTOutputSize = FFTSize/2 + 1;
    while( FFTSize >>= 1 )
    {
        ++config.FFTSizeLog2;
        assert( ( ( FFTSize & 1 )==0 ) || FFTSize==1 ); // FFTSize must be a power of 2.
    }
    
    // Set the FFTSpec to Null.
    config.FFTSpec = NULL;
    
    // Get memory size allocations for this type of FFT.
    int FFT_specification_buffer_size;
    int FFT_init_buffer_size;
    int FFT_working_buffer_size;
    
    IppStatus err = ippsFFTGetSize_R_32f( static_cast< int >( config.FFTSizeLog2 ),
                                          IPP_FFT_DIV_INV_BY_N,
                                          ippAlgHintNone,
                                          &FFT_specification_buffer_size,
                                          &FFT_init_buffer_size,
                                          &FFT_working_buffer_size );
    
    assert( err==ippStsNoErr ); // Error getting FFT structure sizes.
    
    // Allocate memories
    Ipp8u* init_buffer;
    if( FFT_init_buffer_size )
        init_buffer = ippsMalloc_8u( FFT_init_buffer_size );
    else
        init_buffer = NULL;
    
    if( FFT_specification_buffer_size )
        config.FFTSpecBuffer = ippsMalloc_8u( FFT_specification_buffer_size );
    else
        config.FFTSpecBuffer = NULL;
    
    if( FFT_working_buffer_size )
        config.FFTWorkingBuffer = ippsMalloc_8u( FFT_working_buffer_size );
    else
        config.FFTWorkingBuffer = NULL;
    
    // Initialise the FFT specification structures.
    err = ippsFFTInit_R_32f( &(config.FFTSpec),
                            static_cast< int >( config.FFTSizeLog2 ),
                            IPP_FFT_DIV_INV_BY_N,
                            ippAlgHintNone,
                            config.FFTSpecBuffer,
                            init_buffer );
    
    // Free memory used for initialisation
    ippsFree( init_buffer );
    
    // Check for errors
    assert( err==ippStsNoErr ); // Error initialising FFT specification.
    
}

void destroy_FFT( FFTConfig& config )
///
/// Destroys an FFT configuration and all associated memory allocations.
///
/// @param config
///  The FFTConfig object to be destroyed.
///
{
    
    /// @todo [matthew.mccallum 05.25.17] We may need to free the config.FFTSpec memory here
    ///                                   although the function to do this seems to have
    ///                                   disappeared somewhere between IPP 6.1.1 and IPP 8.2...
    ippsFree( config.FFTSpecBuffer );
    ippsFree( config.FFTWorkingBuffer );
    
}

void FFT_not_in_place( const float* input, std::complex< float >* output, FFTConfig& config )
///
/// Performs an FFT from an input vector to an output. The length of the input FFT is
/// assumed equal to the length of the FFT output (specified in FFTConfig), and so any
/// zero padding on the input must be performed before this function call.
/// The output vector will be of length config.FFTSize/2 + 1, where the first and last
/// values of the output array are real values corresponding to DC and Nyquist respectively.
/// This operation cannot be formed in place.
///
/// @param input
///  A pointer to the first element in a contiguous input signal vector.
///
/// @param output
///  The pointer to the first element in a contiguous output signal vector.
///
/// @param config
///  The FFT configuration specifying the FFT length and locations of pre-allocated memory
///  for the FFT operation.
///
{
    
    IppStatus err = ippsFFTFwd_RToCCS_32f( input, reinterpret_cast< Ipp32f* >( output ), config.FFTSpec, config.FFTWorkingBuffer );
    
    assert( err==ippStsNoErr ); // Error in forward FFT operation

}

void IFFT_not_in_place( const std::complex< float >* input, float* output, FFTConfig& config )
///
/// Perform the inverse FFT operation on a contiguous set of complex values. The length of this FFT
/// is specified in config and should be twice the (complex) length of the input minus 2. It is expected
/// that there will be the correct number of elements in input.
/// The output should be of the FFTSize length specified in config.
/// The first and last values in the input should be purely real and correspond to DC and Nyquist respectively.
///
/// @param input
///  A pointer to the first element in a contiguous input signal vector.
///
/// @param output
///  The pointer to the first element in a contiguous output signal vector.
///
/// @param config
///  The IFFT configuration specifying the IFFT length and locations of pre-allocated memory
///  for the IFFT operation.
///
{
    
    IppStatus err = ippsFFTInv_CCSToR_32f( reinterpret_cast< const Ipp32f* >( input ), output, config.FFTSpec, config.FFTWorkingBuffer );
    
    assert( err==ippStsNoErr ); // Error in inverse FFT operation.
    
}
    
void spectral_magnitude( const std::complex< float >* input, float* output, size_t length )
///
/// Computes the magnitude of all complex values in a given vector.
///
/// @param input
///  A pointer to the first element of the complex vector to get the magnitude of.
///
/// @param ouput
///  A pointer to a vector of half the memory size of input (same number of elements),
///  in which to place the magnitude of each value in input.
///
/// @param length
///  The number of elements in input and output.
///
{
    
    IppStatus err =  ippsMagnitude_32fc( reinterpret_cast< const Ipp32fc* >( input ),
                                         static_cast< Ipp32f* >( output ),
                                         static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error calculating magnitude
    
}
    
void phase_spectra( const std::complex< float >* input, float* output, size_t length )
///
/// Get the argument of all complex values in the input vector. These values will
/// be in the range (-pi,pi].
///
/// @param input
///  A pointer to the first complex valued element to get the argument of.
///
/// @param output
///  A pointer to the first element in the output (half the size of the input vector).
///
/// @param length
///  The number of elements in input and output.
///
{
    
    IppStatus err = ippsPhase_32fc( reinterpret_cast< const Ipp32fc* >( input ),
                                    static_cast< Ipp32f* >( output ),
                                    static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error calculating phase
    
}
    
void cart_to_polar( const std::complex< float >* input, float* magnitude, float* phase, size_t length )
///
/// Get the magnitude and arguments of all elements in the input vector.
///
/// @param input
///  A pointer to the first element in a vector of complex elements of which to get the magnitude
///  and phase of each.
///
/// @param magnitude
///  A pointer to the location of the output vector for the magnitude of each element in input.
///
/// @param phase
///  A pointer to the location of the output vector for the phase of each element in input.
///
/// @param length
///  The number of elements in input, magnitude and phase.
///
{

    IppStatus err = ippsCartToPolar_32fc( reinterpret_cast< const Ipp32fc* >( input ),
                                          static_cast< Ipp32f* >( magnitude ),
                                          static_cast< Ipp32f* >( phase ),
                                          static_cast< int >( length ) );
    
    assert( err==ippStsNoErr ); // Error converting coordinates
    
}

} // namespace veclib

} // namespace cupcake
