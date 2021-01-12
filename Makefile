AVLTree: avl.o 
	g++ -std=c++11 -o AVLTree avl.o

avl.o: avl.cpp avl.h
	g++ -std=c++11 -c avl.cpp

clean:
	 rm -f AVLTree avl.o 