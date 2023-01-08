cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/src/

if [ -d ./build ];then 
    rm -rf build
fi
mkdir build

cd build

cmake ../ -DCMAKE_INSTALL_PREFIX=${basepath}/src/install/

make clean
make -j8
make install

cd ${basepath}/Lib/
if [ -d ./you_picker_install ];then 
    rm -rf you_picker_install
fi

cp -r ${basepath}/src/install ${basepath}/Lib/you_picker_install