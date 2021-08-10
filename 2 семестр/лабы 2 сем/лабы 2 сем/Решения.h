
const regex DATEPATERN (R"(([0-2]?[0-9]|[3][0-1])/(0?[0-9]|1[0-2])/\d+)");

struct MyTime
{
	int hours;
	int minuts;

	MyTime() {}

	MyTime(int newHours, int newMinuts ) {
		hours = newHours;
		minuts = newMinuts;
	}
};

void printMatrix(float **matrix, int n, int m) {
	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << matrix[i][j]<<" ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void printMatrix(int **matrix, int n, int m) {
	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void enterMatrix(ifstream file, int** matrix, int n, int m) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			file >> matrix[i][j];
		}
	}
}
MyTime parseTime(string timeToString) {
	
	int hours  =  stoi(timeToString.substr(0, timeToString.find(':', 0)));
	int minuts =  stoi(timeToString.substr(timeToString.find(':', 0)+1));

	return MyTime(hours, minuts);
}
bool isWrongDate(string date) {	
	return !regex_match(date, DATEPATERN);
}

void lab_9()
{
	cout << "Лабораторная №9 (№8, рис. 9.11)" << endl << endl;
	

	ifstream input;
	input.open("input 9 lab.txt");
	if (!input.is_open())
	{
		cout << "Файл ввода для программы не найден !";
		input.close();
		return;
	}


	int n;
	input >> n;


	int **oldMatrix = new int*[n];
	float **newMatrix = new float* [n];
	for (int i = 0; i < n; i++)
	{
		oldMatrix[i] = new int[n];
		newMatrix[i] = new float[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j= 0; j < n; j++)
		{
			input >> oldMatrix[i][j];
		}
	}
	input.close();

	

	cout << endl << endl << "Полученная матрица:"<< endl;
	printMatrix(oldMatrix, n, n);


	int sum; 
	float count;
	for (float i = 0; i < n; i++)
	{
		for (float j = 0; j < n; j++)
		{

			sum = 0;
			count = 0;

			for (float innerI = 0; innerI < n; innerI++)
			{
				for (float innerJ = 0; innerJ < n; innerJ++)
				{
					if (  (i >= innerI 
						//|| (i/j == (1/2)/(sqrt(3)/2))
						|| (cos(i/j) <= cos(1/6))
						//|| (i + j <= (n+1)/2)
						) && j >= innerJ )
					{
						sum += oldMatrix[int (trunc(innerI))][int (trunc(innerJ))];
						count++;
					}
				}
			}
			if (count == 0)
			{
				count = 1;
			}
			newMatrix[int (trunc(i))][int (trunc(j))] = sum / count;

		}
	}


	cout << endl << endl << "Новая матрица:";
	printMatrix(newMatrix, n,n);


	ofstream resultFile("result 9 lab.txt", ios::out | ios::trunc);
	resultFile << "Новая матрица:";
	resultFile.precision(2+1);

	for (int i = 0; i < n; i++)
	{
		resultFile << endl;
		for (int j = 0; j < n; j++)
		{
			//printf("%.2f  ", newMatrix[i][j]);
			resultFile << newMatrix[i][j] << "  ";
		}
	}
	resultFile.close();
}

