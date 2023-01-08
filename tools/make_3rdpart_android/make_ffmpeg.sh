echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make FFMpeg                              ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

ffmpeg_compile() {
    ARCH=$1
    LIB_DIR="${BASE_LIB_DIR}_${ARCH}"
    INSTALL_DIR=ffmpeg_install

    if [ -d ${basepath}/${LIB_DIR}/${INSTALL_DIR} ];then
        echo ""
        echo "*************************************"
        echo "         ffmpeg ${ARCH} exist       "
        echo "*************************************"
        echo ""
        return
    fi


    cd ${basepath}/Eyer3rdpart/

    cp -r ffmpeg-4.4.2 ffmpeg-4.4.2_android_${ARCH}

    chmod -R 777 ffmpeg-4.4.2_android_${ARCH}

    cd ${basepath}/Eyer3rdpart/ffmpeg-4.4.2_android_${ARCH}/

    if [ -d ./${INSTALL_DIR} ];then
        rm -r ${INSTALL_DIR}
    fi

    export TOOLCHAIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG
    export API=21

    if [ $ARCH == "armeabi-v7a" ];then 
        export CROSS_PREFIX="arm-linux-androideabi-"
        export FFMPEG_ARCH="arm"
        export CC=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang
        export CXX=$TOOLCHAIN/bin/armv7a-linux-androideabi$API-clang++
        export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
        export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
        export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
        export NM=$TOOLCHAIN/bin/arm-linux-androideabi-nm
        export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
        export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip
    fi
    
    if [ $ARCH == "arm64-v8a" ];then 
        export CROSS_PREFIX="aarch64-linux-android-"
        export FFMPEG_ARCH="arm64"
        export CC=$TOOLCHAIN/bin/aarch64-linux-android$API-clang
        export CXX=$TOOLCHAIN/bin/aarch64-linux-android$API-clang++
        export AR=$TOOLCHAIN/bin/aarch64-linux-android-ar
        export AS=$TOOLCHAIN/bin/aarch64-linux-android-as
        export LD=$TOOLCHAIN/bin/aarch64-linux-android-ld
        export NM=$TOOLCHAIN/bin/aarch64-linux-android-nm
        export RANLIB=$TOOLCHAIN/bin/aarch64-linux-android-ranlib
        export STRIP=$TOOLCHAIN/bin/aarch64-linux-android-strip
    fi

    if [ $ARCH == "x86" ];then 
        export CROSS_PREFIX="i686-linux-android-"
        export FFMPEG_ARCH="x86"
        export CC=$TOOLCHAIN/bin/i686-linux-android$API-clang
        export CXX=$TOOLCHAIN/bin/i686-linux-android$API-clang++
        export AR=$TOOLCHAIN/bin/i686-linux-android-ar
        export AS=$TOOLCHAIN/bin/i686-linux-android-as
        export LD=$TOOLCHAIN/bin/i686-linux-android-ld
        export NM=$TOOLCHAIN/bin/i686-linux-android-nm
        export RANLIB=$TOOLCHAIN/bin/i686-linux-android-ranlib
        export STRIP=$TOOLCHAIN/bin/i686-linux-android-strip
    fi
    
    if [ $ARCH == "x86_64" ];then 
        export CROSS_PREFIX="x86_64-linux-android-"
        export FFMPEG_ARCH="x86_64" 
        export CC=$TOOLCHAIN/bin/x86_64-linux-android$API-clang
        export CXX=$TOOLCHAIN/bin/x86_64-linux-android$API-clang++
        export AR=$TOOLCHAIN/bin/x86_64-linux-android-ar
        export AS=$TOOLCHAIN/bin/x86_64-linux-android-as
        export LD=$TOOLCHAIN/bin/x86_64-linux-android-ld
        export NM=$TOOLCHAIN/bin/x86_64-linux-android-nm
        export RANLIB=$TOOLCHAIN/bin/x86_64-linux-android-ranlib
        export STRIP=$TOOLCHAIN/bin/x86_64-linux-android-strip
    fi

    # 配置 FFmpeg 选项 

    # export COMMON_FF_CFG_FLAGS=
    # . ${basepath}/tools/configs/module.sh
    
    ## x86 的 asm 编译不过去，直接干掉
    if [ $ARCH == "x86" ];then 
        export COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-asm"
    fi

    if [ $ARCH == "x86_64" ];then 
        export COMMON_FF_CFG_FLAGS="$COMMON_FF_CFG_FLAGS --disable-asm"
    fi

    cd ${basepath}/Eyer3rdpart/ffmpeg-4.4.2_android_${ARCH}/

    echo "-I${basepath}/${LIB_DIR}/openssl_install_${ARCH}/include/"
    echo "-L${basepath}/${LIB_DIR}/openssl_install_${ARCH}/lib/"

    echo ""
    echo ""
    echo ""
    echo "ARCH: $ARCH"
    echo "NM: $NM"
    echo "CC: $CC"
    echo "STRIP: $STRIP"
    echo ""
    echo ""
    echo ""

    ./configure \
    --prefix=${basepath}/Eyer3rdpart/ffmpeg-4.4.2_android_${ARCH}/${INSTALL_DIR} \
    --enable-cross-compile \
    --arch=$FFMPEG_ARCH \
    --target-os=android \
    --nm=$NM \
    --cc=$CC \
    --strip=$STRIP \
    --enable-openssl --enable-protocols --enable-protocol=https \
    --cross-prefix=$TOOLCHAIN/bin/$CROSS_PREFIX \
    --disable-ffmpeg \
    --disable-ffplay \
    --disable-ffprobe \
    --extra-cflags="-I${basepath}/${LIB_DIR}/openssl_install/include/" \
    --extra-ldflags="-L${basepath}/${LIB_DIR}/openssl_install/lib/" \
    ${COMMON_FF_CFG_FLAGS}

    make clean
    make -j8
    make install

    cd ${basepath}

    cp -r Eyer3rdpart/ffmpeg-4.4.2_android_${ARCH}/${INSTALL_DIR} ${LIB_DIR}/${INSTALL_DIR}
}

ffmpeg_compile armeabi-v7a
ffmpeg_compile arm64-v8a
ffmpeg_compile x86
ffmpeg_compile x86_64