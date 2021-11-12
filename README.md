# Compilación

    gcc -o control control.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic