#include <iostream>
#include <string>
#include <cstdlib>
#include "headers/containers.h"

/*
	class tester
*/

void playlifo(void);
void playfifo(void);

int main(int argc, char *argv[])
{
	using namespace std;
	char ch;
	string dump;

	while (true)
	{
		system("CLS");
		//getline(cin, dump);
		cout << "Container toy - select type of container to play:\n\n";
		cout << "1) lifo(stack)\n2) fifo(queue)\n3) other(todo)\n\n0) exit\n";
		cin >> ch;
		switch (ch)
		{
		case '1': playlifo(); break;
		case '2': playfifo(); break;
		case '3': cout << "COMMING SOON\n"; break;
		default: return EXIT_SUCCESS; break;
		}
		system("PAUSE");
	}
}

void playlifo(void)
{
	using namespace std;
	string dump;
	int size;
	char ch;

	cout << "Set desired stack capacity: ";
	cin >> size;
	lifo<char> l(size);

	getline(cin, dump);
	cout << "l.getCapacity() " << l.getCapacity() << ", l.getHeight() " << l.getHeight() << ", l.getFree() " << l.getFree() << endl;
	cout << "Insert Your chars to stack:\n";
	
	while (!l.isFull() && (ch = getchar()) != 10)
		l.push(ch);
	
	cout << "l.getCapacity() " << l.getCapacity() << ", l.getHeight() " << l.getHeight() << ", l.getFree() " << l.getFree() << endl;
	cout << "dumping stack : \n";
	dumpstack(l);
	cout << "l.getCapacity() " << l.getCapacity() << ", l.getHeight() " << l.getHeight() << ", l.getFree() " << l.getFree() << endl;
}
void playfifo(void)
{
	using namespace std;
	string dump;
	char ch;
	fifo<char> f;

	getline(cin, dump);
	cout << "f.getLenght() " << f.getLenght() << endl;
	cout << "Insert Your chars to queue:\n";

	while ( (ch = getchar()) != 10)
		f.push(ch);

	cout << "f.getLenght() " << f.getLenght() << endl;
	cout << "dumping queue : \n";
	dumpqueue(f);
	cout << "f.getLenght() " << f.getLenght() << endl;
}
