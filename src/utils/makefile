OBJ_DIR = ../../obj
CFLAGS=-Wno-narrowing -g -DDEBUG

OBJECTS = vec.o camera.o material.o tools.o stb_image.o texture.o

all : $(OBJECTS)
	@echo [INFO] utils done!

%.o : %.cpp
	g++ $< -c -o $(OBJ_DIR)/$@ $(CFLAGS)