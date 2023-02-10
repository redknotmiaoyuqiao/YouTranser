echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make x265                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/x265_install ];then
    echo ""
    echo "*****************************"
    echo "*        x265 exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

X265_SRC=x265_git

chmod -R 777 ${X265_SRC}

cd ${basepath}/Eyer3rdpart/${X265_SRC}/

if [ -d ./x265_install ];then
    rm -r x265_install
fi



if [ -d ./x265_build_8bit ];then 
    rm -rf x265_build_8bit
fi
mkdir x265_build_8bit

if [ -d ./x265_build_10bit ];then 
    rm -rf x265_build_10bit
fi
mkdir x265_build_10bit

if [ -d ./x265_build_12bit ];then 
    rm -rf x265_build_12bit
fi
mkdir x265_build_12bit 


cd ${basepath}/Eyer3rdpart/${X265_SRC}/x265_build_12bit
${CMAKE_HOME}/bin/cmake -G "MinGW Makefiles" ../source -DENABLE_ASSEMBLY=ON -DHIGH_BIT_DEPTH=ON -DEXPORT_C_API=OFF -DENABLE_SHARED=OFF -DENABLE_CLI=OFF -DMAIN12=ON
mingw32-make -j4

cd ${basepath}/Eyer3rdpart/${X265_SRC}/x265_build_10bit
${CMAKE_HOME}/bin/cmake -G "MinGW Makefiles" ../source -DENABLE_ASSEMBLY=ON -DHIGH_BIT_DEPTH=ON -DEXPORT_C_API=OFF -DENABLE_SHARED=OFF -DENABLE_CLI=OFF
mingw32-make -j4

cd ${basepath}/Eyer3rdpart/${X265_SRC}/x265_build_8bit

ln -sf ../x265_build_10bit/libx265.a libx265_main10.a
ln -sf ../x265_build_12bit/libx265.a libx265_main12.a

${CMAKE_HOME}/bin/cmake -G "MinGW Makefiles" ../source \
-DCMAKE_INSTALL_PREFIX=${basepath}/Eyer3rdpart/${X265_SRC}/x265_install \
-DENABLE_SHARED=OFF \
-DENABLE_ASSEMBLY=ON \
-DEXTRA_LIB="x265_main10.a;x265_main12.a" \
-DEXTRA_LINK_FLAGS=-L. \
-DLINKED_10BIT=ON -DLINKED_12BIT=ON

mingw32-make -j4

mv libx265.a libx265_main.a

ar -M <<EOF
CREATE libx265.a
ADDLIB libx265_main.a
ADDLIB libx265_main10.a
ADDLIB libx265_main12.a
SAVE
END
EOF

mingw32-make install



cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./x265_install ];then
    rm -r x265_install
fi

cd ${basepath}

cp -r Eyer3rdpart/${X265_SRC}/x265_install Lib/x265_install