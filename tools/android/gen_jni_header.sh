cd ../../

basepath=$(cd `dirname $0`; pwd)
echo ${basepath}

javac -h ./ ${basepath}/YouPicker_Android/app/src/main/java/com/yao/youpicker_android/JniFunc.java -classpath ${ANDROID_SDK_HOME}/platforms/android-30/android.jar:${basepath}/YouPicker_Android/app/src/main/java/:.

mv ${basepath}/com_yao_youpicker_android_jniFunc.h ${basepath}/src/YouPickerAndroid/com_yao_youpicker_android_jniFunc.h
