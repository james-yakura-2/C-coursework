all: clean EditDistance run

clean:
	rm -rf EditDistance *.o

EditDistance: 
	g++ -c Main.cpp ED.cpp
	g++ Main.o ED.cpp -o EditDistance -lsfml-system

run:
	./EditDistance < endgaps7.txt