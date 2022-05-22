/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
using namespace std;

class Vehicle{
protected:
    float mass;
    int width, height;
public:
    Vehicle(int mass = 0, int width = 0, int height = 0){
        this->mass = mass;
        this->width = width;
        this->height = height;
    }
    float getMass(){
        return mass;
    }
    int getWidth(){
        return width;
    }
    virtual int dailyPrice() = 0;
};
class Automobile: public Vehicle{
private:
    int doors;
public:
    Automobile(int mass = 0, int width = 0, int height = 0, int doors = 0): Vehicle(mass, width, height){
        this->doors = doors;
    }
    int dailyPrice(){
        return doors < 5 ? 100 : 130;
    }
};
class Bus: public Vehicle{
private:
    int passengers;
public:
    Bus(int mass = 0, int width = 0, int height = 0, int passengers = 0): Vehicle(mass, width, height){
        this->passengers = passengers;
    }
    int dailyPrice(){
        return passengers*5;
    }
};
class Truck: public Vehicle{
private:
    float maxWeight;
public:
    Truck(int mass = 0, int width = 0, int height = 0, int maxWeight = 0): Vehicle(mass, width, height){
        this->maxWeight = maxWeight;
    }
    int dailyPrice(){
        return(mass + maxWeight)*0.02;
    }
    float getmaxWeight(){
        return maxWeight;
    }
};
class Parking{
private:
    Vehicle **vehicles;
    int size;
public:
    Parking(){
        size = 0;
        vehicles = new Vehicle* [0];
    }
    ~Parking(){
        delete [] vehicles;
    }
    Parking &operator+=(Vehicle *other){
        Vehicle **tmp = new Vehicle* [size+1];
        for(int i = 0; i < size; i++){
            tmp[i] = vehicles[i];
        }
        tmp[size++] = other;
        delete [] vehicles;
        vehicles = tmp;
        return *this;
    }
    float totallMass(){
        float max = 0.0;
        for(int i = 0; i < size; i++){
            max+=vehicles[i]->getMass();
        }
        return max;
    }
    int vehiclesWiderThan(int width){
        int count = 0;
        for(int i = 0; i < size; i++){
            if(vehicles[i]->getWidth()>width){
                count++;
            }
        }
        return count;
    }
    void print(){
        int automobiles = 0, busses = 0, trucks = 0;
        for(int i = 0; i < size; i++){
            Automobile *a = dynamic_cast<Automobile*>(vehicles[i]);
            if(a!=NULL){
                automobiles++;
            }
            Bus *b = dynamic_cast<Bus*>(vehicles[i]);
            if(b!=NULL){
                busses++;
            }
            Truck *t = dynamic_cast<Truck*>(vehicles[i]);
            if(t!=NULL){
                trucks++;
            }
        }
        cout<<"Automobiles: "<<automobiles<<endl;
        cout<<"Busses: "<<busses<<endl;
        cout<<"Trucks: "<<trucks<<endl;
    }
    int greaterMaxWeightThan(Vehicle &v){
        int count = 0;
        for(int i = 0; i < size; i++){
            Truck *t = dynamic_cast<Truck *>(vehicles[i]);
            if(t != nullptr){
                if(t->getmaxWeight() > v.getMass()){
                    count++;
                }
            }
        }
        return count;
    }
    int dailyProfit(){
        int result = 0;
        for(int i = 0; i < size; i++){
            result+=vehicles[i]->dailyPrice();
        }
        return result;
    }
};
int main() {
    Parking p;
    int n;
    cin >> n;
    int width, height, broj;
    float mass, max_weight;
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> mass >> width >> height >> broj;
            Automobile *a = new Automobile(mass, width, height, broj);
            p += a;
        }
        if (type == 2) {
            cin >> mass >> width >> height >> broj;
            p += new Bus(mass, width, height, broj);
        }
        if (type == 3) {
            cin >> mass >> width >> height >> max_weight;
            p += new Truck(mass, width, height, max_weight);
        }
    }

    p.print();
    cout << "\nDaily profit: " << p.dailyProfit() << endl;
    cout << "Total mass: " << p.totallMass() << endl;
    cout << "Number wider then 5 is: " << p.vehiclesWiderThan(5) << endl;
    Automobile a(1200, 4, 3, 5);
    cout << "Number of trucks with max weight larger then the automobile is: " << p.greaterMaxWeightThan(a) << endl;
    return 0;
}
