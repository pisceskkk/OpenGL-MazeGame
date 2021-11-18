ifeq ($(OS),Windows_NT)
LDFLAGS=-lfreeglut -lopengl32 -lglu32 -lglew32 -Wl,--subsystem,windows
EXECUTABLE=main.exe
else
LDFLAGS=-lGL -lglut
EXECUTABLE=main
endif
TARGET_DIR = ../bin

OBJECTS = *.o

all : build
	@echo obj done!

build: $(OBJECTS)
	g++ $(OBJECTS) $(LDFLAGS) -o $(TARGET_DIR)/$(EXECUTABLE)