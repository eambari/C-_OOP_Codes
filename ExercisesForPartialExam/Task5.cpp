/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include <cstring>
using namespace std;
struct Player {
    char name[15];
    int level;
    int points;
};
struct ComputerGame {
    char name[20];
    Player players[30];
    int n;

};
void bestPlayer(ComputerGame *array, int n) {
    ComputerGame most;
    int sum=0;
    char temp[20];
    if(array[0].n>array[1].n)
        most=array[0];
    else most=array[1];
    int tempoints=most.players[0].points;
    strcpy(temp,most.players[0].name);
    for(int i=0; i<most.n; i++){
        if(most.players[i].points>tempoints){
            tempoints=most.players[i].points;
            strcpy(temp,most.players[i].name);
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<temp<<" koj ja igra igrata "<<most.name;
}


int main() {
    int n,m;
    char ime[20];
    cin>>n;
    //create an array of max 100 computer games;
    ComputerGame poleigri[100];
    for (int i=0; i<n; i++) {
        ComputerGame nova;
        cin>>nova.name>>nova.n;
        Player pole[30];
        for (int j=0; j<nova.n; j++) {
            Player nov;
            cin>>nov.name>>nov.level>>nov.points;
            nova.players[j]=nov;
        }
        poleigri[i]=nova;
    }

    bestPlayer(poleigri,n);
    return 0;
}
