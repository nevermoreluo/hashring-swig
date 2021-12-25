
if (NOT ${BUILD_CONAN_LIB})
    find_package(lua)
    INCLUDE_DIRECTORIES(${LUA_INCLUDE_PATH})
endif()


_SWIG_LAN(lua)
