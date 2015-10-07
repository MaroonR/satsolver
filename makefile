satsol: main.o
	g++ -o satsol main.o

main.o: main.cpp
	g++ -c main.cpp -std=c++11

clean:
	rm *.o

zip: $(FILES)
	zip -r DavidJones-satsolver .
