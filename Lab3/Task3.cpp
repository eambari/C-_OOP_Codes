/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Table {
private:
    int width;
    int height;
public:
    Table(int _width = 0, int _height = 0){
        width = _width;
        height = _height;
    }
    Table(const Table &t){
        width = t.width;
        height = t.height;
    }
    void print(){
        cout << " Table: " << width << " " << height << endl;
    }
};
class Room {
private:
    Table t;
    int length;
    int width;
public:
    Room(){}
    Room(int _length, int _width, Table _t){
        length = _length;
        width = _width;
        t = _t;
    }
    Room(const Room& r){
        length = r.length;
        width = r.width;
        t = r.t;
    }
    void print(){
        cout << " Room: " << length << " " << width;
        t.print();
    }
};
class House{
private:
    Room r;
    char address[50];
public:
    House(){}
    House (Room _r, char * _address){
        strcpy(address, _address);
        r = _r;
    }
    House (const House & h){
        strcpy(address, h.address);
        r = h.r;
    }
    void print(){
        cout << "Address: " << address;
        r.print();
    }
};
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int tableWidth, tableHeight;
        cin>>tableWidth;
        cin>>tableHeight;
        Table t(tableWidth, tableHeight);
        int rw, rl;
        cin>>rw;
        cin>>rl;
        Room r(rw, rl, t);
        char adresa[30];
        cin>>adresa;
        House h(r,adresa);
        h.print();
    }

    return 0;
}
