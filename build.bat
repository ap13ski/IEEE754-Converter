rem MinGW-W64 v.8.1.0
windres resources.rc -o resources.o
g++ main.cpp converter.cpp clipboard.cpp time.cpp file.cpp resources.o -static -lgdi32 -luser32 -lkernel32 -lcomctl32 -lgcc -lstdc++ -mwindows

pause
