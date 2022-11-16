set(pool_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/pool.c
)

set(CAKE_SRC_FILES ${CAKE_SRC_FILES} ${pool_src_files} CACHE INTERNAL "pool src files" FORCE)

# Add header file include directories
set(pool_header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(CAKE_INCLUDE_DIRS ${CAKE_INCLUDE_DIRS} ${pool_header_dir} CACHE PATH "pool header DIR" FORCE)
