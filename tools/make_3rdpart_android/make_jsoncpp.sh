echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make JSONCPP                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}


jsoncpp_compile() {
    ARCH=$1
    LIB_DIR="${BASE_LIB_DIR}_${ARCH}"
    INSTALL_DIR=jsoncpp_install

    if [ -d ${basepath}/${LIB_DIR}/${INSTALL_DIR} ];then
        echo ""
        echo "*************************************"
        echo "         jsoncpp ${ARCH} exist       "
        echo "*************************************"
        echo ""
        return
    fi

    cd ${basepath}/Eyer3rdpart/

    cp -r jsoncpp-1.9.4 jsoncpp-1.9.4_android_${ARCH}

    chmod -R 777 jsoncpp-1.9.4_android_${ARCH}

    cd ${basepath}/Eyer3rdpart/jsoncpp-1.9.4_android_${ARCH}/

    if [ -d ./${INSTALL_DIR} ];then
        rm -r ${INSTALL_DIR}
    fi
    
    if [ -d ./jsoncpp_build ];then
        rm -r jsoncpp_build
    fi
    mkdir jsoncpp_build
    cd jsoncpp_build

    cmake ../ \
    -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=${ARCH} \
    -DCMAKE_BUILD_TYPE=Release \
    -DANDROID_NATIVE_API_LEVEL=21 \
    -DCMAKE_INSTALL_PREFIX=../jsoncpp_install \
    -DJSONCPP_WITH_TESTS=OFF

    make
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

    cp -r Eyer3rdpart/jsoncpp-1.9.4_android_${ARCH}/${INSTALL_DIR} ${LIB_DIR}/${INSTALL_DIR}
}

jsoncpp_compile armeabi-v7a
jsoncpp_compile arm64-v8a
jsoncpp_compile x86
jsoncpp_compile x86_64