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
	using namespace containers;

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
	using namespace containers;

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
	using namespace containers;

	string input = " ";
	bst<char> b;
	
	while (true)
	{
		cout << "Input command add <chars> | rem <chars> | prev <chars> | next <chars> | search <chars> | print | stop \n";
		cin >> input;
		if (input == "add")
		{
			cin >> input;
			for (char c : input)
			{
				if (c != ' ')
					b.add(c);
			}
		}
		else if (input == "rem")
		{
			cin >> input;
			for (char c : input)
			{
				if (c != ' ')
					cout << "fetching(" << c << "') " << b.fetch(c) << endl;
			}
		}
		else if (input == "print")
		{
			cout << "\nsize() " << b.size() << endl;
			cout << "nodeCount() " << b.nodeCount() << endl;
			cout << "min() " << b.min() << endl;
			cout << "max() " << b.max() << endl;
			cout << "printing tree : \n";
			b.print();
			cout << endl;
		}
		else if (input == "next")
		{
			cin >> input;
			for (char c : input)
			{
				if (c != ' ')
					cout << "b.next('" << c << "') " << b.next(c) << endl;
			}
		}
		else if (input == "prev")
		{
			cin >> input;
			for (char c : input)
			{
				if (c != ' ')
					cout << "b.prev('" << c << "') " << b.prev(c) << endl << endl;
			}
		}
		else if (input == "search")
		{
			cin >> input;
			for (char c : input)
			{
				if (c != ' ')
					cout << "b.search('" << c << "') = " << b.search(c) << endl;
			}
		}
		else if (input == "stop" || input == "0")
			break;
		else
			cout << "UNKNOWN COMMAND: " << input << endl;
	}
}
