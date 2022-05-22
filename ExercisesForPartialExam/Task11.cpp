/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class InvalidDiscount{
    int value;
public:
    InvalidDiscount(int value = 0){
        this->value = value;
    }
    void printMessage(){
        cout << "Invalid discount value: " << value;
    }
};

class IceCream{
private:
    char *name;
    char ingridients[100];
    float price;
    int discount;
public:
    IceCream(char *name = "", char *ingridients = "", float price = 0.0){
        this->name = new char [strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->ingridients, ingridients);
        this->price = price;
        this->discount = 0;
    }
    IceCream(const IceCream &k)
    {
        this->discount=k.discount;
        this->name=new char [strlen(k.name)+1];
        strcpy(this->name,k.name);
        strcpy(this->ingridients,k.ingridients);
        this->price=k.price;
    }
    IceCream &operator=(const IceCream &other){
        this->name = new char [strlen(other.name)+1];
        strcpy(this->name, other.name);
        strcpy(this->ingridients, other.ingridients);
        this->price = other.price;
        this->discount = other.discount;
    }
    ~IceCream(){
        delete [] name;
    }
    friend ostream &operator<<(ostream &out, const IceCream &a){
        out<<a.name<<": ";
        out<<a.ingridients<<" ";
        out<<a.price<<" ";
        if(a.discount !=0)
            out << "(" << a.price * (100 - a.discount) / 100 << ")";
        return out;
    }
    IceCream &operator++(){
        discount+=5;
        return *this;
    }
    void setDiscount(int discount){
        if(discount <= 0 || discount >= 100){
            throw(InvalidDiscount(discount));
        }
        this->discount = discount;
    }
    void setName(char* name){
        delete [] this->name;
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
    }
    IceCream operator+(char *other){
        IceCream tmp(name,ingridients,price+10);
        char *charTmp = new char[strlen(name)+strlen(other)+4];
        strcpy(charTmp, name);
        strcat(charTmp, " + ");
        strcat(charTmp, other);
        tmp.setName(charTmp);
        delete [] charTmp;
        tmp.setDiscount(discount);
        return tmp;
    }
};
class IceCreamShop{
    char name[50];
    IceCream *iceCreams;
    int size;

    void copy(const IceCreamShop &other){
        strcpy(this->name, other.name);
        this->size = other.size;
        iceCreams = new IceCream [other.size];
        for(int i = 0; i < other.size; i++){
            this->iceCreams[i] = other.iceCreams[i];
        }
    }
public:
    IceCreamShop(char *name = " "){
        strcpy(this->name, name);
        iceCreams = new IceCream [0];
        size = 0;
    }
    IceCreamShop(const IceCreamShop &other){
        copy(other);
    }
    IceCreamShop &operator=(const IceCreamShop &other){
        if(this != &other){
            delete [] iceCreams;
            copy(other);
        }
        return *this;
    }
    IceCreamShop &operator+=(const IceCream &other){
        IceCream *tmp = new IceCream [size+1];
        for(int i = 0; i < size; i++){
            tmp[i] = iceCreams[i];
        }
        tmp[size++] = other;
        delete [] iceCreams;
        iceCreams = tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const IceCreamShop &c){
        out << c.name << endl;
        for(int i = 0; i < c.size; i++){
            out << c.iceCreams[i] << endl;
        }
        return out;
    }
};
int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
    cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR &lt;&lt;" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name, 100);
        cin.getline(ingr, 100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name, 100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "TESTING EXCEPTION" << endl;
        cin >> discount;
        try {
            ic1.setDiscount(discount);
        } catch (InvalidDiscount e){
            e.printMessage();
        }

    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
            cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }

    return 0;
}


