main: main.o matrix.o methods.o
	g++ -Wall -o $@ $^

main.o: main.cpp
	g++ -Wall -c -o $@ $<

matrix.o: matrix.cpp matrix.hpp
	g++ -Wall -c -o $@ $<

methods.o: methods.cpp methods.hpp
	g++ -Wall -c -o $@ $<

.PHONY:
	clean

clean:
	rm -f *~ *.o main 
