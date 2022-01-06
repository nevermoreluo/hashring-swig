#hashring
目的是使用swig创建py，lua等脚本语言的c++库的实现以及测试  
目前仅在linux环境下测试过  


# Just test cpp+swig for now
先实验lua+python

## Build-Requirement
1. conan


## Build
如果使用conan管理包，则直接通过cmake编译即可  
如果不使用conan的话，请关掉cmake中的BUILD_CONAN_LIB,并手动安装conanfile.txt中的相应的依赖


## 目录结构  
```
├── lib # swig生成的各语言的库位置
│     ├── lua
│     │     ├── Hashring.so
│     │     └── hashring_gLUA_wrap.cxx
│     └── python
│           ├── Hashring.py
│           ├── _Hashring.so
│           └── hashring_gPYTHON_wrap.cxx
└── src
    ├── cmake  # 管理每个语言生成的cmake文件
    │     ├── lua.cmake
    │     └── python.cmake
    ├── hashring # 需要暴露的项目本身的source code
    │     ├── consistent_hash_map.hpp
    │     ├── hash
    │     │     ├── md5.cpp
    │     │     └── md5.h
    │     ├── hashring.cpp
    │     └── hashring.h
    ├── interfaces # swig需要的定义template文件
    │     └── swig
    │         ├── hashring.i
    │         └── hashring_g.i
    └── tests  # 用于各个语言的测试脚本
        ├── hashring_test.lua
        └── hashring_test.py
```




## How to test?
具体清查阅src/tests目录下的脚本

## Python
python2和python3都是支持的，但是需要安装对应的python版本才可以哦，如果有需要设定特定版本的，  
修改conanfile.txt内的cpython版本或者修改cmake/python.cmake文件内的FIND_PACKAGE的require


## Plan
- [x] Multi Language cmake
- [x] Lua support
- [x] Python support
- [ ] Class support
- [ ] Memory lifetime test
- [ ] Rust support
- [ ] Js support
