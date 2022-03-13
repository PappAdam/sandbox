OBJS = src/engine.c src/main.c src/game.c src/camera.c src/mapgen.c src/renderer.c src/hitbox.c src/gameobj.c

CC = gcc

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image

OBJ_NAME = sandbox

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	./$(OBJ_NAME)