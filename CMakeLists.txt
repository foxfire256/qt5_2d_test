cmake_minimum_required(VERSION 3.0.0)
# cmake version 3.0.0 is needed for block comments, 2.8.11 was the previous
# min version
project(tbsg2)

# http://www.cmake.org/Wiki/CMake_Useful_Variables

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("../common-cpp")

# this assumes you are running cmake from a build directory in the source directory
# cmake .. -G "Visual Studio 15 2017 Win64"
if(MSVC)
	ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
	ADD_DEFINITIONS(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
	ADD_DEFINITIONS(-DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE)
	# WARNING: the following do not work with boost program_options
	#ADD_DEFINITIONS(-DBOOST_NO_RTTI)
	#ADD_DEFINITIONS(-DBOOST_NO_TYPEID)
	
	# /Oi enable intrinsic functions
	# /GR- disable RTTI, can't do with boost program_options
	# /std:c++17 or /std:c++14 are options
	SET(CMAKE_C_FLAGS "/MP ${CMAKE_C_FLAGS}")
	SET(CMAKE_CXX_FLAGS "/MP /std:c++latest /Oi ${CMAKE_CXX_FLAGS}")
	
	set(QT_DIR "C:\\Qt\\Qt5.11.1\\5.11.1\\msvc2017_64")
	# %QT_DIR%\bin must be in the PATH for this to work
	find_package(Qt5Core)
	find_package(Qt5Widgets)
	
	set(EDITOR_LIBS Qt5::Core Qt5::Widgets)
	
	set(VC_PREFIX "C:\\vclibs\\vclibs")
	
	set(LIBS ${LIBS} kernel32.lib)
	set(SDL2_LIBS
		optimized "C:\\vclibs\\vclibs\\lib\\SDL2main.lib"
		debug "C:\\vclibs\\vclibs\\lib\\SDL2maind.lib")
	set(SDL2_LIBS ${SDL2_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\SDL2.lib"
		debug "C:\\vclibs\\vclibs\\lib\\SDL2d.lib")
	set(FONT_LIBS ${SDL2_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\SDL2_ttf.lib"
		debug "C:\\vclibs\\vclibs\\lib\\SDL2_ttfd.lib")
	set(GUI_LIBS ${GUI_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\SDL2_image.lib"
		debug "C:\\vclibs\\vclibs\\lib\\SDL2_imaged.lib")
	
	set(BOOST_LIBS ${BOOST_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libboost_program_options-vc141-mt-x64-1_68.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libboost_program_options-vc141-mt-gd-x64-1_68.lib")
	set(BOOST_LIBS ${BOOST_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libboost_system-vc141-mt-x64-1_68.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libboost_system-vc141-mt-gd-x64-1_68.lib")
	set(BOOST_LIBS ${BOOST_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libboost_filesystem-vc141-mt-x64-1_68.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libboost_filesystem-vc141-mt-gd-x64-1_68.lib")
	
	set(SOUND_LIBS ${SOUND_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\SDL2_mixer.lib"
		debug "C:\\vclibs\\vclibs\\lib\\SDL2_mixerd.lib")
	set(SOUND_LIBS ${SOUND_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libvorbis.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libvorbisd.lib")
	set(SOUND_LIBS ${SOUND_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libogg.lib"
		debug "C:\\vclibs\\vclibs\\lib\\liboggd.lib")
	set(SOUND_LIBS ${SOUND_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\zlib.lib"
		debug "C:\\vclibs\\vclibs\\lib\\zlibd.lib")
	
	include_directories("C:\\vclibs\\vclibs\\include")
	include_directories("C:\\Qt\\Qt5.11.1\\5.11.1\\msvc2017_64\\include")
endif(MSVC)

if(MINGW OR MSYS OR UNIX OR APPLE)
	if(APPLE)
		set(CMAKE_PREFIX_PATH "/usr/local")
		set(CMAKE_INCLUDE_PATH "/usr/local/include")
		set(CMAKE_LIBRARY_PATH "/usr/local/lib")
	elseif(UNIX AND NOT APPLE)
		set(CMAKE_PREFIX_PATH "/usr")
		set(CMAKE_INCLUDE_PATH "/usr/include")
		set(CMAKE_LIBRARY_PATH "/usr/lib")
	elseif(MINGW OR MSYS)
		set(CMAKE_PREFIX_PATH "c:/msys64/mingw64")
		set(CMAKE_INCLUDE_PATH "c:/msys64/mingw64/include")
		set(CMAKE_LIBRARY_PATH "c:/msys64/mingw64/lib")
	endif(APPLE)
	
	find_package(Boost COMPONENTS program_options system filesystem REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
	set(BOOST_LIBS ${Boost_LIBRARIES})
	
	if(APPLE)
		set(LIBS ${LIBS} -L/usr/local/lib)
	elseif(UNIX AND NOT APPLE)
		set(LIBS ${LIBS})
	elseif(MINGW OR MSYS)
		set(LIBS ${LIBS} -lmingw32)
	endif(APPLE)
	
	set(SDL2_LIBS -lSDL2main -lSDL2)
	set(FONT_LIBS -lSDL2_ttf)
	set(GUI_LIBS ${SDL2_LIBS} -lSDL2_image)
	set(SOUND_LIBS -lSDL2_mixer -lvorbis -logg -lz)
	
	if(APPLE)
		# If there are problems with qt5 on Apple run 'which qmake' and make sure
		# it is the correct one. Usually you have to run 'brew link qt5 --force'.
		# Anaconda causes problems too since it has qt4 and other libs.
		set(QT_DIR "/usr/local/opt/qt")
	elseif(UNIX AND NOT APPLE)
		# QT_DIR should already be defined
	elseif(MINGW OR MSYS)
		set(QT_DIR "c:/msys64/mingw64")
	endif(APPLE)

	find_package(Qt5Core)
	find_package(Qt5Widgets)
	
	if(APPLE)
		set(EDITOR_LIBS -L/usr/local/opt/qt/lib Qt5::Core Qt5::Widgets)
		include_directories("/usr/local/opt/qt/include")
		include_directories("/usr/local/include")
		include_directories("/usr/local/include/eigen3")
	elseif(UNIX AND NOT APPLE)
		set(EDITOR_LIBS Qt5::Core Qt5::Widgets)
		include_directories("/usr/include")
		include_directories("/usr/include/eigen3")
	elseif(MINGW OR MSYS)
		set(EDITOR_LIBS -lmingw32 Qt5::Core Qt5::Widgets)
		include_directories("c:/msys64/mingw64/include/eigen3")
	endif(APPLE)
	
	# better optimizations
	# -O3 still IEEE754 compliant
	# -Ofast not IEEE754 compliant, faster than -O3
	# -ffast-math not needed with -Ofast
	# -ftree-vectorize not sure how well this does
	# -mavx
	# -mavx2
	set(CMAKE_C_FLAGS_RELEASE "-Ofast")
	set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
	
	# force some better debugging
	# this should be gcc
	# WARNING: warnings are disabled
	if(NOT APPLE)
		set(CMAKE_C_FLAGS_DEBUG "-ggdb3 -Og")
		set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -Og -w")
	endif(NOT APPLE)
	# and this should be clang
	# WARNING: warnings are disabled on clang
	if(APPLE)
		set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
		set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -w")
	endif(APPLE)

	# enable C11/C++17 for gcc and clang
	set(EXTRA_CXX_FLAGS "-std=c++17 -Wno-deprecated-declarations -pipe -frtti")
	set(EXTRA_C_FLAGS "-std=c17 -Wno-deprecated-declarations -pipe -frtti")
	
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_FLAGS}")
	
	# pipe keeps compilation in memory
	set(CMAKE_LD_FLAGS "-pipe")
endif(MINGW OR MSYS OR UNIX OR APPLE)

set(MAIN_SOURCE
	main.cpp
	main_observer.hpp
	main_observer.cpp
	sdl_message_handler.hpp
	sdl_message_handler.cpp
)
set(COMMON_FOX_SOURCE
	../common-cpp/fox/counter.hpp
	../common-cpp/fox/counter.cpp
)
set(COMMON_EVENTS_SOURCE
	../common-cpp/events/console_writer.hpp
	../common-cpp/events/console_writer.cpp
	../common-cpp/events/message_base.hpp
	../common-cpp/events/message_info.hpp
	../common-cpp/events/message_error.hpp
	../common-cpp/events/manager_interface.hpp
	../common-cpp/events/manager.hpp
	../common-cpp/events/manager.cpp
	../common-cpp/events/message_framerate.hpp
	../common-cpp/events/message_keydown.hpp
	../common-cpp/events/message_keyup.hpp
	../common-cpp/events/message_mousebutton.hpp
	../common-cpp/events/message_mousemotion.hpp
	../common-cpp/events/message_mousewheel.hpp
	../common-cpp/events/message_resize.hpp
	../common-cpp/events/observer.hpp
	../common-cpp/events/observer.cpp
	../common-cpp/events/subject.hpp
	../common-cpp/events/subject.cpp
)

set(GUI_SOURCE
	gui/gfx_sdl.hpp
	gui/gfx_sdl.cpp
	gui/object.hpp
	gui/object.cpp
	gui/rectangle.hpp
	gui/rectangle.cpp
	gui/scene.hpp
	gui/scene_main.hpp
	gui/scene_main.cpp
	gui/button.hpp
	gui/button.cpp
	gui/message_box.hpp
	gui/message_box.cpp
	events/message_guibutton.hpp
	events/message_guimessagebox.hpp
	events/message_battle_start.hpp
	events/message_battle_done.hpp
	gui/scene_battle.cpp
	gui/scene_battle.hpp
	gui/scene_fonttest.cpp
	gui/scene_fonttest.hpp
	gui/scene_world.cpp
	gui/scene_world.hpp
	gui/gfx_config.hpp)
set(COMMON_FOX_GFX_SOURCE
	../common-cpp/fox/gfx/font_factory.cpp
	../common-cpp/fox/gfx/font_factory.hpp
	../common-cpp/fox/gfx/font_config.hpp
	../common-cpp/fox/gfx/font.hpp
	../common-cpp/fox/gfx/font.cpp
	../common-cpp/fox/gfx/font_texture.hpp
	../common-cpp/fox/gfx/font_texture.cpp
	../common-cpp/fox/gfx/font_variant.hpp
	../common-cpp/fox/gfx/texture_factory.cpp
	../common-cpp/fox/gfx/texture_factory.hpp
	../common-cpp/fox/gfx/texture_config.hpp
	../common-cpp/fox/gfx/texture.cpp
	../common-cpp/fox/gfx/texture.hpp
	)

set(SOUND_SOURCE
	events/message_playsound.hpp
	sound/sound_player.hpp
	sound/sound_player.cpp
	sound/sound_config.hpp
	sound/sound_factory.hpp
	sound/sound_factory.cpp
)
set(GCORE_SOURCE
	gcore/ammunition.hpp
	gcore/ammunition.cpp
	gcore/critter.hpp
	gcore/critter.cpp
	gcore/critter_template.hpp
	gcore/critter_factory.hpp
	gcore/critter_factory.cpp
	gcore/ai_faction.hpp
	gcore/ai_faction.cpp
	gcore/ai_unit.hpp
	gcore/ai_unit.cpp
	gcore/ai_habitation.hpp
	gcore/ai_habitation.cpp
	gcore/unit_order.hpp
	gcore/unit_order.cpp
	gcore/habitation_order.hpp
	gcore/habitation_order.cpp
	gcore/unit.hpp
	gcore/unit.cpp
	gcore/armor.hpp
	gcore/armor.cpp
	gcore/armor_template.hpp
	gcore/armor_template.cpp
	gcore/armor_factory.hpp
	gcore/armor_factory.cpp
	gcore/attack.hpp
	gcore/body_location.hpp
	gcore/body_part.hpp
	gcore/body_part.cpp
	gcore/weapon.hpp
	gcore/weapon.cpp
	gcore/weapon_factory.hpp
	gcore/weapon_factory.cpp
	gcore/world.hpp
	gcore/world.cpp
	gcore/world_square.hpp
	gcore/world_square.cpp
	gcore/owner.hpp
	gcore/owner.cpp
	gcore/ownable.hpp
	gcore/battle.hpp
	gcore/battle.cpp
	gcore/battlefield_square.hpp
	gcore/battlefield_square.cpp
	gcore/faction.hpp
	gcore/faction.cpp
	gcore/faction_template.hpp
	gcore/faction_template.cpp
	gcore/faction_factory.hpp
	gcore/faction_factory.cpp
	gcore/battle_stats.hpp
	gcore/battle_stats.cpp
	events/message_battle_start.hpp
	events/message_battle_done.hpp
	events/message_world_init_done.hpp
	events/message_world_init_start.hpp
	events/message_world_deinit_done.hpp
	events/message_world_deinit_start.hpp
	gcore/battlefield_square_type.hpp
	gcore/world_square_type.hpp
	gcore/habitation.hpp
	gcore/habitation.cpp
	gcore/backpack.hpp
	gcore/backpack.cpp
	gcore/wagon.hpp
	gcore/wagon.cpp
	gcore/storable.hpp
	gcore/storable.cpp
	gcore/storage.hpp
	gcore/storage.cpp
	gcore/food.hpp
	gcore/food.cpp
	)
set(CONFIG_EDITOR_SOURCE
	config_editor/main.cpp
	config_editor/main_window.hpp
	config_editor/main_window.cpp
	config_editor/armor_model.hpp
	config_editor/armor_model.cpp
)

add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${GUI_SOURCE} ${COMMON_FOX_GFX_SOURCE} ${GCORE_SOURCE} ${COMMON_FOX_SOURCE} ${COMMON_EVENTS_SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${GUI_LIBS} ${SDL2_LIBS} ${FONT_LIBS} ${BOOST_LIBS})

# Instruct CMake to run Qt moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
#add_executable(${PROJECT_NAME}_config_editor ${CONFIG_EDITOR_SOURCE})
#target_link_libraries(${PROJECT_NAME}_config_editor
#	${LIBS} ${EDITOR_LIBS} gcore)
#set(CMAKE_AUTOMOC OFF)


MESSAGE( STATUS "MINGW: " ${MINGW} )
MESSAGE( STATUS "MSYS: " ${MSYS} )
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "APPLE: " ${APPLE} )
MESSAGE( STATUS "INCLUDE_DIRECTORIES: " ${INCLUDE_DIRECTORIES} )
MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )
MESSAGE( STATUS "CMAKE_C_FLAGS_DEBUG: " ${CMAKE_C_FLAGS_DEBUG} )
MESSAGE( STATUS "CMAKE_C_FLAGS_RELEASE: " ${CMAKE_C_FLAGS_RELEASE} )
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG} )
MESSAGE( STATUS "CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE} )
get_target_property(QtCore_location Qt5::Core LOCATION)
MESSAGE( STATUS "QtCore_location: " ${QtCore_location})
get_target_property(QtWdigets_location Qt5::Widgets LOCATION)
MESSAGE( STATUS "QtWdigets_location: " ${QtWdigets_location})
