set(text_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/text.c
)

set(CAKE_SRC_FILES ${CAKE_SRC_FILES} ${text_src_files} CACHE INTERNAL "text src files" FORCE)

# Add header file include directories
set(text_header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(CAKE_INCLUDE_DIRS ${CAKE_INCLUDE_DIRS} ${text_header_dir} CACHE PATH "text header DIR" FORCE)
