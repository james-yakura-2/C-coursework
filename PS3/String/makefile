all: clean KsGuitarSim run

clean:
	rm -f *.o KsGuitarSim

KsGuitarSim:
	g++ -c KsGuitarSim.cpp StringSound.cpp CircularBuffer.cpp
	g++ KsGuitarSim.o StringSound.o CircularBuffer.o -o KsGuitarSim -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

run:
	./KsGuitarSim
