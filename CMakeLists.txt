cmake_minimum_required(VERSION 3.29)
project(rsa)

set(CMAKE_CXX_STANDARD 20)

# 设置 GMP 位置（Apple Silicon / M 系列）
set(GMP_ROOT /opt/homebrew/opt/gmp)

include_directories(${GMP_ROOT}/include)
link_directories(${GMP_ROOT}/lib)

add_executable(rsa
		main.cpp
		rsa.cpp
		utils.cpp
		crypto.cpp
		file_ops.cpp
)

# 链接 GMP 库
target_link_libraries(rsa gmp gmpxx)