cmake_minimum_required(VERSION 3.10)
project(hashring)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-fPIC)
include_directories(src/hashring)

set(BUILD_CONAN_LIB ON)


if (BUILD_CONAN_LIB)

    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/.conan/conan.cmake
            DESTINATION ${CMAKE_BINARY_DIR})
    endif()
    # 国内下github太慢了 我直接下载在.conan文件内了
    # file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
    #        "${CMAKE_BINARY_DIR}/conan.cmake")

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(NO_OUTPUT_DIRS CONANFILE conanfile.txt
            INSTALL_FOLDER ${CMAKE_BINARY_DIR}
            BUILD missing
            BASIC_SETUP
            )

    set(CONAN_CMAKE_FILE_PATH ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

    include(${CONAN_CMAKE_FILE_PATH})

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
set(SRC_FILES src/hashring/hashring.cpp src/hashring/hash/md5.cpp)


set_property(SOURCE ${SWIG_FILES} PROPERTY CPLUSPLUS ON)

set(TARGET_MODEL_NAME Hashring)

SET_SOURCE_FILES_PROPERTIES(${SWIG_FILES} PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(${SWIG_FILES} PROPERTIES SWIG_FLAGS "-includeall")


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

set(TARGET_LIB_OUTPUT_DIR lib)

function(_SWIG_LAN TARGET_LANGUAGE)
    capitalize(LAN ${TARGET_LANGUAGE})
    string(TOLOWER "${TARGET_LANGUAGE}" lowercase_language)
    set(SWIG_MODEL_NAME ${TARGET_MODEL_NAME}${LAN})


    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${TARGET_LIB_OUTPUT_DIR}/${TARGET_LANGUAGE})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${TARGET_LIB_OUTPUT_DIR}/${TARGET_LANGUAGE})
    set(CMAKE_SWIG_OUTDIR ${CMAKE_SOURCE_DIR}/${TARGET_LIB_OUTPUT_DIR}/${TARGET_LANGUAGE})

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


