cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

project(solanaceae)

add_executable(vcg_csv_to_cpp
	./solanaceae/vcg/csv_to_cpp.cpp
)
target_compile_features(vcg_csv_to_cpp PUBLIC cxx_std_20)

########################################

add_library(solanaceae_vcg
	./solanaceae/vcg/card.hpp
	./solanaceae/vcg/card.cpp

	./solanaceae/vcg/cards/easy_cards.hpp
	./solanaceae/vcg/cards/easy_cards.cpp

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

########################################

add_executable(test_abilities
	./solanaceae/vcg/test_abilities.cpp
)

target_link_libraries(test_abilities PUBLIC solanaceae_vcg)

