OBJ_DIR = ../obj
CFLAGS=-Wno-narrowing -g -DDEBUG

all: main.o
	make -C utils && make -C models
	@echo [INFO] src done!

main.o : main.cpp
	g++ main.cpp -c -o $(OBJ_DIR)/main.o $(CFLAGS)