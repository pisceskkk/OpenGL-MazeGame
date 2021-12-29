OBJ_DIR = ../../obj
CFLAGS=-Wno-narrowing -g -DDEBUG

OBJECTS = key.o ground.o door.o wall.o star.o logo.o button.o

all : $(OBJECTS)
	@echo [INFO] models done!

%.o : %.cpp
	g++ $< -c -o $(OBJ_DIR)/$@ $(CFLAGS)