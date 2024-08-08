cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_vcg
	./solanaceae/vcg/card.hpp
	./solanaceae/vcg/card.cpp

	./solanaceae/vcg/game_state.hpp
	./solanaceae/vcg/game_state.cpp

	./solanaceae/vcg/vcg.hpp
	./solanaceae/vcg/vcg.cpp

	./solanaceae/vcg/sp_gui_states.hpp
	./solanaceae/vcg/vcg_sp_gui.hpp
	./solanaceae/vcg/vcg_sp_gui.cpp
)

target_include_directories(solanaceae_vcg PUBLIC .)
target_compile_features(solanaceae_vcg PUBLIC cxx_std_20)
target_link_libraries(solanaceae_vcg PUBLIC
	solanaceae_util
	p2prng
	solanaceae_p2prng
	imgui
)

########################################

add_executable(test1
	./solanaceae/vcg/test1.cpp
)

target_link_libraries(test1 PUBLIC solanaceae_vcg)

