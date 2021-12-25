cmake_minimum_required(VERSION 3.10)
project(time_swig)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-fPIC)
include_directories(src/hashring)

set(BUILD_CONAN_LIB ON)


if (BUILD_CONAN_LIB)
    set(CONAN_CMAKE_FILE_PATH ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    if(NOT EXISTS ${CONAN_CMAKE_FILE_PATH})
        message(FATAL_ERROR "The file ${CONAN_CMAKE_FILE_PATH} doesn't exist, you have to run follow command \n `conan install . -s compiler.libcxx=libstdc++11 --install-folder=${CMAKE_BINARY_DIR}`")
    endif()

    include(${CONAN_CMAKE_FILE_PATH})
    conan_basic_setup(TARGET NO_OUTPUT_DIRS)

    include(${CONAN_BUILD_MODULES_PATHS_SWIG})
    set(SWIG_DIR ${CONAN_SWIG_ROOT})
    set(SWIG_EXECUTABLE ${CONAN_BIN_DIRS_SWIG}/swig)
    set(SYS_LIBS ${CONAN_LIBS})
else()
    set(SYS_LIBS ${LUA_LIBRARIES})
endif()

find_package (SWIG REQUIRED)
include(UseSWIG)
INCLUDE(${SWIG_USE_FILE})
SET(CMAKE_SWIG_FLAGS "")

set(SWIG_FILES src/interfaces/swig/hashring_g.i)
set(SRC_FILES src/hashring/hashring.cpp)


set_property(SOURCE ${SWIG_FILES} PROPERTY CPLUSPLUS ON)

set(TARGET_MODEL_NAME TimeSwig)

SET_SOURCE_FILES_PROPERTIES(${SWIG_FILES} PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(${SWIG_FILES} PROPERTIES SWIG_FLAGS "-includeall")


#--------------------------------------------------------------------
# capitalize(retval string)
# Make the first letter uppercase and the rest lower
function(capitalize retval value)
    string(TOLOWER ${value} lowercase)
    string(SUBSTRING ${lowercase} 0 1 first_letter)
    string(TOUPPER ${first_letter} first_letter)
    string(REGEX REPLACE "^.(.*)" "${first_letter}\\1" result "${lowercase}")
    set(${retval} ${result} PARENT_SCOPE)
endfunction()


function(_SWIG_LAN TARGET_LANGUAGE)
    capitalize(LAN ${TARGET_LANGUAGE})
    string(TOLOWER "${TARGET_LANGUAGE}" lowercase_language)
    set(SWIG_MODEL_NAME ${TARGET_MODEL_NAME}${LAN})


    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET_LANGUAGE})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${TARGET_LANGUAGE})
    set(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/${TARGET_LANGUAGE})

    if("${lowercase_language}" STREQUAL "javascript")
        set(CMAKE_SWIG_FLAGS -module ${SWIG_MODEL_NAME} -node)
    endif()

    SWIG_ADD_MODULE(${SWIG_MODEL_NAME} ${TARGET_LANGUAGE} ${SWIG_FILES} ${SRC_FILES})

    if ("${lowercase_language}" STREQUAL "lua")
        set_target_properties(${SWIG_MODULE_${SWIG_MODEL_NAME}_REAL_NAME} PROPERTIES OUTPUT_NAME ${TARGET_MODEL_NAME})
    elseif("${lowercase_language}" STREQUAL "python")
        set_target_properties(${SWIG_MODULE_${SWIG_MODEL_NAME}_REAL_NAME} PROPERTIES OUTPUT_NAME _${TARGET_MODEL_NAME})
    elseif("${lowercase_language}" STREQUAL "javascript")
        INCLUDE_DIRECTORIES(${NODEJS_INCLUDE_DIRS})
        SWIG_LINK_LIBRARIES(${SWIG_MODEL_NAME} ${SYS_LIBS} ${NODEJS_LIBRARIES})
    endif()

    SWIG_LINK_LIBRARIES(${SWIG_MODEL_NAME} ${SYS_LIBS} ${${TARGET_LANGUAGE}_LIBRARIES})
endfunction()

include(src/cmake/lua.cmake)
include(src/cmake/python.cmake)

# doesn't work yet
# include(cmake/javascript.cmake)

