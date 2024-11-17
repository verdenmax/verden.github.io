# 指定最低版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(QRReduction)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 查找源文件
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cc")

# 生成可执行文件
add_executable(QRReduction ${SOURCES})

# 设置可执行文件的输出目录
set_target_properties(QRReduction PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# 添加编译选项
target_compile_options(QRReduction PRIVATE -g -w -Wall -O2)

# 添加自定义目标运行可执行文件
add_custom_target(run
		COMMAND ${PROJECT_SOURCE_DIR}/bin/QRReduction
		DEPENDS QRReduction
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Running the QRReduction executable"
)
