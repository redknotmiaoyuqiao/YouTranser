echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make OpenSSL                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/openssl_install ];then
    echo ""
    echo "*****************************"
    echo "*        openssl exist      *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 openssl-1.1.1k

cd ${basepath}/Eyer3rdpart/openssl-1.1.1k/

if [ -d ./openssl_install ];then
    rm -r openssl_install
fi

./config no-asm --prefix=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install no-shared \
--openssldir=${basepath}/Eyer3rdpart/openssl-1.1.1k/openssl_install

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./openssl_install ];then
    rm -r openssl_install
fi

cd ${basepath}

cp -r Eyer3rdpart/openssl-1.1.1k/openssl_install Lib/openssl_install