cmake_minimum_required(VERSION 3.0.0)
# cmake version 3.0.0 is needed for block comments, 2.8.11 was the previous
# min version
project(qt5_2d_test)

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
	find_package(Qt5Gui)
	
	set(QT_LIBS Qt5::Core Qt5::Widgets Qt5::Gui)
	
	set(VC_PREFIX "C:\\vclibs\\vclibs")
	
	set(LIBS ${LIBS} kernel32.lib)
	
	set(BOOST_LIBS ${BOOST_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libboost_program_options-vc141-mt-x64-1_68.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libboost_program_options-vc141-mt-gd-x64-1_68.lib")
	set(BOOST_LIBS ${BOOST_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libboost_system-vc141-mt-x64-1_68.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libboost_system-vc141-mt-gd-x64-1_68.lib")
	set(BOOST_LIBS ${BOOST_LIBS}
		optimized "C:\\vclibs\\vclibs\\lib\\libboost_filesystem-vc141-mt-x64-1_68.lib"
		debug "C:\\vclibs\\vclibs\\lib\\libboost_filesystem-vc141-mt-gd-x64-1_68.lib")
	
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
	find_package(Qt5Gui)
	
	if(APPLE)
		set(QT_LIBS -L/usr/local/opt/qt/lib Qt5::Core Qt5::Widgets Qt5::Gui)
		include_directories("/usr/local/opt/qt/include")
		include_directories("/usr/local/include")
		include_directories("/usr/local/include/eigen3")
	elseif(UNIX AND NOT APPLE)
		set(QT_LIBS Qt5::Core Qt5::Widgets Qt5::Gui)
		include_directories("/usr/include")
		include_directories("/usr/include/eigen3")
	elseif(MINGW OR MSYS)
		set(QT_LIBS -lmingw32 Qt5::Core Qt5::Widgets Qt5::Gui)
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
	main_window.hpp
	main_window.cpp
	gl_widget.hpp
	gl_widget.cpp
)
set(COMMON_FOX_SOURCE
	../common-cpp/fox/counter.hpp
	../common-cpp/fox/counter.cpp
)

set(CMAKE_AUTOMOC ON)
add_executable(${PROJECT_NAME} ${MAIN_SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${QT_LIBS} ${BOOST_LIBS})
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
