graphic_windows_x86: ./graphic/graphic.c ./graphic/polygon.c
	gcc -c ./graphic/graphic.c -o ./build/bin/graphic.o
	gcc -c ./graphic/polygon.c -o ./build/bin/polygon.o


matrix_windows_x86: ./matrix/matrix.c
	gcc -c ./matrix/matrix.c -o ./build/bin/matrix.o


examples_windows_x86: ./examples/triangle_windows.c ./examples/cube_windows.c
	gcc -o ./build/triangle.exe ./examples/triangle_windows.c -lgdi32 -L./build/bin/ -lsw3d
	gcc -o ./build/cube.exe ./examples/cube_windows.c -lgdi32 -L./build/bin -lsw3d


archive:
	ar rcs ./build/bin/libsw3d.a ./build/bin/graphic.o ./build/bin/polygon.o ./build/bin/matrix.o