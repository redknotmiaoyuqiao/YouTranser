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


platform=$(uname -a)
echo $platform

cd ${basepath}/tools/make_3rdpart_m1

sh make_openssl.sh

sh make_x264.sh

sh make_x265.sh

sh make_lame.sh

sh make_fdk_aac.sh

sh mske_libpng.sh

sh make_libvpx.sh

sh make_ffmpeg.sh

sh make_glfw.sh

sh make_jsoncpp.sh

sh make_freetype.sh

# sh make_skia.sh

sh make_bgfx.sh

sh make_libraw.sh