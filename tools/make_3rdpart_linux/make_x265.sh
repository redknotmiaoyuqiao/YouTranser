echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make x265                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/x265_install ];then
    echo ""
    echo "*****************************"
    echo "*        x265 exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 x265_3.5

cd ${basepath}/Eyer3rdpart/x265_3.5/

if [ -d ./x265_install ];then
    rm -r x265_install
fi

if [ -d ./x265_build ];then 
    rm -rf x265_build
fi
mkdir x265_build

cd ${basepath}/Eyer3rdpart/x265_3.5/x265_build

cmake ../source/ \
-DENABLE_SHARED=OFF \
-DCMAKE_INSTALL_PREFIX=${basepath}/Eyer3rdpart/x265_3.5/x265_install \
-DENABLE_LIBNUMA=OFF

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./x265_install ];then
    rm -r x265_install
fi

cd ${basepath}

cp -r Eyer3rdpart/x265_3.5/x265_install Lib/x265_install