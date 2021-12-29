ifeq ($(OS),Windows_NT)
EXECUTABLE=main.exe
else
EXECUTABLE=main
endif

SRC_DIR=src
OBJ_DIR=obj
TARGET_DIR=bin
LOG=log.txt

CFLAGS=-Wno-narrowing -g -DDEBUG

all:
	make -C $(SRC_DIR) && make -C $(OBJ_DIR)
	rm $(OBJ_DIR)/*.o
	@echo [INFO] Successfully built!

clean:
	rm $(OBJ_DIR)/*.o
	rm $(TARGET_DIR)/$(EXECUTABLE)
	rm $(TARGET_DIR)/$(LOG)

run:
	./$(TARGET_DIR)/$(EXECUTABLE)