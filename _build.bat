rem MinGW resource compiler
windres resources.rc -o resources.o
g++ main.cpp converter.cpp clipboard.cpp time.cpp file.cpp resources.o -static -lgdi32 -luser32 -lkernel32 -lcomctl32 -lgcc -lstdc++ -mwindows -o ieee754_converter_x64.exe

del *.o

pause