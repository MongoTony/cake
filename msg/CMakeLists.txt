set(msg_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/msg.c
)

set(CAKE_SRC_FILES ${CAKE_SRC_FILES} ${msg_src_files} CACHE INTERNAL "msg src files" FORCE)

# Add header file include directories
set(msg_header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(CAKE_INCLUDE_DIRS ${CAKE_INCLUDE_DIRS} ${msg_header_dir} CACHE PATH "msg header DIR" FORCE)
