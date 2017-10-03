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
        './',
      ],

      'sources': 
      [
        'FFT.h',
        'src/FFT.cpp',
        'sig_gen.h',
        'src/sig_gen.cpp',
        'vector_functions.h',
        'src/vector_functions.cpp',
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