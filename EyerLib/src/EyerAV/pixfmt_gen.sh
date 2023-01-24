basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

echo "" > pixfmt_gen_auto_code_def.txt;
echo "" > pixfmt_gen_auto_code_imp.txt;
echo "" > pixfmt_gen_auto_code_switch.txt;

for line in `cat ${basepath}/pixfmt_des.txt`
do
    echo $line
    fmt_name=$line
    code_def="static EyerAVPixelFormat EYER_${fmt_name};"
    echo ${code_def} >> pixfmt_gen_auto_code_def.txt;

    code_imp="EyerAVPixelFormat EyerAVPixelFormat::EYER_${fmt_name} (AV_PIX_FMT_${fmt_name}, AV_PIX_FMT_${fmt_name}, \"EYER_${fmt_name}\", \"${fmt_name}\");"
    echo ${code_imp} >> pixfmt_gen_auto_code_imp.txt;

    code_switch="case AV_PIX_FMT_${fmt_name}: return EYER_${fmt_name};"
    echo ${code_switch} >> pixfmt_gen_auto_code_switch.txt;
done
