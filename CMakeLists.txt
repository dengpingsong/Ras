cmake_minimum_required(VERSION 3.29)
project(rsa_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(rsa_main
		main.cpp
		rsa.cpp
		utils.cpp
)

target_link_libraries(rsa_main gmp gmpxx)