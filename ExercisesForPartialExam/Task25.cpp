/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Tickets{
protected:
    int ID[13];
    char event[100];
    float basePrice;
    static int discount;
public:
    Tickets(int *ID = {0}, char *event = "", float basePrice = 0.0){
        for(int i = 0; i < 12; i++){
            this->ID[i] = ID[i];
        }
        strcpy(this->event, event);
        this->basePrice = basePrice;
    }
    Tickets(const Tickets &other){
        for(int i = 0; i < 12; i++){
            this->ID[i] = other.ID[i];
        }
        strcpy(this->event, other.event);
        this->basePrice = other.basePrice;
    }
    static void changeDiscount(int d){
        discount = d;
    }
    bool falsifikat(int from, int to){
        int number = 1000*ID[8] + 100*ID[9] + 10*ID[10] + ID[11];
        return (number >= from && number <= to);
    }
    friend ostream &operator<<(ostream &out, const Tickets &e){
        for(int i = 0; i < 12; i++){
            out << e.ID[i];
        }
        return out << "-" << e.event << "-" << e.presmetajCena();
    }
    virtual float presmetajCena() const{
        return basePrice*(1-discount/100.0);
    }
};
int Tickets::discount = 0;

class Online: public Tickets{
private:
    bool premium;
public:
    Online(int *ID = {0}, char *event = "", float basePrice = 0.0, bool premium = false): Tickets(ID, event, basePrice){
        this->premium = premium;
    }
    Online(const Online &other): Tickets(other){
        this->premium = other.premium;
    }
    float presmetajCena() const{
            return (premium ? basePrice*(1-(0.15+(discount/100.0))) : basePrice*(1-(discount/100.0)));
    }
};

class Offline: public Tickets{
private:
    bool reservation;
public:
    Offline(int *ID = {0}, char *event = "", float basePrice = 0.0, bool reservation = false): Tickets(ID, event, basePrice){
        this->reservation = reservation;
    }
    Offline(const Offline &other): Tickets(other){
        this->reservation = other.reservation;
    }
    float presmetajCena() const{
        return (reservation ? basePrice*(1-(0.1-(discount/100.0))) : basePrice*(1-(discount/100.0)));
    }
};

void vkupenPrihod(Tickets ** t, int n, int from, int to){
    float total = 0.0;
    for(int i = 0; i < n; i++){
        if(t[i]->falsifikat(from, to)){
            total += t[i]->presmetajCena();
        }
    }
    cout << total;
}

int main() {
    int testCase;
    cin >> testCase;
    int ID[12];
    char nastan[100];
    float price;
    bool premium;
    bool rezervacija;
    int od, doo;

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> premium;
        Online o1(ID, nastan, price, premium);
        cout << o1 << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> rezervacija;
        Offline o2(ID, nastan, price, rezervacija);
        cout << o2 << endl;

    }
    else if (testCase == 2) {
        cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
        int n;
        cin >> n;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; j++)
                cin >> ID[j];
            cin >> nastan;
            cin >> price;

            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        cin >> od;
        cin >> doo;
        vkupenPrihod(t, n, od, doo);
        for (int i = 0; i < n; ++i) {
            delete t[i];
        }
        delete[] t;
    }
    else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        //cout<<n<<endl;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; ++j)
                cin >> ID[j];
            cin >> nastan;
            //cout<<nastan<<endl;
            cin >> price;
            //cout<<price<<endl;
            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                //cout<<rezervacija<<endl;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        int d;
        cin >> d;
        Tickets::changeDiscount(d);
        for (int i = 0; i < n; ++i)
            cout << *t[i] << endl;

    }
}

