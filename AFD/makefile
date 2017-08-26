a.out: main.o AFD.o Estado.o Transicion.o Pruebas.o
	g++ main.o AFD.o Estado.o Transicion.o Pruebas.o   -Wall
main.o: main.cpp
	g++ -c main.cpp -Wall
AFD.o: AFD.cpp
	g++ -c AFD.cpp -Wall
Estado.o: Estado.cpp
	g++ -c Estado.cpp -Wall
Pruebas.o: Pruebas.cpp
	g++ -c Pruebas.cpp -Wall
Transicion.o: Transicion.cpp
	g++ -c Transicion.cpp -Wall
clean:
	rm main.o AFD.o Estado.o Transicion.o Pruebas.o a.out
run:
	./a.out
indent:
	indent main.cpp AFD.cpp Estado.cpp Pruebas.cpp Transicion.cpp bresenham.hpp Transicion.hpp Estado.hpp Pruebas.hpp -linux
