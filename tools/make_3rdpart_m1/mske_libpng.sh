echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make libpng                              ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/libpng_install ];then
    echo ""
    echo "*****************************"
    echo "*        libpng exist       *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 libpng-1.6.37

cd ${basepath}/Eyer3rdpart/libpng-1.6.37/
./configure --prefix=${basepath}/Eyer3rdpart/libpng-1.6.37/libpng_install --enable-static --disable-shared

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./libpng_install ];then
    rm -r libpng_install
fi

cd ${basepath}

cp -r Eyer3rdpart/libpng-1.6.37/libpng_install Lib/libpng_install