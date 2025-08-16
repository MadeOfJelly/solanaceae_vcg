cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

project(solanaceae)

add_executable(vcg_csv_to_cpp
	./solanaceae/vcg/csv_to_cpp.cpp
)
target_compile_features(vcg_csv_to_cpp PUBLIC cxx_std_20)

########################################

add_library(solanaceae_vcg)

# TODO: split lib
target_sources(solanaceae_vcg
	PUBLIC
		./solanaceae/vcg/card.hpp
		./solanaceae/vcg/cards/easy_cards.hpp
		./solanaceae/vcg/cards/random.hpp
		./solanaceae/vcg/cards/predefined_decks.hpp
		./solanaceae/vcg/game_state.hpp

		./solanaceae/vcg/vcg.hpp

		./solanaceae/vcg/sp_gui_states.hpp
		./solanaceae/vcg/vcg_sp_gui.hpp
	PRIVATE
		./solanaceae/vcg/card.cpp
		./solanaceae/vcg/cards/easy_cards.cpp
		./solanaceae/vcg/cards/random.cpp
		./solanaceae/vcg/cards/predefined_decks.cpp
		./solanaceae/vcg/game_state.cpp

		./solanaceae/vcg/vcg.cpp

		./solanaceae/vcg/sp_gui_states.cpp
		./solanaceae/vcg/vcg_sp_gui.cpp
)

#function(cards2cpp faction)
#    add_custom_target(cards2cpp_${faction} ALL
#        vcg_csv_to_cpp ${CMAKE_CURRENT_SOURCE_DIR}/../res/${faction}.csv .
#        BYPRODUCTS ${faction}.hpp ${faction}.cpp
#        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../res/${faction}.csv
#    )

#    target_sources(solanaceae_vcg
#        PUBLIC
#            ${CMAKE_CURRENT_BINARY_DIR}/${faction}.hpp
#        PRIVATE
#            ${CMAKE_CURRENT_BINARY_DIR}/${faction}.cpp
#    )
#endfunction()

function(cards2cpp faction)
	# simple hack, since we write the files to the soruce tree
	if(NOT CMAKE_CROSSCOMPILING)
		add_custom_target(cards2cpp_${faction}
			vcg_csv_to_cpp ${CMAKE_CURRENT_SOURCE_DIR}/../res/${faction}.csv ${CMAKE_CURRENT_SOURCE_DIR}/solanaceae/vcg/cards
			BYPRODUCTS
				${CMAKE_CURRENT_SOURCE_DIR}/solanaceae/vcg/cards/${faction}.hpp
				${CMAKE_CURRENT_SOURCE_DIR}/solanaceae/vcg/cards/${faction}.cpp
			SOURCES
				${CMAKE_CURRENT_SOURCE_DIR}/../res/${faction}.csv
		)
	endif()

	target_sources(solanaceae_vcg
		PUBLIC
			${CMAKE_CURRENT_SOURCE_DIR}/solanaceae/vcg/cards/${faction}.hpp
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/solanaceae/vcg/cards/${faction}.cpp
	)
endfunction()

cards2cpp(aberrations)
cards2cpp(assassins)
cards2cpp(bandits)
cards2cpp(clerics)
cards2cpp(crafters)
cards2cpp(cultists)
#cards2cpp(easy_cards)
cards2cpp(farmers)
cards2cpp(invaders)
cards2cpp(junkies)
cards2cpp(mages)
cards2cpp(merchants)
cards2cpp(monsters)
cards2cpp(nobles)
cards2cpp(parasites)
#cards2cpp(supporters)
cards2cpp(thieves)

target_include_directories(solanaceae_vcg PUBLIC .)
target_compile_features(solanaceae_vcg PUBLIC cxx_std_20)
target_link_libraries(solanaceae_vcg PUBLIC
	solanaceae_util
	p2prng
	solanaceae_p2prng
	imgui
)

########################################

add_executable(vcg_test1
	./solanaceae/vcg/test1.cpp
)

target_link_libraries(vcg_test1 PUBLIC solanaceae_vcg)

########################################

if(SOLANACEAE_VCG_BUILD_TESTING)
	add_executable(vcg_test_abilities
		./solanaceae/vcg/test_abilities.cpp
	)

	target_link_libraries(vcg_test_abilities PUBLIC solanaceae_vcg)
	add_test(NAME vcg_test_abilities COMMAND vcg_test_abilities)

########################################

	add_executable(vcg_test_parse_all_cards
		./solanaceae/vcg/test_parse_all_cards.cpp
	)

	target_link_libraries(vcg_test_parse_all_cards PUBLIC solanaceae_vcg)
	add_test(NAME vcg_test_parse_all_cards COMMAND vcg_test_parse_all_cards)
endif()

