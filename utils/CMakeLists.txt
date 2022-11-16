set(utils_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/utils_list.c
)

set(CAKE_SRC_FILES ${CAKE_SRC_FILES} ${utils_src_files} CACHE INTERNAL "utils src files" FORCE)

# Add header file include directories
set(utils_header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(CAKE_INCLUDE_DIRS ${CAKE_INCLUDE_DIRS} ${utils_header_dir} CACHE INTERNAL "utils header DIR" FORCE)
