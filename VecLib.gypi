  {

    'variables': 
    {
      'veclib_base_dir': '.',
      'veclib_thirdparty_lib_dir': '<(base_dir)/thirdparty/lib/',
      'veclib_thirdparty_include_dir': '<(base_dir)/thirdparty/include/',
    },

    'include_dirs': 
    [
      '<(veclib_thirdparty_include_dir)',
    ],

    'target_defaults' : 
    {
      'include_dirs': 
      [
        './src',
      ],

      'sources': 
      [
        'src/FFT.cpp',
        'src/FFT.h',
        'src/sig_gen.cpp',
        'src/sig_gen.h',
        'src/vector_functions.cpp',
        'src/vector_functions.h',
      ],

      'link_settings': 
      {
        'libraries': [
          '<(veclib_thirdparty_lib_dir)/libippcore.a',
          '<(veclib_thirdparty_lib_dir)/libipps.a',
          '<(veclib_thirdparty_lib_dir)/libippsvm.a',
        ],
      },
    },
  }