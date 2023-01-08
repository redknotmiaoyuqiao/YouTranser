echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make FFmpeg                              ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/ffmpeg_install ];then
    echo ""
    echo "*****************************"
    echo "*        ffmpeg exist       *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 ffmpeg-4.4.2

cd ${basepath}/Eyer3rdpart/ffmpeg-4.4.2/

./configure \
--enable-static --disable-shared \
--prefix=${basepath}/Eyer3rdpart/ffmpeg-4.4.2/ffmpeg_install \
--enable-gpl \
--enable-pic \
--extra-libs=-ldl \
--enable-libx264 \
--enable-libx265 \
--enable-libmp3lame \
--enable-libfdk-aac \
--enable-libvpx \
--enable-encoder=libvpx_vp8 \
--enable-encoder=libvpx_vp9 \
--enable-openssl --enable-protocols --enable-protocol=https \
--enable-nonfree \
--extra-cflags="-I${basepath}/Lib/x264_install/include/ -I${basepath}/Lib/lame_install/include/ -I${basepath}/Lib/fdk_aac_install/include/ -I${basepath}/Lib/x265_install/include/ -I${basepath}/Lib/openssl_install/include/ -I${basepath}/Lib/libvpx_install/include/" \
--extra-ldflags="-L${basepath}/Lib/x264_install/lib/ -L${basepath}/Lib/lame_install/lib/ -L${basepath}/Lib/fdk_aac_install/lib/ -L${basepath}/Lib/x265_install/lib/ -L${basepath}/Lib/openssl_install/lib/ -L${basepath}/Lib/libvpx_install/lib/ -lstdc++"

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./ffmpeg_install ];then
    rm -r ffmpeg_install
fi

cd ${basepath}

cp -r Eyer3rdpart/ffmpeg-4.4.2/ffmpeg_install Lib/ffmpeg_install