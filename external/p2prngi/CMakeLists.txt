cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

project(solanaceae)

# TODO: proper lib

add_library(solanaceae_p2prng INTERFACE
	./p2prng.hpp
)

target_include_directories(solanaceae_p2prng INTERFACE .)
target_compile_features(solanaceae_p2prng INTERFACE cxx_std_17)
target_link_libraries(solanaceae_p2prng INTERFACE
	solanaceae_util
	solanaceae_contact
	p2prng
)

########################################

