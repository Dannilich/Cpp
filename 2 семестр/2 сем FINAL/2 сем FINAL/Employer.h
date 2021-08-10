//#include <string>
//using namespace std

struct Employer
{
	int id;
	string name;
	string address;
	string telephonNumber;
	string position;
	int salary;

	Employer() {}

	Employer(
		int id, 
		string name,
		string address,
		string telephonNumber,
		string position,
		int salary
	)
	{
		this->id = id;
		this->name = name;
		this->address = address;
		this->telephonNumber = telephonNumber;
		this->position = position;
		this->salary = salary;
	}
};