void lab_10()
{
	cout << "Лабораторная №10" << endl << endl;

	struct Agent
	{
		string surname;
		string name;
		string patronymic;

		int sum;
	};


	ifstream input("input 10 lab.txt");
	if (!input.is_open())
	{
		cout << "Файл ввода для программы не найден !";
		input.close();
		return;
	}

	unsigned int n;
	input >> n;
	
	//Agent *customers = new Agent[n];
	vector <Agent> customers;

	Agent currentAgent;
	bool isNewCustomer = true;
	unsigned int currentCustomerIndex;
	for (int i = 0; i < n; i++)
	{
		input >> currentAgent.surname;
		input >> currentAgent.name;
		input >> currentAgent.patronymic;


		currentCustomerIndex = 0;
		for  ( Agent agent : customers)
		{
			if ( agent.name == currentAgent.name &&
				 agent.surname == currentAgent.surname &&
				 agent.patronymic == currentAgent.patronymic
				) 
			{
				isNewCustomer = false;
				break;
			}
			currentCustomerIndex++;
		}

		if (isNewCustomer)
		{
			currentAgent.sum = 0;
			customers.push_back(currentAgent);
			currentCustomerIndex = customers.size()-1;
		}

		input >> currentAgent.sum;
		customers.at(currentCustomerIndex).sum += currentAgent.sum;
	}
	input.close();


	Agent intermediaryVar;
	for (int i = 0; i < (customers.size()-1) -1 ; i++)
	{
		for (int j = 0; j < (customers.size()-1) -1; j++)
		{
			if (customers.at(j).surname > customers.at(j+1).surname)
			{
				intermediaryVar = customers.at(j);
				customers.at(j) = customers.at(j + 1);
				customers.at(j + 1) = intermediaryVar;
			}
		}
	}


	ofstream result("result 10 lab.txt", ios::out | ios::trunc);
	for (Agent agent : customers)
	{
		result
			<< agent.surname << "  "
			<< agent.name << "  "
			<< agent.patronymic << "  "
			<< agent.sum << "  "
			<< endl
		;
	}
	result.close();
}

void lab_11()
{
	cout << "Лабораторная №11"<< endl << endl;

	
	struct WrongsDatesStack {

		string date;

		WrongsDatesStack* previous;

		WrongsDatesStack() {
			date = "";
			previous = NULL;
		};
		WrongsDatesStack(string newDate) {
			date = newDate;
			previous = NULL;
		}

		void add(WrongsDatesStack* newWrongDate) {
			
			if (previous != NULL)
			{
				previous->add(newWrongDate);
			}
			else {
				previous = newWrongDate;
			}
		}

		void del() {
			if (previous->previous != NULL)
			{
				previous->del();
			}
			else {
				previous = NULL;
			}
		}

		void print(ofstream& out) {

			if (previous != NULL) {
				previous->print(out);
			}
			out << endl << date;
		}

	};


	WrongsDatesStack wrongDates;
	int count = 0;


	ifstream in("input 11 lab.txt");
	if (!in.is_open())
	{
		cout << "Файл ввода для программы не найден !";
		in.close();
		return;
	}



	string newDate;
	do
	{
		in >> newDate;
		if (isWrongDate(newDate))
		{
			wrongDates.add(new WrongsDatesStack(newDate));
			count++;
		}

	} while (!in.eof());

	in.close();

	
	ofstream out("output 11 lab.txt", ios::out | ios::trunc);
	
	out << "Всего неправильных дат: " << count;
	wrongDates.print(out);

	out.close();
}

