CC=g++
CPPFLAGS=$(shell sdl2-config --cflags) $(shell $(PKG_CONFIG) SDL2_image --cflags) $(EXTRA_CPPFLAGS) -std=c++11 -Wall -Wextra -DDEBUG
LDLIBS=$(shell sdl2-config --libs) $(shell $(PKG_CONFIG) SDL2_image --libs) -lGLEW $(EXTRA_LDLIBS)
EXTRA_LDLIBS?=-lGL -lGLU -lpng
PKG_CONFIG?=pkg-config
all: test

test:
	$(CC) $(CPPFLAGS) \
	main.cc \
	../src/debug.cc \
	../src/core.cc \
	../src/renderer.cc \
	../src/window.cc \
	../src/scene.cc \
	../src/camera.cc \
	../src//entity.cc \
	../src/resourcemanager.cc \
	../src/texturedatareader.cc \
	../src/imageloader.cc \
	../src/programdatareader.cc \
	../src/entitycreator.cc \
	../src/meshdatareader.cc \
	../src/stringutl.cc \
	-o test $(LDLIBS) 

clean:
	rm -f *.o test
.PHONY: all clean

