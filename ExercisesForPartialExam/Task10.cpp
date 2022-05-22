/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class InvalidTeamName{
    char name[50];
public:
    InvalidTeamName(char *name = " "){
        strcpy(this->name, name);
    }
    void printMessage(){
        cout << "Invalid team name: " << name << endl;
    }
};

class Goal{
private:
    char *scorer;
    int minute;
    char teamName[50];

    void copy(const Goal &other){
        this->scorer = new char[strlen(other.scorer)+1];
        strcpy(this->scorer, other.scorer);
        this->minute = other.minute;
        strcpy(this->teamName, other.teamName);
    }
public:
    Goal(char *scorer = " ", int minute = 0, char *teamName = " "){
        this->scorer = new char[strlen(scorer)+1];
        strcpy(this->scorer, scorer);
        this->minute = minute;
        strcpy(this->teamName, teamName);
    }
    Goal(const Goal &other){
        copy(other);
    }
    Goal &operator=(const Goal &other){
        if(this != &other){
            delete []scorer;
            copy(other);
        }
        return *this;
    }
    friend ostream& operator<<(ostream &out, const Goal &g){
        return out << g.minute << " " << g.scorer;
    }
    Goal &operator++(){
        this->minute++;
        return *this;
    }
    Goal operator--(int){
        Goal tmp(*this);
        minute--;
        return tmp;
    }
    char *getName(){
        return teamName;
    }
    ~Goal(){
        delete [] scorer;
    }
};
class Game{
    char firstTeam[50];
    char secondTeam[50];
    Goal *goals;
    int size;

    void copy(const Game &other){
        strcpy(firstTeam, other.firstTeam);
        strcpy(secondTeam, other.secondTeam);
        size = other.size;
        goals = new Goal [other.size];
        for(int i = 0; i < other.size; i++){
            goals[i] = other.goals[i];
        }
    }
public:
    Game(char *first = " ", char *second = " "){
        strcpy(firstTeam, first);
        strcpy(secondTeam, second);
        goals = new Goal [0];
        size = 0;
    }
    Game(const Game &other){
        copy(other);
    }
    Game &operator+=(Goal &other){
        if(strcmp(other.getName(),firstTeam)!=0 && strcmp(other.getName(),secondTeam)!=0){
                throw InvalidTeamName(other.getName());
        }
        Goal *tmp = new Goal [size+1];
        for(int i = 0; i < size; i++){
            tmp[i] = goals[i];
        }
        tmp[size++] = other;
        delete [] goals;
        goals = tmp;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Game &g){
        out << g.firstTeam << " - " << g.secondTeam << endl;
        for(int i = 0; i < g.size; i++){
            out << g.goals[i] << endl;
        }
        return out;
    }
    ~Game(){
        delete [] goals;
    }
};
int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            e.printMessage();
        }
    }
    cout << n << endl;
    return 0;
}


