LIB=src/lib/vector.cpp src/lib/basis.cpp src/lib/SINS.cpp

filereader:
		g++ src/test/filereader.cpp -o filereader.out
main:
		g++ src/main.cpp $(LIB) -o main.out
vectest:
		g++ src/test/vectest.cpp $(LIB) -o vectest.out 
progbartest:
		g++ src/test/progbartest.cpp $(LIB) -o progbartest.out
		
