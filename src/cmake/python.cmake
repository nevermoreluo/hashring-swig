
if (NOT ${BUILD_CONAN_LIB})
    FIND_PACKAGE(PythonLibs REQUIRED)
    INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
endif()

_SWIG_LAN(python)