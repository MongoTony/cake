cmake_minimum_required(VERSION 3.16)

project(cake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(CAKE_SRC_FILES)
set(CAKE_HEADER_FILES)
set(CAKE_INCLUDE_DIRS)
# message(p00:"${CAKE_SRC_FILES}")

# message(p01:"${CAKE_HEADER_FILES}")
# 支持GDB
# set(CMAKE_BUILD_TYPE "debug")
set(CMKAE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -o0 -wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -o3 -wall")

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

# 设置预编译宏
add_compile_definitions(TEST_MODE)

# Add block directories
add_subdirectory(modules)
add_subdirectory(main)
add_subdirectory(utils)
add_subdirectory(schedule)
add_subdirectory(pool)
add_subdirectory(msg)

include_directories(${CAKE_INCLUDE_DIRS})

# Target
add_executable(cake ${CAKE_SRC_FILES})

# 添加连接库
target_link_libraries(cake pthread)