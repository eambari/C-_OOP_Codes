/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;

class InvalidDateException{
    int day, month, year;
public:
    InvalidDateException(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    void printError(){
        cout << "Invalid Date " << day << "/" << month << "/" << year << endl;
    }
};
class NotSupportedCurrencyException{
    char currency[4];
public:
    NotSupportedCurrencyException(char *currency = ""){
        strcpy(this->currency, currency);
    }
    void printError(){
        cout << currency << " is not a supported currency" << endl;
    }
};
class Transaction{
protected:
    int day, month, year;
    double amount;
    static double eur, usd;
public:
    Transaction(int day = 0, int month = 0, int year = 0, double amount = 0.0){
        if(day > 31 || day < 1 || month > 12 || month < 1){
            throw(InvalidDateException(day,month,year));
        }
        this->day = day;
        this->month = month;
        this->year = year;
        this->amount = amount;
    }
    virtual void print() = 0;
    virtual double toDenars() = 0;

    static void setEUR(double i){
        eur = i;
    }
    static void setUSD(double i){
        usd = i;
    }
    double getAmount(){
        return amount;
    }
};
double Transaction::eur = 61.0;
double Transaction::usd = 50.0;

class DenarsTransaction: public Transaction{
public:
    DenarsTransaction(int day = 0, int month = 0, int year = 0, double amount = 0.0): Transaction(day, month, year, amount){}
    void print () override {
        cout << day << "/" << month << "/" << year << " " << amount << " MKD";
    }
    double toDenars () override{
        return amount;
    }
    DenarsTransaction *operator=(DenarsTransaction *tmp){
        day = tmp->day;
        month = tmp->month;
        year = tmp->year;
        amount = tmp->amount;
    }
};
class ForeignCurrencyTransaction: public Transaction{
private:
    char currency[4];
public:
    ForeignCurrencyTransaction(int day = 0, int month = 0, int year = 0, double amount = 0.0, char* currency = " "): Transaction(day,month,year, amount){
        if(strcmp(currency, "EUR") == 0 || strcmp(currency, "USD") == 0){
            strcpy(this->currency, currency);
        } else {
            throw(NotSupportedCurrencyException(currency));
        }

    }
    void print () override {
        cout << day << "/" << month << "/" << year << " " << amount << (strcmp(currency,"EUR") == 0 ? " EUR" : " USD");
    }
    double toDenars () override{
        return amount * ((strcmp(currency,"EUR") == 0) ? eur : usd);
    }
    ForeignCurrencyTransaction &operator=(ForeignCurrencyTransaction *tmp){
        day = tmp->day;
        month = tmp->month;
        year = tmp->year;
        amount = tmp->amount;
        strcpy(this->currency, tmp->currency);
    }
};
class Account{
private:
    Transaction **transactions;
    int size;
    char number[15];
    double start;
public:
    Account(char *nr = "", double str = 0.0){
        size = 0;
        transactions = new Transaction* [0];
        strcpy(number, nr);
        start = str;
    }
    ~Account(){
        delete [] transactions;
    }
    Account &operator +=(Transaction* other){
        Transaction **tmp = new Transaction * [size+1];
        for(int i = 0; i < size; i++){
            tmp[i] = transactions[i];
        }
        tmp[size++] = other;
        delete [] transactions;
        transactions = tmp;
        return *this;
    }
    void reportInDenars(){
        double total = 0.0;
        for(int i = 0; i < size; i++) {
            total+=transactions[i]->toDenars();
        }
        cout << "The user with account number: " << number << " has account balance of: "
             << start+total << " MKD" << endl;
    }
    void printTranscations(){
        for(int i = 0; i < size; i++){
            transactions[i]->print();
            cout << endl;
        }
    }
};
int main () {

    Account s ("300047024112789",1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta [3];

    cin>>n;
    cout<<"===TRANSACTION ADDITION AND EXCEPTION HANDLING==="<<endl;
    for (int i=0;i<n;i++){
        cin>>tip>>den>>mesec>>godina>>iznos;
        if (tip==2){
            cin>>valuta;
            try {
                Transaction *t = new ForeignCurrencyTransaction(den, mesec, godina, iznos, valuta);
                s += t;
            }
            catch(NotSupportedCurrencyException e){
                e.printError();
            }
            catch(InvalidDateException e){
                e.printError();
            }
        }
        else {
            try {
                Transaction *t = new DenarsTransaction(den, mesec, godina, iznos);
                s += t;
            }
            catch(InvalidDateException e){
                e.printError();
            }
        }
    }
    cout<<"===TRANSACTIONS LIST==="<<endl;
    s.printTranscations();
    cout<<"===TRANSACTIONS REPORT IN DENARS==="<<endl;
    s.reportInDenars();


    cout<<"\n===CHANGE OF THE COURSE OF THE EUR AND USD===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transaction::setEUR(newEUR);
    Transaction::setUSD(newUSD);
    cout<<"===TRANSACTIONS REPORT IN DENARS==="<<endl;
    s.reportInDenars();




    return 0;
}
