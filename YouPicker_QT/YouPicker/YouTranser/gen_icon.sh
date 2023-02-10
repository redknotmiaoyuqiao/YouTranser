basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

cd ${basepath}/YouTransIcon.iconset/

function sips_image()
{
    sips -z $2 $2 $1 --out icon_$2.png
    sips -z $2 $2 $1 --out icon_$2@2x.png
}

sips_image YouTransIcon.png 512
sips_image YouTransIcon.png 256
sips_image YouTransIcon.png 128
sips_image YouTransIcon.png 64
sips_image YouTransIcon.png 32
sips_image YouTransIcon.png 16

cd ${basepath}/

iconutil -c icns YouTransIcon.iconset