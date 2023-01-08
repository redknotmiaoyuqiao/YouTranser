cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/src/

if [ -d ./build ];then 
    rm -rf build
fi
mkdir build

cd build

export CMAKE_HOME=/c/cmake/
${CMAKE_HOME}/bin/cmake ../ -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=${basepath}/src/install/

mingw32-make clean
mingw32-make -j4
mingw32-make install

cd ${basepath}/Lib/
if [ -d ./you_picker_install ];then 
    rm -rf you_picker_install
fi

cp -r ${basepath}/src/install ${basepath}/Lib/you_picker_install