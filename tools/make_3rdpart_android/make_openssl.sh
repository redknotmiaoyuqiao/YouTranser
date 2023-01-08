echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make OpenSSL                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

openssl_compile() {
    ARCH=$1
    LIB_DIR="${BASE_LIB_DIR}_${ARCH}"
    INSTALL_DIR=openssl_install

    if [ -d ${basepath}/${LIB_DIR}/${INSTALL_DIR} ];then
        echo "${basepath}/${LIB_DIR}/${INSTALL_DIR}"
        echo ""
        echo "*************************************"
        echo "         openssl ${ARCH} exist       "
        echo "*************************************"
        echo ""
        return
    fi

    cd ${basepath}/Eyer3rdpart/

    cp -r openssl-1.1.1k openssl-1.1.1k_android_${ARCH}

    chmod -R 777 openssl-1.1.1k_android_${ARCH}

    cd ${basepath}/Eyer3rdpart/openssl-1.1.1k_android_${ARCH}/

    if [ -d ./${INSTALL_DIR} ];then
        rm -r ${INSTALL_DIR}
    fi

    # ./config --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install -fPIC no-shared
    # ./Configure android-arm64 -D__ANDROID_API__=30 --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install
    # ./Configure android-x86 -D__ANDROID_API__=30 --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install
    # ./Configure android-x86_64 -D__ANDROID_API__=30 --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install
    echo ""
    echo ""
    
    # ./Configure --help

    echo ""
    echo ""

    if [ ${ARCH} == "armeabi-v7a" ];then 
        export OPENSSL_ARCH="android-arm"
    fi

    if [ ${ARCH} == "arm64-v8a" ];then 
        export OPENSSL_ARCH="android-arm64"
    fi

    if [ ${ARCH} == "x86" ];then 
        export OPENSSL_ARCH="android-x86 no-asm"
    fi

    if [ ${ARCH} == "x86_64" ];then 
        export OPENSSL_ARCH="android-x86_64 no-asm"
    fi

    echo "==============================="
    echo ${OPENSSL_ARCH}

    CC=clang

    ./Configure \
    no-shared \
    --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k_android_${ARCH}/${INSTALL_DIR} \
    ${OPENSSL_ARCH} \
    -D__ANDROID_API__=21

    make clean
    make -j4
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

    cp -r Eyer3rdpart/openssl-1.1.1k_android_${ARCH}/${INSTALL_DIR} ${LIB_DIR}/${INSTALL_DIR}
}

openssl_compile armeabi-v7a
openssl_compile arm64-v8a
openssl_compile x86
openssl_compile x86_64