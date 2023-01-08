echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make EyerLib                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ ! -n "$NDK" ]; then
    echo "Please set NDK first"
    echo "export NDK=...."
    exit;
fi

if [ -d ./EyerLib ];then 
   rm -rf EyerLib
fi

git clone https://gitee.com/redknot/EyerLib

export BASE_LIB_DIR=Lib_android

eyerlib_compile() {
    ARCH=$1
    LIB_DIR="${BASE_LIB_DIR}_${ARCH}"
    INSTALL_DIR=EyerLib_install

    cd ${basepath}/EyerLib/src

    if [ -d ./build_${ARCH} ];then 
        rm -rf build_${ARCH}
    fi

    mkdir build_${ARCH}

    cd build_${ARCH}

    cmake ../ \
    -DGLRender=ON \
    -DGL_MESA=OFF \
    -DEyerG=OFF \
    -DEyerFrontEngine=OFF \
    -DEyerFontEngine=OFF \
    -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=${ARCH} \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_NATIVE_API_LEVEL=21 \
    -DCMAKE_INSTALL_PREFIX=../EyerLib_install_${ARCH}

    make clean
    make -j8
    make install



    cd ${basepath}

    if [ ! -d ./${LIB_DIR} ];then
        mkdir ${LIB_DIR}
    fi

    cd ${basepath}/${LIB_DIR}

    if [ -d ./${INSTALL_DIR} ];then
        rm -r ${INSTALL_DIR}
    fi

    cd ${basepath}

    cp -r ${basepath}/EyerLib/src/EyerLib_install_${ARCH} ${LIB_DIR}/${INSTALL_DIR}
}

eyerlib_compile armeabi-v7a
eyerlib_compile arm64-v8a
eyerlib_compile x86
eyerlib_compile x86_64