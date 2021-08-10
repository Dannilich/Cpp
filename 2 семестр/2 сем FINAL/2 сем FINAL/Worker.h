struct Worker
{
	int id;
	string FIO;
	string address;
	string phoneNumber;
	string dateOfBirth;
	int experience;
	bool isUnemployed = true;

	Worker() {}

	Worker(
		int id,
		string FIO,
		string address,
		string phoneNumber,
		string dateOfBirth,
		int experience
	) 
	{
		this->id = id;
		this->FIO = FIO;
		this->address = address;
		this->phoneNumber = phoneNumber;
		this->dateOfBirth = dateOfBirth;
		this->experience = experience;
	}
};