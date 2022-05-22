/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;
class Team{
protected:
    char name[15];
    int wins;
    int defeats;

    void copy(const Team &other){
        strcpy(this->name, other.name);
        this->wins = other.wins;
        this->defeats = other.defeats;
    }
public:
    Team(char *name = "Manchester United", int wins = 10, int defeats = 0){
        strcpy(this->name, name);
        this->wins = wins;
        this->defeats = defeats;
    }
    Team(const Team &other){
        copy(other);
    }
    Team &operator=(const Team &other){
        if(this != &other){
            copy(other);
        }
        return *this;
    }
    void print(){
        cout << "Ime: " << name << " Pobedi: " << wins << " Porazi: " << defeats;
    }
};
class FootballTeam: public Team{
private:
    int yellowCards;
    int redCards;
    int draw;
public:
    FootballTeam(char *name, int wins, int defeats, int yellowCards, int redCards, int draw): Team(name, wins, defeats){
        this->yellowCards = yellowCards;
        this->redCards = redCards;
        this->draw = draw;
    }
    void print(){
        Team::print();
        cout << " Nereseni: " << draw << " Poeni: " << (wins * 3) + draw;
    }
};
int main(){
    char ime[15];
    int pob,por,ck,zk,ner;
    cin>>ime>>pob>>por>>ck>>zk>>ner;
    FootballTeam f1(ime, pob, por, ck, zk, ner);
    f1.print();
    return 0;
}
