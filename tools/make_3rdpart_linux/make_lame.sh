echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make Lame                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/lame_install ];then
    echo ""
    echo "*****************************"
    echo "*        lame exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 lame-3.100

cd ${basepath}/Eyer3rdpart/lame-3.100/
./configure --prefix=${basepath}/Eyer3rdpart/lame-3.100/lame_install --enable-static --disable-shared

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./lame_install ];then
    rm -r lame_install
fi

cd ${basepath}

cp -r Eyer3rdpart/lame-3.100/lame_install Lib/lame_install