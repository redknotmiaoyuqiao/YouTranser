echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make FDK AAC                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/fdk_aac_install ];then
    echo ""
    echo "*****************************"
    echo "*        fdkaac exist       *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 fdk-aac-2.0.2

cd ${basepath}/Eyer3rdpart/fdk-aac-2.0.2/
./configure --prefix=${basepath}/Eyer3rdpart/fdk-aac-2.0.2/fdk_aac_install --enable-static --disable-shared

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./fdk_aac_install ];then
    rm -r fdk_aac_install
fi

cd ${basepath}

cp -r Eyer3rdpart/fdk-aac-2.0.2/fdk_aac_install Lib/fdk_aac_install