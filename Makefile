# aagarwala; Agarwala, Anirudh

huffman.out: main.o classes.o
	g++ -Wall -g -o huffman main.o classes.o

main.o: main.cpp classes.h
	g++ -Wall -g -c main.cpp

classes.o: classes.cpp classes.h
	g++ -Wall -g -c classes.cpp

clean:
	rm -f main.o classes.o
