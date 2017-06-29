#include <iostream>
#include <string>
#include <cstdlib>
#include "headers/containers.h"

/*
	class tester
*/

int main(int argc, char *argv[])
{
	using namespace std;
	lifo<char> l(16);

	cout << "l.getCapacity() " << l.getCapacity() << ", l.getHeight() " << l.getHeight() << ", l.getFree() " << l.getFree() << endl;
	cout << "Insert Your chars to stack:\n";
	while (!l.isFull() && l.push(getchar()) != 10) ;
	cout << "dumping stack : \n";
	dumpstack(l);
	cout << endl;
	system("PAUSE");
	return EXIT_SUCCESS;
}
