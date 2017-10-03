VecLib
======

A C++ library for wrapping up vectorized data operations in an easier to use C++ interface.

At this stage the only library supported [IPP](https://software.intel.com/en-us/intel-ipp/details), although, having this functionality wrapped up like this allows easy swapping out of vector libraries and keeps the code clean of the often complex function calls in vectorized libraries.

Dependencies
------------

This code depends on:
 * [GYP](https://gyp.gsrc.io/)
 * [IPP](https://software.intel.com/en-us/intel-ipp/details)

IPP can be installed from [here](https://software.intel.com/en-us/intel-ipp/details).

Install
-------

This codebase is intended to be linked into a project that uses [GYP](https://gyp.gsrc.io/) project generation. The code can simply be added to a project by inserting:

```
'includes': 
    [
      '<(veclib_dir)/VecLib.gypi',
    ],
```

into the parent project's .gyp file. Here veclib_dir is the directory that this file resides in.

Due to the IPP dependency, this library must be added to a <(veclib_dir)/thirdparty directory. Information on installing this library can be found [here](https://software.intel.com/en-us/articles/free-ipp). 

For convenience on OSX a script `pull_thirdparty_osx.sh` is provided to pull this library in if it is installed on your machine.