/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Film {
    char name[100];
    char director[50];
    char genre[50];
    int year;
public:
    Film(){}
    Film(char emer[100], char direktor[50], char zhanri[50], int viti){
        strcpy(name, emer);
        strcpy(director, direktor);
        strcpy(genre, zhanri);
        year = viti;
    }
    int getYear(){
        return year;
    }
    void print()
    {
      cout<<"Name: "<<name<<endl<<"Director: "<<director<<endl<<"Genre: "<<genre<<endl<<"Year: "<<year<<endl;
    }
};

void print_by_year(Film *f, int n, int year){
    for(int i = 0; i < n; i++){
        if(year == f[i].getYear()){
            f[i].print();
        }
    }
}

int main() {
    int n;
    cin >> n;
    Film films[n];

    for(int i = 0; i < n; ++i) {
        char name[100];
        char director[50];
        char genre[50];
        int year;
        cin >> name;
        cin >> director;
        cin >> genre;
        cin >> year;
        films[i] = Film(name, director, genre, year);

    }
    int year;
    cin >> year;
    print_by_year(films, n, year);

    return 0;
}
