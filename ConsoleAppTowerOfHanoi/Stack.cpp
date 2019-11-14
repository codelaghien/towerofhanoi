#include "Stack.h"
#include <string> 
Stack::Stack() {
	_AvailableIndex = 0;
	_Stack = new int[MAX_SIZE];
	_Count = 0;
}
Stack::~Stack()
{
	delete[] _Stack;
}
bool Stack::push(int n)
{
	if (isFull()) return false;
	_Stack[_AvailableIndex] = n;
	_AvailableIndex++;
	_Count++;
	return true;
}
bool Stack::pop(int* n)
{
	if (isEmpty()) return false;
	_AvailableIndex--;
	_Count--;
	*n = _Stack[_AvailableIndex];
	return true;
}
int Stack::peek()
{
	if (isEmpty()) return 0;
	return _Stack[_AvailableIndex - 1];
}
bool Stack::isEmpty()
{
	return (_AvailableIndex == 0);
}
bool Stack::isFull()
{
	return (_AvailableIndex >= MAX_SIZE);
}
string Stack::getData()
{
	string st = "";
	for (int i = 0; i < _AvailableIndex; i++)
	{
		st += to_string(_Stack[i]) + " ";
	}
	return st;
}
int Stack::getLength()
{
	return _Count;
}