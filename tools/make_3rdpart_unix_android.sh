cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

if [ "reclone" == "${1}" ];then 
    if [ -d ./Eyer3rdpart ];then 
        rm -rf Eyer3rdpart
    fi

    if [ -d ./Eyer3rdpartOpenCV ];then 
        rm -rf Eyer3rdpartOpenCV
    fi

    if [ -d ./Eyer3rdpartSkia ];then 
        rm -rf Eyer3rdpartSkia
    fi

    if [ -d ./Eyer3rdpartBGFX ];then 
        rm -rf Eyer3rdpartBGFX
    fi
fi

if [ ! -d ./Eyer3rdpart ];then 
    git clone https://gitee.com/redknot/Eyer3rdpart
fi

if [ ! -d ./Eyer3rdpartOpenCV ];then 
    git clone https://gitee.com/redknot/Eyer3rdpartOpenCV
fi

if [ ! -d ./Eyer3rdpartSkia ];then 
    git clone https://gitee.com/redknot/Eyer3rdpartSkia
fi

if [ ! -d ./Eyer3rdpartBGFX ];then 
    git clone https://gitee.com/redknot/Eyer3rdpartBGFX
fi

if [ ! -n "$NDK" ]; then
    echo "Please set NDK first"
    echo "export NDK=...."
    exit;
fi

# Android ENV
files=$(ls $NDK/toolchains/llvm/prebuilt/)
export HOST_TAG=$""
for filename in $files
do
    echo $filename
    export HOST_TAG=$filename
done

# export ANDROID_NDK=$NDK

echo "HOST_TAG:"${HOST_TAG}

export ANDROID_NDK_HOME=${NDK}
export TOOLCHAIN=${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/${HOST_TAG}
export PATH=$NDK/toolchains/llvm/prebuilt/$HOST_TAG/bin:$PATH

# export TARGET=armv7a-linux-androideabi
# export API=18
# export CC=$TOOLCHAIN/bin/$TARGET$API-clang
# export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++
# export AR=$TOOLCHAIN/bin/arm-linux-androideabi-ar
# export AS=$TOOLCHAIN/bin/arm-linux-androideabi-as
# export LD=$TOOLCHAIN/bin/arm-linux-androideabi-ld
# export RANLIB=$TOOLCHAIN/bin/arm-linux-androideabi-ranlib
# export STRIP=$TOOLCHAIN/bin/arm-linux-androideabi-strip

export BASE_LIB_DIR=Lib_android


platform=$(uname -a)
echo $platform

cd ${basepath}/tools/make_3rdpart_android/

bash make_openssl.sh

bash make_ffmpeg.sh

bash make_jsoncpp.sh