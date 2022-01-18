
#include "stdafx.h"



struct Task
{
	int number;
	int duration;
	char* executor;
	Task* next;
	Task(int n=0, int d=0, char* e=NULL)
	{
		number = n;
		duration = d;
		executor = _strdup(e);
		next = NULL;
	}
	Task*add_Task(Task*f);
	void print_Task(void);
};



int main()
{
	setlocale(LC_ALL, "rus");
	fstream input("input.txt");
	Task*first = NULL, *el;
	int n, d;
	cout.setf(ios::left);
	char s[20];
	input >> n;
	while (!input.eof())
	{
		input >> d >> s;
		el = new Task(n, d, s);
		first = el->add_Task(first);
		input >> n;
	}
	first->print_Task();
}
Task*Task::add_Task(Task*f)
{
	Task*prev = NULL, *ptr = f;
	if (!f)
	{
		f = this;
		return f;
	}
	while (ptr&&ptr->duration >duration)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (!prev)
	{
		next = f;
		f = this;
	}
	else
	{
		prev->next = this;
		next = ptr;
	}
	return f;
}
void Task::print_Task(void)
{
	Task*ptr = this;
	while (ptr)
	{
		cout.width(5);
		cout << ptr->number;
		cout.width(20);
		cout << ptr->executor;
		cout << ptr->duration << '\n';
		ptr = ptr->next;
	}
}