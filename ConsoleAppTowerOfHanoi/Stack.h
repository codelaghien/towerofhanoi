#pragma once
#include <string>
using namespace std;

class Stack
{
private:
	const int MAX_SIZE = 100;
	int _AvailableIndex = 0;
	int* _Stack;
	int _Count = 0;
public:
	Stack();
	~Stack();

	bool push(int n);
	bool pop(int* n);
	int peek();
	bool isEmpty();
	bool isFull();
	string getData();
	int getLength();
};

