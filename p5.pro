TARGET = p5
#TARGET will be the name of the executable

#don't change these
TEMPLATE = app
LANGUAGE = C++

#the important things here are that debugging is turned on (equivalent to -g)
#and that we're linking with opengl. warn_on means -Wall for gcc
QT += opengl
#Config += console
CONFIG += debug warn_on qt opengl console

#put all your .h files in here
HEADERS += Canvas.h \
	raytrace.h \
	control.h \
	vec3.h \
	fileio.h

FORMS	= control.ui

#put all your .cpp files in here
SOURCES += \
	Canvas.cpp \
	Main.cpp \
	raytrace.cpp \
	vec3.cpp \
	fileio.cpp

#qt will make a bunch of temporary files when it builds.
#this tells it to put these files out of the way so they
#don't clutter the directory
MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj
