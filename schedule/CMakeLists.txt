set(sch_src_files
    ${CMAKE_CURRENT_SOURCE_DIR}/schedule.c
)

set(CAKE_SRC_FILES ${CAKE_SRC_FILES} ${sch_src_files} CACHE INTERNAL "sch src files" FORCE)

# Add header file include directories
set(sch_header_dir
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(CAKE_INCLUDE_DIRS ${CAKE_INCLUDE_DIRS} ${sch_header_dir} CACHE PATH "data header DIR" FORCE)
