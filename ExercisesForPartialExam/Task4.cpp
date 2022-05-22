/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<string.h>
using namespace std;

class Cinema{
private:
    char name[20];
    int size;
    static float studentDiscount;
    float ticketPrice;
public:
    Cinema(char *name = " ", int size = 0, float ticketPrice = 0.0){
        strcpy(this->name, name);
        this->size = size;
        this->ticketPrice = ticketPrice;
    }
     static void setStudentDiscount(float sD){
        studentDiscount = sD;
    }
    virtual float price (bool isStudent){
        return isStudent == true ? ticketPrice - (ticketPrice * studentDiscount) : ticketPrice;
    }
    char *getname(){
        return name;
    }
    virtual float getStudentDiscount(){
        return studentDiscount;
    }
};
float Cinema::studentDiscount = 0.17;

class ThreeDCinema: public Cinema{
private:
    char *movieName;
    float hours;
    bool premiere;
public:
    ThreeDCinema(char *name = " ", int size = 0, float ticketPrice = 0.0, char *movieName = "", float hours = 0.0, bool premiere = false): Cinema(name,size,ticketPrice){
        this->movieName = new char[strlen(movieName)+1];
        strcpy(this->movieName, movieName);
        this->hours = hours;
        this->premiere = premiere;
    }
    float price (bool isStudent){
        float tmp = Cinema::price(isStudent);
        if(hours>3)
        {
            tmp+=70;
        }
        else if(hours>2.5)
        {
            tmp+=50;
        }
        if(premiere)
            tmp+=60;
        return tmp;
    }
    ~ThreeDCinema(){
        delete [] movieName;
    }
};
bool searchCinema (Cinema ** c, int n, char * title, bool premiere, bool isStudent) {
    if (premiere == true) {
        for (int i = 0; i < n; i++) {
            ThreeDCinema *t = dynamic_cast<ThreeDCinema *>(c[i]);
            if (t != nullptr) {
                if (strcmp(t->getname(), title) == 0) {
                    cout << title << " " << t->price(isStudent) << endl;
                    return true;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (strcmp(c[i]->getname(), title) == 0) {
            cout << title << " " << c[i]->price(isStudent) << endl;
            return true;
        }
        return false;
    }
}
void cheapestCinema(Cinema ** halls, int n,bool isStudent){
    float min = halls[0]->price(isStudent);
    int index = 0, counter = 0;
    for(int i = 1; i < n; i++){
        if(min > halls[i]->price(isStudent)){
            min = halls[i]->price(isStudent);
            index = i;
        }
        if(dynamic_cast<ThreeDCinema*>(halls[i])!=nullptr){
            counter++;
        }
    }
    cout << "Cheapest movie hall: " << halls[index]->getname() << " " << halls[index]->price(isStudent) << endl;
    cout << "3D cinema halls: " << counter << " from total " << n;
}
int main(){

    int tip,n;
    char name[100], movieName[40];
    int no;
    bool premiere;
    float ticketPrice;
    float hours;
    bool isStudent;

    cin>>tip;
    if (tip==1){//Cinema
        cin>>name>>no>>ticketPrice;
        Cinema k1(name,no,ticketPrice);
        cout<<"Cinema created with name: "<<k1.getname()<<endl;
    }
    else if (tip==2){//price - Cinema
        cin>>name>>no>>ticketPrice>>isStudent;
        Cinema k1(name,no,ticketPrice);
        cout<<"Initial price for the cinema with name "<<k1.getname()<< " is: " <<k1.price(isStudent)<<endl;
    }
    else if (tip==3){//3D Cinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"Cinema created with name "<<s.getname()<<" and discount "<<s.getStudentDiscount()<<endl;
    }
    else if (tip==4){//price - 3DCinema
        cin>>name>>no>>ticketPrice>>movieName>>hours>>premiere>>isStudent;
        ThreeDCinema s(name,no,ticketPrice,movieName,hours,premiere);
        cout<<"The price for the cinema "<<s.getname()<<" is: "<<s.price(isStudent)<<endl;
    }
    else if (tip==5) {//cheapest Cinema
        Cinema ** halls = new Cinema *[5];
        int n;
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Home",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        cheapestCinema(halls,5,true);
    }
     else if (tip==6){//search
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);

        if(searchCinema(halls,5, "Milenium3D",true,true))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

        if(searchCinema(halls,5, "CinePlexx1",false,false))
            cout<<"Found"<<endl;
        else cout<<"Not found"<<endl;

    }
    else if (tip==7){//change price
        Cinema ** halls = new Cinema *[5];
        halls[0] = new Cinema("Cineplexx1",1,350);
        halls[1] = new ThreeDCinema("Milenium3D",44,285,"Shrek",2.5,false);
        halls[2] = new ThreeDCinema("Vardar",12,333,"StarWars",4,true);
        halls[2] = new ThreeDCinema("Domasno",44,299,"Godfather",5,false);
        halls[3] = new Cinema("Cineplexx2",2,333);
        halls[4] = new ThreeDCinema("Cinedays",1,310,"ManInBlack",5,true);
        halls[2] -> setStudentDiscount(0.9);
        cheapestCinema(halls,4,true);
    }
    return 0;
}