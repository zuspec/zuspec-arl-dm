
file(GLOB libarl_SRC
  "*.h"
  "*.cpp"
  )

add_library(arl SHARED ${libarl_SRC})

target_include_directories(arl PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${LIBVSC_DIR}/src/include
    ${CMAKE_BINARY_DIR}/include
    )

target_link_directories(arl PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    )

#target_link_libraries(arl
#        bitwuzla
#        boolector
#        btor2parser
#        cadical
#        gmp
#        )
add_dependencies(arl LibVSC)

add_library(arl_static STATIC ${libarl_SRC})

target_include_directories(arl_static PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${LIBVSC_DIR}/src/include
    ${CMAKE_BINARY_DIR}/include
    ${Boolector_INCLUDE_DIR}
    )

target_link_directories(arl_static PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    )

add_dependencies(arl_static LibVSC)

