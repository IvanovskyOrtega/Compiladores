a.out: main.o Automata.o AFN.o AFD.o Estado.o Transicion.o Pruebas.o PruebasAFD.o PruebasAFN.o Subconjunto.o
	g++ main.o Automata.o AFN.o AFD.o Estado.o Transicion.o Pruebas.o PruebasAFD.o PruebasAFN.o Subconjunto.o -Wall
main.o: main.cpp
	g++ -c main.cpp -Wall
Automata.o: Automata.cpp
	g++ -c Automata.cpp -Wall
AFN.o: AFN.cpp
	g++ -c AFN.cpp -Wall
AFD.o: AFD.cpp
	g++ -c AFD.cpp -Wall
Estado.o: Estado.cpp
	g++ -c Estado.cpp -Wall
Pruebas.o: Pruebas.cpp
	g++ -c Pruebas.cpp -Wall
PruebasAFD.o: PruebasAFD.cpp
	g++ -c PruebasAFD.cpp -Wall
PruebasAFN.o: PruebasAFN.cpp
	g++ -c PruebasAFN.cpp -Wall
Transicion.o: Transicion.cpp
	g++ -c Transicion.cpp -Wall
Subconjunto.o: Subconjunto.cpp
	g++ -c Subconjunto.cpp -Wall
clean:
	rm main.o Automata.o AFN.o AFD.o Estado.o Transicion.o Pruebas.o PruebasAFD.o PruebasAFN.o Subconjunto.o a.out
run:
	./a.out
indent:
	indent main.cpp AFN.cpp AFD.cpp Estado.cpp Pruebas.cpp Transicion.cpp AFD.hpp AFN.hpp Transicion.hpp Estado.hpp Pruebas.hpp -linux
