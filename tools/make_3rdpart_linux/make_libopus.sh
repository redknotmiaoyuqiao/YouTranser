echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make opus                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/libopus_install ];then
    echo ""
    echo "*****************************"
    echo "*        opus exist        *"
    echo "*****************************"
    echo ""
    exit;
fi

OPUS_DIR=opus-1.3.1

cd ${basepath}/Eyer3rdpart/

chmod -R 777 ${OPUS_DIR}

cd ${basepath}/Eyer3rdpart/${OPUS_DIR}/

./configure --prefix=${basepath}/Eyer3rdpart/${OPUS_DIR}/libopus_install --enable-static --disable-shared

make clean
make -j4
make install


cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./libopus_install ];then
    rm -r libopus_install
fi

cd ${basepath}

cp -r Eyer3rdpart/${OPUS_DIR}/libopus_install Lib/libopus_install