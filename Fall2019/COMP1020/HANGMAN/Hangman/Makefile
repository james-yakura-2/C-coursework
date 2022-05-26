CC=gcc
CFLAGS=-Wall --std=c99 -g
OBJECTS=main.o my_string.o vector.o
TESTOBJ=my_string.o unit_test.o test_def.o
ALL: string_driver unit_test

unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
unit_test.o: unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
vector.o: vector.c
	$(CC) $(CFLAGS) -c vector.c -o vector.o
clean:
	rm string_driver $(OBJECTS) unit_test $(TESTOBJ) 