void lab_selection()
{
	cout << "Лабораторная \"Выборка\"" << endl << endl;


	struct good
	{
		string name;
		int price;

		good(string newName, int newPrice) {
			name = newName;
			price = newPrice;
		}
	};


	vector <good*> goods = {
	/*	new good("Молоко"  ,56),
		new good("Ряженка" ,38),
		new good("Творог"  ,105),
		new good("Сметана" ,92),
		new good("Кефир"   ,30)*/
	};


	ifstream input("input Selection lab.txt");
	if (!input.is_open()) {
		cout << "Не удалось открыть файл !";
		input.close();
		return;
	}

	int BUDGET;
	input >> BUDGET;

	string nameOfProduct;
	int priceOfProduct;
	do
	{
		input >> nameOfProduct;
		input >> priceOfProduct;

		goods.push_back( new good(nameOfProduct, priceOfProduct) );

	} while (!input.eof());
	
	input.close();


	int goodsAmount = goods.size();
	/*cout << goodsAmount;

	for (good *item : goods) {
		cout << endl << item->name;
	}*/
	bitset<16> maskOfSelection(pow(2,goodsAmount)-1);
	//cout << maskOfSelection;


	bitset<16> optimumSelectionInBinary (0);
	bitset<16> selection(0);
	int sumToSpend;
	int minChange = BUDGET;

	for (unsigned short selectionToBinary = 0; selectionToBinary <= maskOfSelection.to_ulong(); selectionToBinary++)
	{
		sumToSpend = 0;
		selection = selectionToBinary;
		//cout << endl << selection;

		for (int i = 0; i < selection.size(); i++ )
		{
			if (selection.test(i))
			{
				sumToSpend += goods.at(i)->price;
			}
		}
	
		if ((BUDGET - sumToSpend) >= 0 && (BUDGET - sumToSpend) < minChange)
		{
			//optimumSelectionInBinary = selection;
			minChange = BUDGET - sumToSpend;
		}
	}


	ofstream output("output Selection lab.txt", ios::out | ios::trunc);



	output << "Минимальная сдача:" << minChange;
	output << endl << endl << "Возможные максимизированный по бюджету список покупок:";
	int countOfpurchaiseList = 0;

	for (unsigned short selectionToBinary = 0; selectionToBinary <= maskOfSelection.to_ulong(); selectionToBinary++)
	{
		sumToSpend = 0;
		selection = selectionToBinary;

		for (int i = 0; i < selection.size(); i++)
		{
			if (selection.test(i))
			{
				sumToSpend += goods.at(i)->price;
			}
		}

		if ((BUDGET - sumToSpend) == minChange)
		{
			//optimumSelectionInBinary = selection;
			
			output << "\n\nСписок " << ++countOfpurchaiseList << ":" << endl;

			for (int i = 0; i < selection.size(); i++)
			{
				if (selection.test(i))
				{
					output << endl << goods.at(i)->name << ": " <<  goods.at(i)->price;
				}
			}
		}
	}

	output.close();
}

void lab_dateTime()
{
	cout << "Лабораторная \"Дата и время\" №11" << endl << endl;

	


	struct PersonTimeTable
	{
		string name;
		MyTime arrive;
		MyTime travelTime;
		MyTime reception;
		int minutsDiviation;


		PersonTimeTable(
			string newName, 
			MyTime newArrive, 
			MyTime newTravelTime,
			MyTime newReception
		) 
		{
			name = newName;
			arrive = newArrive;
			travelTime = newTravelTime;
			reception = newReception;

			minutsDiviation = (
				reception.hours * 60 + reception.minuts -
				(arrive.hours * 60 + arrive.minuts) -
				(travelTime.hours * 60 + travelTime.minuts)
			);
		}
	};


	ifstream input("input DateTime lab.txt");
	if (!input.is_open())
	{
		cout << "Файл ввода не открывается!";
		input.close();
		return;
	}

	vector< PersonTimeTable* > timeLog;


	string newName;
	MyTime newArrive;
	MyTime newTravelTime;
	MyTime newReception;
	string strBuffer;

	do
	{
		input >> newName;
		
		input >> strBuffer;
		newArrive = parseTime(strBuffer);

		input >> strBuffer;
		newTravelTime = parseTime(strBuffer);

		input >> strBuffer;
		newReception = parseTime(strBuffer);


		timeLog.push_back(
			new PersonTimeTable(newName, newArrive, newTravelTime, newReception)
		);

	} while (!input.eof());

	
	ofstream output("output DateTime lab.txt", ios::out | ios::trunc );

	output << "Пометки журнала посещаемости:";
	for (PersonTimeTable* person : timeLog) {
		
		if (person->minutsDiviation < 0 )
		{
			output << endl
				<< person->name << " опоздал на " 
				<< -(person->minutsDiviation) << " Минут !"
			;
		}

		if (person->minutsDiviation > 10)
		{
			output << endl 
				<< person->name << " пришёл раньше на "
				<< person->minutsDiviation << " Минут !"
			;
		}
	}
	
	

}



