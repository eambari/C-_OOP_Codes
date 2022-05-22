#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

class InvalidTeamName{
public:
    void what(char * a){
        cout<<a;
    }
};
class Goal {
private:
    char * player;
    int time;
    char teamname[50];
    void copy(const Goal & g){
        this->time=g.time;
        strcpy(this->teamname,g.teamname);
        this->player = new char [strlen(g.player)+1];
        strcpy(this->player,g.player);
    }
public:
    Goal(char * player="", int time=0,char * teamname=""){
        this->time=time;
        strcpy(this->teamname,teamname);
        this->player = new char [strlen(player)+1];
        strcpy(this->player,player);
    }
    Goal (const Goal & g){
        copy(g);
    }

    Goal & operator =(const Goal &g){
        if(this!=&g){
            delete [] player;
            copy(g);
        }
        return *this;
    }

    friend ostream & operator << (ostream & out, const Goal &g){
        out<<g.time<<" "<<g.player<<endl;
        return out;
    }
    Goal & operator ++(){
        time++;
        return *this;
    }
    Goal operator -- (){
        Goal copy(*this);
        time--;
        return copy;
    }
    char *getTeamname (){
        return teamname;
    }

};

class Game{
private:
    Goal * goals;
    char Team1[50];
    char Team2[50];
    int n;
    void copy(const Game & g){
        strcpy(this->Team1,g.Team1);
        strcpy(this->Team2,g.Team2);
        this->goals = new Goal [g.n];
        for(int i=0; i<g.n; i++)
            goals[i]=g.goals[i];
    }
public:
    Game(char * Team1 = "", char * Team2 = ""){
        strcpy(this->Team1,Team1);
        strcpy(this->Team2,Team2);
        goals = new Goal [0];
        n=0;
    }
    Game (const Game & g){
        copy(g);
    }
    Game & operator = (const Game & g){
        if(this!=&g){
            delete [] goals;
            copy(g);
        }
        return *this;
    }

    Game & operator += (const Goal & g){
        Goal copy (g);
        if (strcmp(copy.getTeamname(),Team1)!=0&&strcmp(copy.getTeamname(),Team2)!=0)
            throw InvalidTeamName();

        Goal * tmp = new Goal [n+1];
        for(int i=0; i<n; i++)
            tmp[i]=goals[i];
        tmp[n++]=g;
        delete [] goals;
        goals=tmp;
        return *this;
    }
    friend ostream & operator << (ostream & out, const Game & g){
        out<<g.Team1<<" - "<<g.Team2<<endl;
        for(int i=0; i<g.n; i++)
            out<<g.goals[i];
        return out;
    }
    ~Game(){
        delete [] goals;
    }
    char *getTeam1(){
        return Team1;
    }
    char *getTeam2(){
        return Team2;
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
        try{
            n += g;
        } catch(InvalidTeamName &e) {
            cout<<"Invalid team name: "; e.what(team1);
        }
    }
    cout<<endl;
    cout << n << endl;
    return 0;
}
