cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/YouPicker_QT/

if [ -d ${basepath}/YouPicker_QT/Release_build ];then
    rm -rf Release_build/
fi

mkdir Release_build/

cmake ../

make

cd YouTranscoder/

macdeployqt YouTranser.app -dmg