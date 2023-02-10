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

if [ ! -d ./EyerLib ];then 
    git clone https://gitee.com/redknot/EyerLib
fi

if [ -d ./EyerLib ];then 
    cd EyerLib
    git pull origin master
fi

cd ${basepath}/EyerLib/src

if [ -d ./build ];then 
    rm -rf build
fi

mkdir build

cd build

export CMAKE_HOME=/c/cmake/

${CMAKE_HOME}/bin/cmake ../ \
-G "MinGW Makefiles" \
-DGLRender=ON \
-DGL_MESA=OFF \
-DEyerG=OFF \
-DENABLE_EYER_TEST=OFF \
-DCMAKE_INSTALL_PREFIX=${basepath}/EyerLib/src/install

mingw32-make clean
mingw32-make -j4
mingw32-make install

cd ${basepath}/Lib/
if [ -d ./EyerLib_install ];then 
    rm -rf EyerLib_install
fi

cd ${basepath}/
cp -r ${basepath}/EyerLib/src/install/ ${basepath}/Lib/EyerLib_install/