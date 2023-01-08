cd ../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

IS_GLFW=OFF

while getopts "r:u:" opt; do
    case $opt in
        r)
            echo "OPT_ARG: $OPTARG"
            if [ -d ./Eyer3rdpart ];then 
                rm -rf Eyer3rdpart
            fi

            if [ -d ./Eyer3rdpartOpenCV ];then 
                rm -rf Eyer3rdpartOpenCV
            fi

            if [ -d ./Eyer3rdpartSkia ];then 
                rm -rf Eyer3rdpartSkia
            fi
            ;;

        u)
            echo "OPT_ARG: $OPTARG"
            IS_GLFW=ON
            ;;
        \?)
            echo "Invalid option"
            ;;
    esac
done

# 

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

cd ${basepath}/tools/make_3rdpart_linux/

sh make_openssl.sh

sh make_x264.sh

sh make_x265.sh

sh make_lame.sh

sh make_fdk_aac.sh

sh mske_libpng.sh

sh make_libvpx.sh

sh make_libopus.sh

sh make_ffmpeg.sh

sh make_ffmpeg_3.3.9.sh

echo ${IS_GLFW}

if [ ${IS_GLFW} = ON ];then
    sh make_glfw.sh
fi

sh make_jsoncpp.sh

sh make_freetype.sh

# sh make_skia.sh

# sh make_bgfx.sh

sh make_libraw.sh

sh make_opencv.sh