OBJ_DIR = ../../obj
CFLAGS=-Wno-narrowing -g -DDEBUG

OBJECTS = map.o

all : $(OBJECTS)
	@echo [INFO] models done!

%.o : %.cpp
	g++ $< -c -o $(OBJ_DIR)/$@ $(CFLAGS)