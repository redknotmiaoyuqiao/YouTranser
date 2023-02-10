echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make x264                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/x264_install ];then
    echo "*****************************"
    echo "*        x264 exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 x264

cd ${basepath}/Eyer3rdpart/x264/

if [ -d ./x264_install ];then
    rm -r x264_install
fi

./configure --prefix=${basepath}/Eyer3rdpart/x264/x264_install --enable-static --disable-shared \
--disable-avs \
--disable-swscale \
--disable-lavf \
--disable-ffms \
--disable-gpac \
--disable-lsmash

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./x264_install ];then
    rm -r x264_install
fi

cd ${basepath}

cp -r Eyer3rdpart/x264/x264_install Lib/x264_install