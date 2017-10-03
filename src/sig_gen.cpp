//
// Created by: Matt C. McCallum
// 4th June 2017
//
// Utility functions for generating signals - implementation.
//

// In Module includes
#include "sig_gen.h"

// Thirdparty includes
// None.

// Std Lib includes
#include <algorithm>
#include <ctime>
#include <math.h>
#include <assert.h>

namespace cupcake
{

namespace veclib
{

void seed_rand()
///
/// Helper function to seed the random variable maker.
///
{
    srand( static_cast< unsigned int >( std::time( 0 ) ) );
}

float make_random_number( float minVal, float maxVal )
///
/// Returns a random float type number greater than or equal to minVal and
/// less than or equal to maxVal.
///
/// @param minVal
///  The lower limit on the output range of the random number generator.
///
/// @param maxVal
///  The upper limit on the output range of the random number generator.
///
/// @return
///  The generated random number.
///
{
    assert( maxVal > minVal ); // Only generates numbers in a positive range.
    return ( static_cast< float >( rand() )/RAND_MAX*( maxVal - minVal ) + minVal );
}

void fill_vector_sine( std::vector< float >& output, float frequency, float phase, float mag )
///
/// Fills a vector with a sinusoid of the appropriate frequency, phase, and amplitude.
///
/// @param output
///  The vector to be filled with a sinusoid.
///
/// @param frequency
///  The frequency of the sinusoid in cycles per sample.
///
/// @param phase
///  The phase of the sinusoid in radians.
///
/// @param mag
///  The magnitude of the sinusoid.
///
{
    size_t n = 0;
    std::generate( output.begin(), output.end(), [&n, frequency, phase, mag]{
        float result = mag*cos( 2.0*M_PI*frequency*static_cast< float >( n ) + phase );
        ++n;
        return result;
    });
}
    
void fill_vector_chirp( std::vector< float >& output, float start_freq, float end_freq, float start_phase, float mag )
///
/// Fills a vector with a chirp signal that starts with a certain phase, frequency and magnitude,
/// and ends with a different frequency, the extrapolated phase, and the same magnitude.
/// The chirp frequency is a linear function of time.
///
/// @param output
///  A vector to be filled with the linear chirp signal.
///
/// @param start_freq
///  The frequency in cycles per sample at which to start the chirp signal at output index 0.
///
/// @param end_freq
///  The frequency in cycles per sample at which to end the chirp signal at output index output.size()-1.
///
/// @param start_phase
///  The sinusoid phase offset to apply at the first sample. All samples thereafter have a phase
///  determined by the progression of the chirp.
///
/// @param mag
///  The magnitude of the chirp signal at all samples.
///
{
    float freq_per_sample = ( end_freq - start_freq )/static_cast< float >( output.size() );
    size_t n = 0;
    std::generate( output.begin(), output.end(), [&n, start_freq, freq_per_sample, start_phase, mag]{
        float samp = static_cast< float >( n );
        float result = mag*cos( 2.0*M_PI*( start_freq + samp*freq_per_sample )*samp + start_phase );
        ++n;
        return result;
    });
}
    
void hamming( std::vector< float >& window_output )
///
/// Fills a vector with a Hamming window.
/// This window is "periodic" in the sense that it is circularly continuous - the
/// first and last elements in the window are not equal.
///
/// @param window_output
///  The vector to be filled with a Hamming window.
///
{
    size_t n = 0;
    float N = static_cast< float >( window_output.size() );
    std::generate( window_output.begin(), window_output.end(),
        [&n, N]
        {
            float result = 0.54 - 0.46*cos( 2.0*M_PI*static_cast< float >( n )/N );
            ++n;
            return result;
        }
    );
}
    
void linspace( float start, float finish, std::vector< float >& output )
///
/// Creates a vector of linearly spaced values between start and finish (inclusive).
///
/// @param start
///  The value of output at index 0.
///
/// @param finish
///  The value of output at index output.size()-1.
///
/// @param output
///  A vector to be filled with linearly spaced vaues between start and finish.
///  The size of this vector is unchanged by this operation.
///
{
    float increment = ( finish - start )/static_cast<float>( output.size() - 1 );
    size_t n = 0;
    std::generate( output.begin(), output.end(),
        [start, increment, &n]
        {
            return start + (n++)*increment;
        });
}

} // namespace veclib

} // namespace cupcake