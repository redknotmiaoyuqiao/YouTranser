echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make GLFW                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/glfw_install ];then
    echo ""
    echo "*****************************"
    echo "*        glfw exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 glfw-3.3.4

cd ${basepath}/Eyer3rdpart/glfw-3.3.4/

if [ -d ./glfw_install ];then
    rm -r glfw_install
fi

if [ -d ./glfw_build ];then 
    rm -rf glfw_build
fi
mkdir glfw_build

cd ${basepath}/Eyer3rdpart/glfw-3.3.4/glfw_build

cmake ../ \
-DCMAKE_INSTALL_PREFIX=${basepath}/Eyer3rdpart/glfw-3.3.4/glfw_install

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./glfw_install ];then
    rm -r glfw_install
fi

cd ${basepath}

cp -r Eyer3rdpart/glfw-3.3.4/glfw_install Lib/glfw_install