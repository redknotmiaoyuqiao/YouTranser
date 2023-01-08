echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make vpx                                 ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/libvpx_install ];then
    echo ""
    echo "*****************************"
    echo "*        vpx exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 libvpx-1.11.0

cd ${basepath}/Eyer3rdpart/libvpx-1.11.0/
./configure --prefix=${basepath}/Eyer3rdpart/libvpx-1.11.0/libvpx_install --enable-static --disable-shared

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./libvpx_install ];then
    rm -r libvpx_install
fi

cd ${basepath}

cp -r Eyer3rdpart/libvpx-1.11.0/libvpx_install Lib/libvpx_install