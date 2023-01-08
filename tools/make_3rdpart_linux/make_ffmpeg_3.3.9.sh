echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make FFmpeg 3.3.9                        ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

FFMPEG_DIR=ffmpeg-3.3.9
FFMPEG_DIST=ffmpeg-3.3.9_install

if [ -d ${basepath}/Lib/${FFMPEG_DIST} ];then
    echo ""
    echo "*****************************"
    echo "*        ffmpeg exist       *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 ${FFMPEG_DIR}

cd ${basepath}/Eyer3rdpart/${FFMPEG_DIR}/

export PKG_CONFIG_PATH=${basepath}/Lib/x265_install/lib/pkgconfig/:$PKG_CONFIG_PATH
export PKG_CONFIG_PATH=${basepath}/Lib/x264_install/lib/pkgconfig/:$PKG_CONFIG_PATH

echo $PKG_CONFIG_PATH

./configure \
--enable-static --disable-shared \
--prefix=${basepath}/Eyer3rdpart/${FFMPEG_DIR}/ffmpeg_install \
--enable-gpl \
--enable-pic \
--extra-libs="-ldl -lm -lstdc++ -lpthread" \
--enable-libx264 \
--enable-libmp3lame \
--enable-libvpx \
--enable-decoder=vp8 \
--enable-decoder=vp9 \
--enable-decoder=libvpx_vp8 \
--enable-decoder=libvpx_vp9 \
--enable-encoder=libvpx_vp8 \
--enable-encoder=libvpx_vp9 \
--enable-openssl --enable-protocols --enable-protocol=https \
--enable-nonfree \
--extra-cflags="-I${basepath}/Lib/x264_install/include/ -I${basepath}/Lib/lame_install/include/ -I${basepath}/Lib/fdk_aac_install/include/ -I${basepath}/Lib/x265_install/include/ -I${basepath}/Lib/openssl_install/include/ -I${basepath}/Lib/libvpx_install/include/" \
--extra-ldflags="-L${basepath}/Lib/x264_install/lib/ -L${basepath}/Lib/lame_install/lib/ -L${basepath}/Lib/fdk_aac_install/lib/ -L${basepath}/Lib/x265_install/lib/ -L${basepath}/Lib/openssl_install/lib/ -L${basepath}/Lib/libvpx_install/lib/ -lstdc++ -lm"

#--enable-libx265 \

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./${FFMPEG_DIST} ];then
    rm -r ${FFMPEG_DIST}
fi

cd ${basepath}

cp -r Eyer3rdpart/${FFMPEG_DIR}/ffmpeg_install Lib/${FFMPEG_DIST}