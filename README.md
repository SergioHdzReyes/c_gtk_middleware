# Compilación

    gcc -o control control.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
    gcc -o game game.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

    ./control
    ./game
    
Ejemplo de funcionamiento:
https://www.youtube.com/watch?v=xu9NZHqS77U
