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

if [ -d ./EyerLib ];then 
    rm -rf EyerLib
fi

git clone https://gitee.com/redknot/EyerLib

cd ${basepath}/EyerLib/src

if [ -d ./build ];then 
    rm -rf build
fi

mkdir build

cd build

cmake ../ \
-DGLRender=ON \
-DGL_MESA=OFF \
-DEyerG=OFF \
-DCMAKE_INSTALL_PREFIX=../EyerLib_install_linux

make clean
make -j8
make install

cd ${basepath}/Lib/
if [ -d ./EyerLib_install ];then 
    rm -rf EyerLib_install
fi

cd ${basepath}/
cp -r ${basepath}/EyerLib/src/EyerLib_install_linux/ ${basepath}/Lib/EyerLib_install/