# somedate this may work as c++17
CONFIG += c++1z
# ewww, hacks if the above stops working, gcc and clang only
#QMAKE_CXXFLAGS += -std=c++17
#QMAKE_CFLAGS += -std=c17

INCLUDEPATH += ../common-cpp

QT += widgets gui 3dcore

HEADERS = main_window.hpp \
	gl_widget.hpp \
	gfx.hpp \
	../common-cpp/fox/counter.hpp

SOURCES = main.cpp \
	main_window.cpp \
	gl_widget.cpp \
	gfx.cpp \
	../common-cpp/fox/counter.cpp

RESOURCES = qt5_2d_test.qrc

