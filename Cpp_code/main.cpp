#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "headers/containers.h"

/*
	class tester
*/

void playlifo(void);
void playfifo(void);
void playbst(void);
void playbststr(void);

int main(int argc, char *argv[])
{
	using namespace std;

	char ch;
	string dump;

	while (true)
	{
		system("CLS");
		cout << "Container toy - select type of container to play:\n\n";
		cout << "1) lifo(stack)\n2) fifo(queue)\n3) AVL bst(binary search tree)\n4) AVL with strings and files\n\n0) exit\n";
		cin >> ch;
		switch (ch)
		{
			case '1': playlifo(); break;
			case '2': playfifo(); break;
			case '3': playbst(); break;
			case '4': playbststr(); break;
			default: return EXIT_SUCCESS; break;
		}
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
	system("PAUSE");
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
	system("PAUSE");
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
void playbststr(void)
{
	using namespace std;
	using namespace containers;

	string input = " ";
	bst<string> b;

	while (true)
	{
		cout << "Input command: add <string> | rem <string> | prev <string> | next <string> |\n";
		cout << "search <string> | print | load <filename> | save <filename> | stop \n";
		cin >> input;
		if (input == "add")
		{
			cin >> input;
			b.add(input);
		}
		else if (input == "rem")
		{
			cin >> input;
			cout << "fetching(" << input << "') " << b.fetch(input) << endl;
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
			cout << "b.next('" << input << "') " << b.next(input) << endl;
		}
		else if (input == "prev")
		{
			cin >> input;
			cout << "b.prev('" << input << "') " << b.prev(input) << endl << endl;

		}
		else if (input == "search")
		{
			cin >> input;
			cout << "b.search('" << input << "') = " << b.search(input) << endl;
		}
		else if (input == "load") {
			cin >> input;
			ifstream file;
			file.open(input);
			if (file.is_open())
			{
				cout << "FILE " << input << " OPENED\n";
				int cnt = 0;
				for ( ; !file.eof() ; ++cnt)
				{
					file >> input;
					b.add(input);
				}
				cout << cnt << " strings loaded to bst from file\n";
			}
			else
				cout << "FILE " << input << " CANNOT BE OPENED\n";
			file.close();
		}
		else if (input == "save") {
			cin >> input;
			ofstream file;
			file.open(input, ios::out | ios::app);
			if (file.is_open())
			{
				cout << "FILE " << input << " OPENED\n";
				int cnt = 0;
				string maximum = b.max();
				for (input = b.min() ; input != maximum  ; ++cnt )
				{
					file << input << ' ';
					if(cnt % 10 == 0 && cnt != 0)
						file << '\n';
					input = b.next(input);	
				}
				file << input << ' ';
				if (cnt % 10 == 0 && cnt != 0)
					file << '\n';
				cout << cnt << " strings saved to file in lexicographic order\n";
			}
			else
				cout << "FILE " << input << " CANNOT BE OPENED\n";
			file.close();
		}
		else if (input == "stop" || input == "0")
			break;
		else
			cout << "UNKNOWN COMMAND: " << input << endl;
	}
}
