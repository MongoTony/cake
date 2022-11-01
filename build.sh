args=$1


# 外部编译，创建build
if [ ! -d "build" ];then
    mkdir build
else
    rm -rf build
    mkdir build
fi

build() {
    # 外部编译
    cd build
    cmake ..
    # 先删除原来文件，在编译
    make clean
    make
}

build
../output/cake
