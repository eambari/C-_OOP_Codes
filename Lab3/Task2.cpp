/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Worker {
private:
    char firstName[30];
    char lastName[30];
    int salary;
public:
    Worker(char * _firstName = "", char *_lastName = "", int _salary = 0){
        strcpy(firstName, _firstName);
        strcpy(lastName, _lastName);
        salary = _salary;
    }
    Worker(const Worker& w){
        strcpy(firstName, w.firstName);
        strcpy(lastName, w.lastName);
        salary = w.salary;
    }
    int getsalary(){
        return salary;
    }
    void setfirstName(char* _firstName){
        strcpy(firstName, _firstName);
    }
    void setlastName(char* _lastName){
        strcpy(lastName, _lastName);
    }
    void setsalary(int _salary){
        salary = _salary;
    }
    void print(){
        cout << firstName << " " << lastName << " " << salary << endl;
    }
};
class Factory {
private:
    Worker workers[100];
    int workersNumber;
public:
    Factory(){}
    Factory(int _workersNumber, Worker * _workers){
        workersNumber = _workersNumber;
        for(int i = 0; i < _workersNumber; i++){
            workers[i] = _workers[i];
        }
    }
    Factory(const Factory & f){
        workersNumber = f.workersNumber;
        for(int i = 0; i < f.workersNumber; i++){
            workers[i] = f.workers[i];
        }
    }
    void printWorkers(){
        cout<<"ALL WORKERS:"<<endl;
        for(int i = 0; i < workersNumber; i++){
            workers[i].print();
        }
    }
    void printWithSalary(int salary){
        cout<<"EMPLOYEES WITH SALARY "<<salary<<":"<<endl;
        for(int i = 0; i < workersNumber; i++){
            if(workers[i].getsalary() > salary) {
                workers[i].print();
            }
        }
    }
};
int main()
{
   int n, salary;
   char name[30], lastname[30];
   cin >> n;
   Worker workers[n];
   for(int i = 0; i < n; i++){
      cin>>name>>lastname>>salary;
      workers[i].setfirstName(name);
      workers[i].setlastName(lastname);
      workers[i].setsalary(salary);
   }
   cin>>salary;
    Factory f1(n, workers);
    f1.printWorkers();
    f1.printWithSalary(salary);
}