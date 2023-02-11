# YouTranser

YouTranser 是一款开源免费的视频转码工具，支持 Windows，Mac，Linux。

网址：www.zzsin.com


# 编译指南

## Mac

- 首先，先编译第三方库
    ````
    bash make_3rdpart_unix_m1.sh
    ````

- 之后编译 EyerLib (核心库)
    ````
    bash make_eyer_lib_m1.sh
    ````
- 之后编译界面，界面是 Qt 写的，所以你要先安装 Qt，之后跑下面的代码
    ````
    cd You_QT
    mkdir build
    cd build

    cmake ../You/ -DCMAKE_PREFIX_PATH=<qt-path>

    make clean
    make -j8
    ````

## Windows

windows 下使用 msys2 + mingw 进行编译，所以你要先安装，之后在 msys2 环境里面去执行。

- 首先，先编译第三方库
    ````
    bash make_3rdpart_unix_msys2.sh
    ````

- 之后编译 EyerLib (核心库)
    ````
    bash make_eyer_lib_msys.sh
    ````
- 之后编译界面，界面是 Qt 写的，所以你要先安装 Qt，之后跑下面的代码
    ````
    cd You_QT
    mkdir build
    cd build

    cmake ../You/ -DCMAKE_PREFIX_PATH=C:/Qt/6.2.4/mingw_64/ -G "MinGW Makefiles"

    mingw32-make clean
    mingw32-make -j4
    ````