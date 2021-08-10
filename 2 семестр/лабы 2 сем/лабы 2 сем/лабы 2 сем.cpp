#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <map>
#include <bitset>
#include <string>
#include <regex>
#include <clocale>
#include <math.h>

using namespace std;

#include "Решения.h"
#include <clocale>
//#define _CRT_SECURE_NO_WARNINGS


void main()
{
	setlocale(LC_ALL, "ru");


	vector<function<void()>> tasks;
	//tasks.emplace_back(bind(lab_9));
	//tasks.emplace_back(bind(lab_10));
	//tasks.emplace_back(bind(lab_11));
	//tasks.emplace_back(lab_selection);
	tasks.emplace_back(lab_dateTime);

	int i = 0;
	for (auto& task : tasks) {
		cout << "Задание № " << ++i  << endl
			 << "----------------------------------------"
			 << endl //<< endl
		;

		task();

		cout << endl 
			 << "========================================"
			 << endl << endl << endl
		;
	}

	
	//return 0;
}

