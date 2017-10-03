#!/bin/bash
#
# Created by: Matt C. McCallum
# 2nd October 2017
#
# Pulls in dependencies for the VecLib project
#
# Dependencies covered here:
#   - IPP
#   - GYP
#

echo " "
echo "Installing Dependencies..."
echo " "

ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
pushd "${ROOT_DIR}"

    # Prepare thirdparty paths

    THIRDPARTY_DIR="${ROOT_DIR}"/thirdparty/
    LIB_DIR="${THIRDPARTY_DIR}/lib"
    INCLUDE_DIR="${THIRDPARTY_DIR}/include"
    mkdir -p "${LIB_DIR}"
    mkdir -p "${INCLUDE_DIR}"

    ###################################################
    #                      IPP                        #
    ###################################################

    echo " "
    echo "Installing IPP..."
    echo " "

    IPP_BASE_DIR="/opt/intel/ipp/"

    if [ ! -e "/opt/intel/ipp/include/ipp.h" ]; then
        echo "ERROR: Could not find IPP library."
        echo "This must be manually downloaded and installed."
        echo "Go here for more info: https://software.intel.com/en-us/articles/free-ipp"
        echo " "
    fi

    if [ ! -e "${LIB_DIR}/libippsmerged.a" ]; then
        cp "${IPP_BASE_DIR}/lib/libippcore.a" "${LIB_DIR}/libippcore.a"
        cp "${IPP_BASE_DIR}/lib/libipps.a" "${LIB_DIR}/libipps.a"
        cp "${IPP_BASE_DIR}/lib/libippvm.a" "${LIB_DIR}/libippvm.a"

        mkdir "${INCLUDE_DIR}/ipp/"
        cp "${IPP_BASE_DIR}/include/"*.h "${INCLUDE_DIR}/ipp/"
    fi

    ###################################################
    #                      GYP                        #
    ###################################################

    echo " "
    echo "Installing GYP..."
    echo " "

    if [[ $( which gyp ) == "" ]]; then

        GYP_BUILD_DIR="${THIRDPARTY_DIR}/gyp/"
        mkdir -p "${GYP_BUILD_DIR}"
        pushd "${GYP_BUILD_DIR}"

            git clone https://chromium.googlesource.com/external/gyp.git
            GYP_LIB_DIR="./gyp"
            pushd ${GYP_LIB_DIR}
                echo " "
                echo "Going to need your computer password to install GYP..."
                echo " "
                sudo python setup.py install 
            popd

        popd

    fi
    
popd



