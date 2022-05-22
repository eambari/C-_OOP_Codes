/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<string.h>
using namespace std;

class ExistingBill{
public:
    void printMessage(){
        cout << "The bill already exists" << endl;
    }
};

class Bill{
private:
    char *billNr;
    int expense;
    char date[8];
    bool payed;

    void copy(const Bill& other){
        expense = other.expense;
        strcpy(date, other.date);
        payed = other.payed;
        billNr = new char [strlen(other.billNr)+1];
        strcpy(billNr, other.billNr);
    }
public:
    Bill(char * _nr = " ", int _expense = 0, char * _date = "", bool _payed = true){
        billNr = new char [strlen(_nr)+1];
        strcpy(billNr, _nr);
        expense = _expense;
        strcpy(date, _date);
        payed = _payed;
    }
    Bill(const Bill& other){
        copy(other);
    }
    Bill &operator=(const Bill& other){
        if(this!=&other){
            delete [] billNr;
            copy(other);
        }
        return *this;
    }
    bool operator==(Bill &other){
        return !strcmp(this->billNr, other.billNr);
    }
    friend ostream &operator<<(ostream &o, const Bill &other) {
        return o << other.billNr << "(" << other.date << ") - " << other.expense << endl;
    }
    bool getPayed() const{
        return this->payed;
    }
    char *getDate(){
        return date;
    }
    int getExpense(){
        return expense;
    }
};

class UserProfile{
private:
    char username[30];
    Bill billsArray[30];
    int size;
    void copy(const UserProfile& other){
        strcpy(username, other.username);
        size = other.size;
        for(int i = 0; i < other.size; i++){
            billsArray[i] = other.billsArray[i];
        }
    }
public:
    UserProfile(char *name = ""){
        strcpy(username, name);
        size = 0;
    }
    UserProfile(const UserProfile& other){
        copy(other);
    }
    UserProfile& operator +=(Bill &other){
        for(int i = 0; i < size; i++){
            if(billsArray[i]==other){
                throw(ExistingBill());
            }
        } billsArray[size++] = other;
        return *this;
    }
    friend ostream& operator<<(ostream& o, const UserProfile& c){
        o<<"Unpaid bills of user "<<c.username<<" are:"<<endl;
        for(int i = 0; i < c.size; i++){
            if(!c.billsArray[i].getPayed()){
                o << c.billsArray[i];
            }
        }
        return o;
    }

    int totalDue(int month, int year) {
        int totalsum=0;
        char str[8];
        int date=0;
        int s;
        for(int i=0; i<size; i++){
            date=0;
            strcpy(str,billsArray[i].getDate());
            for(int i=0; i<strlen(str); i++){
                s=0;
                if(str[i]=='.')
                    continue;
                s=str[i]-'0';
                date = date * 10 + s;
            }
            if(date/10000 == month)
                totalsum=totalsum+billsArray[i].getExpense();
        }
        return totalsum;
    }
};

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try{
                up += s;
            } catch(ExistingBill e){
                e.printMessage();
            }
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try{
                up += s;
            } catch(ExistingBill e){
                e.printMessage();
            };
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            try{
                up += s;
            } catch(ExistingBill e){
                e.printMessage();
            };
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}

