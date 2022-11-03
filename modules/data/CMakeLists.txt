set(data_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/data_rx.c
)

set(CAKE_SRC_FILES ${CAKE_SRC_FILES} ${data_src_files} CACHE FILEPATH "data src files" FORCE)

# Add header file include directories
set(data_header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(CAKE_INCLUDE_DIRS ${CAKE_INCLUDE_DIRS} ${data_header_dir} CACHE PATH "data header DIR" FORCE)
