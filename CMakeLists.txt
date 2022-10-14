
cmake_minimum_required(VERSION 3.10)

project(libarl)

include (ExternalProject)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (NOT PACKAGES_DIR)
  set(PACKAGES_DIR ${CMAKE_SOURCE_DIR}/packages)
  set(ENABLE_TESTING 1)


endif()

set (LIBVSC_DIR "${PACKAGES_DIR}/libvsc")

ExternalProject_Add(LibVSC
  PREFIX libvsc
  SOURCE_DIR ${LIBVSC_DIR}
  CMAKE_CACHE_ARGS
    -DPACKAGES_DIR:PATH=${PACKAGES_DIR}
    -DCMAKE_INTERPROCEDURAL_OPTIMIZATION:BOOL=${CMAKE_INTERPROCEDURAL_OPTIMIZATION}
    -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=${CMAKE_POSITION_INDEPENDENT_CODE}
    -DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DTESTING:BOOL=OFF
  )
 
#add_dependencies(Bitwuzla Cadical Btor2tools GMP)
#add_dependencies(Boolector Cadical Btor2tools GMP)


if(NOT WIN32)
  add_compile_options(-fPIC)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)



#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_subdirectory(src)

if (ENABLE_TESTING)
  # Testing is only enabled when libvsc is the top-level project
  enable_testing()

  add_subdirectory(test)
endif()


