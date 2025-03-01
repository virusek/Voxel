CC := x86_64-w64-mingw32-gcc

SRC_DIR := src
BUILD_DIR := bin
OBJ_DIR := $(BUILD_DIR)/obj
BIN = bin

CFLAGS := -I/usr/x86_64-w64-mingw32/include -MMD -MP -Wall
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments

CFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include -Ilib/stb

LDFLAGS := lib/cglm/libcglm.a lib/glad/src/glad.o lib/glfw/src/libglfw3.a -lm
LDFLAGS += -L/usr/x86_64-w64-mingw32/lib -lgdi32 -luser32 -lwinpthread

SRC  = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/**/*.c) $(wildcard $(SRC_DIR)/**/**/**/*.c)
OBJ  = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN)/game.exe

.PHONY: all clean

all: dirs libs game

libs:
	echo "Building CGLM"
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make
	echo "Building GLAD"
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
	echo "Building GLFW"
	cd lib/glfw && cmake -S . -DCMAKE_TOOLCHAIN_FILE=CMake/x86_64-w64-mingw32.cmake -G "Ninja" && ninja
	echo "Building NOISE"
	cd lib/noise && make
	echo "Finished building libraries"

dirs:
	mkdir -p ./$(BIN)
	mkdir -p ./$(OBJ_DIR)
	mkdir -p ./$(OBJ_DIR)/gfx

run: all
	$(TARGET)

game: $(OBJ)
	$(CC) --static -o $(TARGET) $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) --static -static-libgcc -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
