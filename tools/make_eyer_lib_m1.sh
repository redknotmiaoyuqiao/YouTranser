echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make EyerLib                             ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/EyerLib/src

if [ -d ./build ];then 
    rm -rf build
fi

mkdir build

cd build

cmake ../ \
-DGLRender=ON \
-DGL_MESA=OFF \
-DEyerG=ON \
-DGLRender=OFF \
-DENABLE_EYER_TEST=OFF \
-DCMAKE_INSTALL_PREFIX=${basepath}/EyerLib/src/install

make clean
make -j8
make install

cd ${basepath}/Lib/
if [ -d ./EyerLib_install ];then 
    rm -rf EyerLib_install
fi

cd ${basepath}/
cp -r ${basepath}/EyerLib/src/install/ ${basepath}/Lib/EyerLib_install/