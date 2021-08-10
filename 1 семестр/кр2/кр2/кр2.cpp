#include <iostream>
#include <fstream>
#include <string>

#include <bitset>
using namespace std;


bitset<16> bitExchange(bitset<16> binX, bitset<16> binY, int n);
string bitToStr(bitset<16> bitX);

int main()
{
	setlocale(LC_ALL, "ru");

	unsigned int n;
	cout << "Введите n: "; cin >> n;
	cout << endl;

	int x,y;
	cout << "Введите х: ";cin  >> x;
	cout << endl;
	cout << "Введите y: "; cin >> y;
	cout << endl;

	bitset<16> binX = bitset<16>(x);
	bitset<16> binY = bitset<16>(y);

	ofstream fileOut("Результаты.txt");
	fileOut << "n = " << n << endl ;

	fileOut << "Исходный двоичный вид:";
	fileOut << endl << "x: " << bitToStr(binX);
	fileOut << endl << "y: " << bitToStr(binY);
	fileOut << endl << endl;


	fileOut << "Итоговое преобразрование Х:" << endl <<
		bitToStr(bitExchange(x, y, n));
	/*fileOut << endl << endl;*/
}

bitset<16> bitExchange(bitset<16> binX, bitset<16> binY, int n) {

	for (unsigned int i = 0; i < n; i++)
	{
		binX[i] = binY[i];
	}

	return binX;
}

string bitToStr(bitset<16> bitX) {

	string reversedBit = bitX.to_string();
	string bit = "";

	for (int i = 16; i > 0; i--)
	{
		bit.append(reversedBit.substr(i, 1));
	}
	
	return bit;
}
