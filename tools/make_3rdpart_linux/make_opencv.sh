echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make OpenCV                              ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/opencv_install ];then
    echo ""
    echo "*****************************"
    echo "*        OpenCV exist       *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpartOpenCV/

chmod -R 777 opencv-4.5.4

cd ${basepath}/Eyer3rdpartOpenCV/opencv-4.5.4/

if [ -d ./opencv_install ];then
    rm -r opencv_install
fi

if [ -d ./opencv_build ];then 
    rm -rf opencv_build
fi
mkdir opencv_build

cd ${basepath}/Eyer3rdpartOpenCV/opencv-4.5.4/opencv_build

cmake ../ -DCMAKE_INSTALL_PREFIX=../opencv_install 

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./opencv_install ];then
    rm -r opencv_install
fi

cd ${basepath}

cp -r Eyer3rdpartOpenCV/opencv-4.5.4/opencv_install Lib/opencv_install