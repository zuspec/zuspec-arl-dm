
file(GLOB zuspec_arl_dm_SRC
  "*.h"
  "*.cpp"
  )

add_library(zuspec-arl-dm SHARED ${zuspec_arl_dm_SRC})

target_include_directories(zuspec-arl-dm PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${DEBUG_MGR_DIR}/src/include
    ${LIBVSC_DM_DIR}/src/include
    ${CMAKE_BINARY_DIR}/include
    )

target_link_directories(zuspec-arl-dm PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    )
target_link_libraries(zuspec-arl-dm
    vsc-dm
    debug-mgr)

add_dependencies(zuspec-arl-dm LibVSC-DM DebugMgr)

add_library(zuspec-arl-dm_static STATIC ${zuspec_arl_dm_SRC})

target_include_directories(zuspec-arl-dm_static PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/include
    ${DEBUG_MGR_DIR}/src/include
    ${LIBVSC_DM_DIR}/src/include
    ${CMAKE_BINARY_DIR}/include
    )

target_link_directories(zuspec-arl-dm_static PRIVATE
    ${CMAKE_BINARY_DIR}/lib
    ${CMAKE_BINARY_DIR}/lib64
    )

add_dependencies(zuspec-arl-dm_static LibVSC-DM DebugMgr)

install(TARGETS zuspec-arl-dm_static
    DESTINATION lib
    EXPORT zuspec-arl-dm-targets)

