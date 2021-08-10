struct EmploymentContract
{
	int companyID;
	int workerID;
	string Date;

	EmploymentContract() {}

	EmploymentContract(
		int companyID,
		int workerID,
		string Date
	) 
	{
		this->companyID = companyID;
		this->workerID = workerID;
		this->Date = Date;
	}
};