/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class RealEstate{
protected:
    char *address;
    int area;
    int price;

    void copy(const RealEstate &other){
        address = new char[strlen(other.address)+1];
        strcpy(address, other.address);
        area = other.area;
        price = other.price;
    }
public:
    RealEstate(char *a = " ", int r = 0, int p = 0){
        address = new char[strlen(a)+1];
        strcpy(address, a);
        area = r;
        price = p;
    }
    RealEstate(const RealEstate &other){
        copy(other);
    }
    RealEstate &operator =(const RealEstate &other){
        if(this != &other){
            delete[] address;
            copy(other);
        }
        return *this;
    }
    int priceArea(){
        return price*area;
    }
    void print(){
        cout << address << ", Kvadratura: " << price << ", Cena po Kvadrat: " << area << endl;
    }
    float estateTax(){
        return priceArea()*0.05;
    }
    friend istream &operator>>(istream &i, RealEstate &r){
        return i >> r.address >> r.price >> r.area;
    }
    ~RealEstate(){
        delete [] address;
    }
    char *getAddress(){
        return address;
    }
};
class Villa: public RealEstate{
private:
    float tax;
public:
    Villa(char *a = " ", int r = 0, int p = 0, int taxe = 10): RealEstate(a, r, p){
        tax = taxe;
    }
    Villa(RealEstate &tmp, int taxe): RealEstate(tmp){
        tax = taxe;
    }
    void print(){
        cout << address << ", Kvadratura: " << price << ", Cena po Kvadrat: " << area << ", Danok na luksuz: " << tax << endl;
    }
    float estateTax(){
        return priceArea()*(0.05+tax/100);
    }
    friend istream &operator>>(istream &i, Villa &r){
        return i >> r.RealEstate::address >> r.RealEstate::price >> r.RealEstate::area >> r.tax;
    }
};
int main(){
    RealEstate re;
    Villa v;
    cin >> re;
    cin >> v;
    re.print();
    cout << "Danok za: " << re.getAddress() << ", e: " << re.estateTax() << endl;
    v.print();
    cout << "Danok za: " << v.getAddress() << ", e: " << v.estateTax() << endl;
    return 0;
}
