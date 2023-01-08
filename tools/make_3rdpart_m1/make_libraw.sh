echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make LibRaw                              ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/libraw_install ];then
    echo ""
    echo "*****************************"
    echo "*        LibRaw exist       *"
    echo "*****************************"
    echo ""
    exit;
fi

LIB_RAW_SRC_DIR=LibRaw-0.20.2

cd ${basepath}/Eyer3rdpart/${LIB_RAW_SRC_DIR}/

export CXXFLAGS="${CXXFLAGS} -std=c++11 -lstdc++"
export LIBS="${LIBS} -lstdc++"

./configure --prefix=${basepath}/Eyer3rdpart/${LIB_RAW_SRC_DIR}/libraw_install --enable-static --disable-shared

make clean
make -j4
make install




cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./libraw_install ];then
    rm -r libraw_install
fi

cd ${basepath}

cp -r Eyer3rdpart/${LIB_RAW_SRC_DIR}/libraw_install Lib/libraw_install