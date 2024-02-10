SRC := .\src
LIB := .\lib
TARGET := .\target

CC := gcc
CFLAGS := \
	-Ilib\SDL2\include \
	-Llib\SDL2\lib\x64 \
	-Ilib\SDL2_ttf\include \
	-Llib\SDL2_ttf\lib\x64 \
	-Ilib\SDL2_image\include \
	-Llib\SDL2_image\lib\x64 \
	-O3 -m64 -Wall -Werror -Wpedantic -s \
	-lmingw32 \
	-lSDL2 \
	-lSDL2main \
	-lSDL2_ttf \
	-lSDL2_image

.PHONY: all clean ship

all: clean $(TARGET)\main.exe

$(TARGET)\main.exe: $(SRC)\main.c
	$(CC) -o $@ $^ $(CFLAGS)
	copy /b $(LIB)\SDL2\lib\x64\SDL2.dll $(TARGET)\SDL2.dll 1>nul
	copy /b $(LIB)\SDL2_ttf\lib\x64\SDL2_ttf.dll $(TARGET)\SDL2_ttf.dll 1>nul
	copy /b $(LIB)\SDL2_image\lib\x64\SDL2_image.dll $(TARGET)\SDL2_image.dll 1>nul

clean:
	del /q $(TARGET)\*.exe 2>nul
	del /q $(TARGET)\*.dll 2>nul

ship:
	windres $(SRC)\main.rc -O coff $(TARGET)\main.res
	$(CC) -o $(TARGET)\main.exe $(SRC)\main.c $(TARGET)\main.res $(CFLAGS)
	del /q $(TARGET)\main.res 2>nul
