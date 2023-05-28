all: compile link

compile: 
	g++ -c main.cpp -I"D:\IF Make\Projects\SFML Files\libraries2\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ main.o -o main -L"D:\IF Make\Projects\SFML Files\libraries2\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	del -f main *.o