cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(FetchContent)

if (NOT TARGET solanaceae_util)
	FetchContent_Declare(solanaceae_util
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_util.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(solanaceae_util)
endif()

if (NOT TARGET solanaceae_plugin)
	FetchContent_Declare(solanaceae_plugin
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_plugin.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(solanaceae_plugin)
endif()

if (NOT TARGET solanaceae_contact)
	FetchContent_Declare(solanaceae_contact
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_contact.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(solanaceae_contact)
endif()

if (NOT TARGET p2prng)
	FetchContent_Declare(p2prng
		GIT_REPOSITORY https://github.com/Green-Sky/p2prng.git
		GIT_TAG master
	)
	FetchContent_MakeAvailable(p2prng)
endif()

add_subdirectory(./p2prngi)

if (NOT TARGET imgui)
	FetchContent_Declare(imgui
		GIT_REPOSITORY https://github.com/ocornut/imgui.git
		GIT_TAG 5d4126876bc10396d4c6511853ff10964414c776 # v1.92.1
		EXCLUDE_FROM_ALL
	)

	# imgui does not provide a cmake
	FetchContent_GetProperties(imgui)
	if(NOT imgui_POPULATED)
		FetchContent_MakeAvailable(imgui)

		add_library(imgui STATIC
			${imgui_SOURCE_DIR}/imgui.h
			${imgui_SOURCE_DIR}/imgui_internal.h

			${imgui_SOURCE_DIR}/imgui.cpp
			${imgui_SOURCE_DIR}/imgui_demo.cpp
			${imgui_SOURCE_DIR}/imgui_draw.cpp
			${imgui_SOURCE_DIR}/imgui_tables.cpp
			${imgui_SOURCE_DIR}/imgui_widgets.cpp
			${imgui_SOURCE_DIR}/imstb_rectpack.h
			${imgui_SOURCE_DIR}/imstb_textedit.h
			${imgui_SOURCE_DIR}/imstb_truetype.h

			${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.h
			${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
		)
		target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
		target_compile_features(imgui PUBLIC cxx_std_11)
		target_compile_definitions(imgui PUBLIC IMGUI_USE_WCHAR32)
	endif()
endif()

