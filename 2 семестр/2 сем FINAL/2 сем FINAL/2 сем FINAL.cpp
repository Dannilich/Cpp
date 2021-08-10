#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <vector>

using namespace std;

//#include "MyDate.h"
#include "Employer.h"
#include "Worker.h"
#include "EmploymentСontract.h"


int currentWorkerID;
int currentEmployerID;

bool sortPredicateOfWorkers(Worker* w1, Worker* w2) {
    return w1->FIO < w2->FIO;
}
bool sortPredicateOfEmploers(Employer* e1, Employer* e2) {
    return e1->name < e2->name;
}
void printWorker(Worker* w) { cout << endl << w->id << ": " << w->FIO; }
bool isUnemployedWorker(Worker* w) { return w->isUnemployed; }
void printUnemployedWorker(Worker* w) { if(isUnemployedWorker(w)) printWorker(w); }
void printEmployer(Employer* e) { cout << endl << e->id << ": " << e->name; }
bool isCurrentWorker(Worker* w) { return w->id == currentWorkerID; }
bool isCurrentEmploer(Employer* e) { return e->id == currentEmployerID; }

void main()
{
    setlocale(LC_ALL, "ru");


    ifstream inWorkers("inputWorkers.txt");
    if (!inWorkers.is_open())
    {
        cout << "Файл не открылся!";
        inWorkers.close();
        return;
    }
   
    vector < Worker *> workers;
    do
    {
        workers.emplace_back(new Worker());

        inWorkers >> workers.back()->id;
        inWorkers >> workers.back()->FIO;
        inWorkers >> workers.back()->address;
        inWorkers >> workers.back()->phoneNumber;
        inWorkers >> workers.back()->dateOfBirth;
        inWorkers >> workers.back()->experience;

    } while (!inWorkers.eof());
  /*  cout << endl << workers.front()->FIO;
    cout << endl << workers.back()->FIO;*/
    inWorkers.close();

    sort(workers.begin(), workers.end(), sortPredicateOfWorkers);
    //cout << endl << workers.front()->FIO;
    //cout << endl << workers.back()->FIO;


    ifstream inEmploers("inputEmploers.txt");
    if (!inEmploers.is_open())
    {
        cout << "Файл не открылся!";
        inEmploers.close();
        return;
    }
   
    vector < Employer*> employers;
    do
    {
        employers.emplace_back(new Employer());

        inEmploers >> employers.back()->id;
        inEmploers >> employers.back()->name;
        inEmploers >> employers.back()->address;
        inEmploers >> employers.back()->telephonNumber;
        inEmploers >> employers.back()->position;
        inEmploers >> employers.back()->salary;

    } while (!inEmploers.eof());

    inEmploers.close();

    sort(employers.begin(), employers.end(), sortPredicateOfEmploers);



    vector <EmploymentContract*> employed;
    
    char controlExitKey;
    int unemployedWorkersCount;
    do
    {
        system("cls");
        cout << "Заполнение трудовых договоров:" ;
        employed.emplace_back(new EmploymentContract());


        cout << endl << endl << endl << "Список свободных сотрудников:";
        for_each(workers.begin(), workers.end(), printUnemployedWorker);

        cout << endl << endl << "Выберете работника по коду:";
        cin >> currentWorkerID;
        
        auto findWorker{ find_if(workers.begin(), workers.end(), isCurrentWorker) };
        (*findWorker)->isUnemployed =  false;
        employed.back()->workerID = currentWorkerID;
        

        cout << endl << endl << endl << "Список Работодателей:";
        for_each(employers.begin(), employers.end(), printEmployer);

        cout << endl << endl << "Выберете работодателя по коду:";
        cin >> employed.back()->companyID;
        

        cout << endl << endl << endl << "Введите дату трудового договора: ";
        cin >> employed.back()->Date;


        unemployedWorkersCount = count_if(workers.begin(), workers.end(), isUnemployedWorker);

    
        cout << endl << endl << "для выхода из набора нажмите esc...";
        controlExitKey = _getch();

    } while (controlExitKey != 27 && unemployedWorkersCount != 0);

    system("cls");
    cout << "Заполнение завершено!";

    ofstream out("output.txt", ios::out | ios::trunc);

    out << "Списки трудоустроенных:" << endl;

    for (auto it_emploer = employers.begin(); it_emploer < employers.end(); it_emploer++)
    {
        out << endl << endl << (*it_emploer)->name << ":"<< endl;
        
        for (auto it_employeed = employed.begin(); it_employeed < employed.end(); it_employeed++)
        {
            if ((*it_emploer)->id == (*it_employeed)->companyID)
            {
                currentWorkerID = (*it_employeed)->workerID;
                auto findWorker{ find_if(workers.begin(), workers.end(), isCurrentWorker) };
                out << endl << (*findWorker)->FIO;
            }
           
        }
    }
    
}