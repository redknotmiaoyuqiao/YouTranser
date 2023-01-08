echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make bgfx                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/bgfx_install ];then
    echo ""
    echo "*****************************"
    echo "*        bgfx exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpartBGFX/

chmod -R 777 bgfx.cmake

cd ${basepath}/Eyer3rdpartBGFX/bgfx.cmake/

if [ -d ./bgfx_install ];then
    rm -r bgfx_install
fi

if [ -d ./bgfx_build ];then 
    rm -rf bgfx_build
fi

mkdir bgfx_build

cd ${basepath}/Eyer3rdpartBGFX/bgfx.cmake/bgfx_build/

cmake ../ \
-DCMAKE_INSTALL_PREFIX=${basepath}/Eyer3rdpartBGFX/bgfx.cmake/bgfx_install


make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./bgfx_install ];then
    rm -r bgfx_install
fi

cd ${basepath}

cp -r Eyer3rdpartBGFX/bgfx.cmake/bgfx_install Lib/bgfx_install