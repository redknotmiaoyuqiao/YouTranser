echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make JSONCPP                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/jsoncpp_install ];then
    echo ""
    echo "*****************************"
    echo "*        jsoncpp exist      *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 jsoncpp-1.9.4

cd ${basepath}/Eyer3rdpart/jsoncpp-1.9.4/

if [ -d ./jsoncpp_install ];then
    rm -r jsoncpp_install
fi

if [ -d ./jsoncpp_build ];then 
    rm -rf jsoncpp_build
fi
mkdir jsoncpp_build

cd ${basepath}/Eyer3rdpart/jsoncpp-1.9.4/jsoncpp_build

cmake ../ \
-DBUILD_SHARED_LIBS=OFF \
-DBUILD_STATIC_LIBS=ON \
-DCMAKE_INSTALL_PREFIX=${basepath}/Eyer3rdpart/jsoncpp-1.9.4/jsoncpp_install

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./jsoncpp_install ];then
    rm -r jsoncpp_install
fi

cd ${basepath}

cp -r Eyer3rdpart/jsoncpp-1.9.4/jsoncpp_install Lib/jsoncpp_install