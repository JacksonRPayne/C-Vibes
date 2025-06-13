py update_compile_commands.py
gcc -c src\main.c src\glad.c -Wall
gcc -o main.exe main.o glad.o -lglfw3dll -lopengl32 -Wall
del main.o
del glad.o
main.exe
