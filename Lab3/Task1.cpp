/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>

using namespace std;

class Signature
{
private:
    char name[20];
    char surname[20];
    char embg[14];
public:
    Signature(){

    }
    Signature(char * _name, char * _surname, char * _embg){
        strcpy(name, _name);
        strcpy(surname, _surname);
        strcpy(embg, _embg);
    }
    Signature(const Signature& d){
        strcpy(name, d.name);
        strcpy(surname, d.surname);
        strcpy(embg, d.embg);
    }
    friend class Contract;
};
class Contract
{
private:
    int id;
    char category[50];
    Signature signers[3];
public:
    Contract(){

    }
    Contract(int _id, char * _category, Signature _signers[3]) {
        id = _id;
        strcpy(category, _category);
        for (int i = 0; i < 3; i++) {
            signers[i] = _signers[i];
        }
    }
    Contract(const Contract& d){
            id = d.id;
            strcpy(category, d.category);
            for(int i=0; i<3; i++){
                signers[i]=d.signers[i];
            }
    }
    bool check (){
        int i, j;
        for(i = 0; i < 2; i++){
            for(j = i+1; j < 3; j++){
                if(strcmp(signers[i].embg, signers[j].embg)==0){
                    return true;
                }
            }
        }
        return false;
    }
};


int main()
{
    char embg[14], name[20], surname[20], category[20];
    int number, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> embg >> name >> surname;
        Signature p1(name, surname, embg);
        cin >> embg >> name >> surname;
        Signature p2(name, surname, embg);
        cin >> embg >> name >> surname;
        Signature p3(name, surname, embg);
        cin >> number >> category;
        Signature p[3];
        p[0] = p1; p[1] = p2; p[2] = p3;
        Contract d(number, category, p);
        cout << "Dogovor " << number << ":" << endl;
        if(d.check() == true)
            cout << "Postojat potpishuvaci so ist EMBG" << endl;
        else
            cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}