//
// Created by: Matt C. McCallum
// 4th June 2017
//
// Utility functions for generating signals.
//

#ifndef CUPCAKE_VEC_LIB_SIG_GEN_H
#define CUPCAKE_VEC_LIB_SIG_GEN_H

// In module includes
// None.

// Thirdparty includes
// None.

// Std Lib includes
#include <vector>
#include <cmath>

namespace cupcake
{

namespace veclib
{

void seed_rand();

float make_random_number( float minVal, float maxVal );
    
void fill_vector_sine( std::vector<float>& output, float frequency, float phase, float mag );
    
void fill_vector_chirp( std::vector< float >& output, float start_freq, float end_freq, float start_phase, float mag );
    
void hamming( std::vector<float>& window_output );
    
void linspace( float start, float finish, std::vector<float>& output );

} // namespace veclib

} // namespace cupcake

#endif // CUPCAKE_VEC_LIB_SIG_GEN_H
