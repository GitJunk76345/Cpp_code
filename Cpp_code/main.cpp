#include <iostream>
#include <string>
#include <cstdlib>
#include "headers/containers.h"

/*
	class tester
*/

void playlifo(void);
void playfifo(void);
void playbst(void);

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
		cout << "1) lifo(stack)\n2) fifo(queue)\n3) bst(binary search tree)\n\n0) exit\n";
		cin >> ch;
		switch (ch)
		{
		case '1': playlifo(); break;
		case '2': playfifo(); break;
		case '3': playbst(); break;
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
void playbst(void)
{
	using namespace std;
	string dump;
	char ch;
	bst<char> b;

	getline(cin, dump);
	cout << "b.size() " << b.size() << endl;
	cout << "b.nodeCount() " << b.nodeCount() << endl;
	cout << "Insert Your chars to tree:\n";

	while ((ch = getchar()) != 10)
		b.add(ch);

	cout << "b.size() " << b.size() << endl;
	cout << "b.nodeCount() " << b.nodeCount() << endl;
	cout << "b.min() " << b.min() << endl;
	cout << "b.max() " << b.max() << endl;
	getline(cin, dump);
	while ((ch = getchar()) != 10)
	{
		cout << "b.search('" << ch << "') " << b.search(ch) << endl;
		cout << "b.next('" << ch << "') " << b.next(ch) << endl;
		cout << "b.prev('" << ch << "') " << b.prev(ch) << endl << endl;
	}
	cout << "print tree : \n";
	b.print();
	cout << endl;
}
