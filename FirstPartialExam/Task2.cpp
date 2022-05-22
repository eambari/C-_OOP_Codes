/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;

class Flight{
private:
    char takeOff[50];
    char landing[50];
    float duration;
    float price;

    void copy(const Flight &other){
        strcpy(takeOff, other.takeOff);
        strcpy(landing, other.landing);
        duration = other.duration;
        price = other.price;
    }
public:
    Flight(char *_take = " ", char *land = " ", float _duration = 0.0, float _price = 0.0){
        strcpy(takeOff, _take);
        strcpy(landing, land);
        duration = _duration;
        price = _price;
    }
    Flight (const Flight &other){
        copy(other);
    }
    Flight &operator=(const Flight &other){
        if(this != &other){
            copy(other);
        }
        return *this;
    }
    char *getDepartureCity(){
        return takeOff;
    }
    char *getArrivalCity(){
        return landing;
    }
    void printDuration (){
        int n = int(duration);
        cout << n << "h:" << ((duration-n)*60) << "min";
    }
    void printFlight (){
        cout << takeOff << " -> ";
        printDuration();
        cout << " -> " << landing << ": " << price << "EUR";
    }
    bool operator==(const Flight &f){
        return(strcmp(takeOff, f.takeOff) == 0 && strcmp(landing, f.landing) == 0);
    }
};

class Airline{
private:
    char name[50];
    Flight *flights;
    int size;

    void copy(const Airline &other){
        strcpy(name, other.name);
        size = other.size;
        flights = new Flight [size];
        for(int i = 0; i < size; i++){
            flights[i] = other.flights[i];
        }
    }
public:
    Airline(char *_name = " "){
        strcpy(name, _name);
        size = 0;
        flights = new Flight [0];
    }
    Airline(const Airline &other){
        copy(other);
    }
    Airline &operator=(const Airline &other){
        if(this != &other){
            delete [] flights;
            copy(other);
        }
        return *this;
    }
    void addFlight(Flight &f){
        for(int i = 0; i < size; i++){
            if(flights[i]==f){
                return;
            }
        }
        Flight *tmp = new Flight [size+1];
        for(int i = 0; i < size; i++){
            tmp[i] = flights[i];
        }
        tmp[size++] = f;
        delete [] flights;
        flights = tmp;
    }
    Flight* getFlights(){
        return flights;
    }
    int getN(){
        return size;
    }
    friend void searchFlights (Airline a, char departureCity [], char arrivalCity []);
};

void searchFlights (Airline a, char departureCity [], char arrivalCity []){
    bool has = true;
    for(int i = 0; i < a.getN(); i++){
        if(strcmp(a.getFlights()[i].getDepartureCity(), departureCity) == 0 && strcmp(a.getFlights()[i].getArrivalCity(), arrivalCity) == 0){
            a.getFlights()[i].printFlight();
            has = false;
        } else if(strcmp(departureCity, a.getFlights()[i].getArrivalCity())== 0){
            for(int j = 0; j < a.getN(); j++){
                if(strcmp(a.getFlights()[j].getDepartureCity(), arrivalCity) == 0)
                    a.getFlights()[i].printFlight();
                printf(" 1 stop ");
                a.getFlights()[j].printFlight();
                printf("\n");
                has = false;
                break;
            }
        }
    }
    if (has == true){
        printf("No connection between the cities\n");
    }
}

int main(){

    int testCase;
    cin >> testCase;

    if(testCase == 1){
        cout << "====Testing class Flight constructors and additional methods====" << endl;
        Flight f1;
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        cout << f2.getDepartureCity() << " " << f2.getArrivalCity() << endl;
        cout << "Testing OK" << endl;
    }
    else if(testCase == 2){
        cout << "====Testing class Flight methods printDuration() and printFlight()====" << endl;
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        f2.printFlight();
        cout << endl;
    }
    else if(testCase == 3){
        cout << "====Testing class Airplane constructors and methods====" << endl;
        Airline a("Wizzair");
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f1(dep, arr, dur, pr);
        a.addFlight(f1);
        Flight f3 = f1;
        a.addFlight(f3);
        a.getFlights()[0].printFlight();
        cout << endl;
        cout << a.getN() << endl;
        Airline b = a;
        b.getFlights()[0].printFlight();
        cout << endl;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        b.addFlight(f2);
        b.getFlights()[1].printFlight();
        cout << endl;
        cout << "Testing OK" << endl;
    }
    else if(testCase == 4){
        cout << "====Testing global function====" << endl;
        Airline a("Wizzair");
        char dep[50], arr[50];
        double dur, pr;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> dep >> arr >> dur >> pr;
            Flight f(dep, arr, dur, pr);
            a.addFlight(f);
        }
        cin >> dep >> arr;
        searchFlights(a, dep, arr);
        cout << endl << "Testing OK" << endl;
    }
    return 0;
}

