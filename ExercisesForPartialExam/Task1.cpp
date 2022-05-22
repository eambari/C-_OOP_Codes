/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class AlcoholicDrink{
protected:
    char name[100];
    char country[100];
    float percent;
    float base;
    static int discount;
public:
    AlcoholicDrink(float percent = 0.0, char *name = " ", char *country = " ", float base = 0.0){
        this->percent = percent;
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->base = base;
    }
    virtual float computePrice() = 0;

    bool operator<(AlcoholicDrink *b){
        return computePrice() < b->computePrice();
    }
    static void changeDiscount(int d){
        discount = d;
    }
    static void total(AlcoholicDrink** ad, int n){
        float max = 0.0;
        for(int i = 0; i < n; i++){
            max += ad[i]->computePrice();
        }
        cout << "Total price: " << max << endl;
        cout << "Total price with discount: " << (max-(max*(float(discount)/100))) << endl;
    }
};
int AlcoholicDrink::discount = 5;

class Beer: public AlcoholicDrink{
private:
    bool mainIn;
public:
    Beer(float percent = 0.0, char *name = " ", char *country = " ", float base = 0.0, bool mainIn = false): AlcoholicDrink(percent, name, country, base){
        this->mainIn = mainIn;
    }
    float computePrice(){
        if(strcmp(country,"Germany")==0){
            return base * 1.05;
        } else if(mainIn == false){
            return base * 1.1;
        }
        return base;
    }
    friend ostream &operator <<(ostream &out, Beer &b){
        cout << b.name << " " << b.country << " " << b.computePrice();
    }
};
class Wine: public AlcoholicDrink{
private:
    int year;
    char grapeType[20];
public:
    Wine(float percent = 0.0, char *name = " ", char *country = " ", float base = 0.0, int year = 0, char *grape = ""): AlcoholicDrink(percent, name, country, base){
        this->year = year;
        strcpy(this->grapeType, grape);
    }
    float computePrice(){
        if(strcmp(country,"Italy")==0){
            return base * 1.05;
        } else if(year <= 2005 ){
            return base * 1.15;
        }
        return base;
    }
    friend ostream &operator <<(ostream &out, Wine &b){
        cout << b.name << " " << b.country << " " << b.computePrice() << endl;
    }
};
void lowestPrice(AlcoholicDrink ** ad, int n){
    AlcoholicDrink *tmp = ad[0];
    for(int i = 1; i < n; i++){
        if(ad[i]>tmp){
            tmp = ad[i];
        }
    }
    Beer*b = dynamic_cast<Beer*>(tmp);
    cout << *b;
}
int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }
}


