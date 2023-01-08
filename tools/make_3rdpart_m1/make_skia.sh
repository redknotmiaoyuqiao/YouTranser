echo "======================================================================="
echo "=                                                                     ="
echo "=                                                                     ="
echo "=                            Make Skia                                ="
echo "=                                                                     ="
echo "=                                                                     ="
echo "======================================================================="

cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ -d ${basepath}/Lib/skia_install ];then
    echo ""
    echo "*****************************"
    echo "*        skia exist         *"
    echo "*****************************"
    echo ""
    exit;
fi

cd ${basepath}/Eyer3rdpartSkia/
export PATH="${PWD}/depot_tools:${PATH}"

cd ${basepath}/Eyer3rdpartSkia/skia/

python3 tools/git-sync-deps

echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo "======================================================================="
echo "=                                  compile                            ="
echo "======================================================================="
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""

bin/gn gen out/Static --args='
is_official_build=true
skia_use_system_libjpeg_turbo=false
skia_use_system_libpng=false
skia_use_system_icu=false
skia_use_system_harfbuzz=false
skia_use_libwebp_decode=false
skia_use_libwebp_encode=false
'

ninja -C out/Static


if [ ! -d ${basepath}/Lib/skia_install ];then
    cd ${basepath}/Lib/
    mkdir skia_install
fi

cd ${basepath}/Lib/skia_install

# 搬运头文件
cp -r ${basepath}/Eyer3rdpartSkia/skia/include ${basepath}/Lib/skia_install/

cd ${basepath}/Lib/skia_install

if [ ! -d lib ];then
    mkdir lib
fi

cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libskia.a ${basepath}/Lib/skia_install/lib/libskia.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libskottie.a ${basepath}/Lib/skia_install/lib/libskottie.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libskparagraph.a ${basepath}/Lib/skia_install/lib/libskparagraph.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libskresources.a ${basepath}/Lib/skia_install/lib/libskresources.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libsksg.a ${basepath}/Lib/skia_install/lib/libsksg.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libskshaper.a ${basepath}/Lib/skia_install/lib/libskshaper.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libsktext.a ${basepath}/Lib/skia_install/lib/libsktext.a
cp ${basepath}/Eyer3rdpartSkia/skia/out/Static/libskunicode.a ${basepath}/Lib/skia_install/lib/libskunicode.a