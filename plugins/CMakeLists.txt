cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

########################################

add_library(plugin_vcg MODULE
	./plugin_vcg.cpp
)
target_compile_features(plugin_vcg PUBLIC cxx_std_17)
set_target_properties(plugin_vcg PROPERTIES
	C_VISIBILITY_PRESET hidden
)
target_link_libraries(plugin_vcg PUBLIC
	solanaceae_vcg
	solanaceae_plugin
)

