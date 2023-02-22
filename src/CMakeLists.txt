
file(GLOB zuspec_arl_dm_SRC
  "*.h"
  "*.cpp"
  )

add_library(zsp-arl-dm SHARED ${zuspec_arl_dm_SRC})

target_include_directories(zsp-arl-dm PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${DEBUG_MGR_DIR}/src/include
    ${LIBVSC_DM_DIR}/src/include
    ${JSON_DIR}/include
    ${CMAKE_BINARY_DIR}/include
    "${vsc_dm_INCDIR}"
    "${debug_mgr_INCDIR}"
    )

target_link_directories(zsp-arl-dm PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    "${vsc_dm_LIBDIR}"
    "${debug_mgr_LIBDIR}"
    )
target_link_libraries(zsp-arl-dm
    vsc-dm
    debug-mgr)

install(TARGETS zsp-arl-dm
    DESTINATION lib
    EXPORT zsp-arl-dm-targets)



