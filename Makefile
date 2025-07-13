CC = cc
CFLAGS = -gdwarf-4 -Wall
IFLAGS = -I/opt/homebrew/Cellar/raylib/5.5/include -I/opt/homebrew/Cellar/sdl3/3.2.8/include -I/opt/homebrew/Cellar/sdl3_image/3.2.4/include -I/opt/homebrew/Cellar/sdl3_ttf/3.2.2/include -I/opt/homebrew/Cellar/cglm/0.9.6/include
LFLAGS = -gdwarf-4 -L/opt/homebrew/Cellar/raylib/5.5/lib -L/opt/homebrew/Cellar/sdl3/3.2.8/lib -L/opt/homebrew/Cellar/sdl3_image/3.2.4/lib -L/opt/homebrew/Cellar/sdl3_ttf/3.2.2/lib -L/opt/homebrew/Cellar/cglm/0.9.6/lib

build:
	${CC} ${CLFAGS} ./src/*.c ${IFLAGS} ${LFLAGS} -lSDL3 -lSDL3_image -lSDL3_ttf -lcglm -lraylib -o ./build/main

run:
	./build/main

clean:
	rm -rf ./build/*
