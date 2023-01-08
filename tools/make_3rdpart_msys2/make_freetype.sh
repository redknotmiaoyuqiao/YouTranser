echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make freetype                            ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/freetype_install ];then
    echo ""
    echo "*****************************"
    echo "*        freetype exist     *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpart/

chmod -R 777 freetype-2.11.1

cd ${basepath}/Eyer3rdpart/freetype-2.11.1/
if [ -d ./freetype_install ];then
    rm -r freetype_install
fi

./configure \
--prefix=${basepath}/Eyer3rdpart/freetype-2.11.1/freetype_install \
--without-harfbuzz \
--without-brotli \
--enable-static \
--disable-shared \
--enable-pic

make clean
make -j4
make install

cd ${basepath}

if [ ! -d ./Lib ];then
    mkdir Lib
fi

cd ${basepath}/Lib

if [ -d ./freetype_install ];then
    rm -r freetype_install
fi

cd ${basepath}

cp -r Eyer3rdpart/freetype-2.11.1/freetype_install Lib/freetype_install