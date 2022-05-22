/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <string.h>
using namespace std;
class Parcel {
protected:
    int id;
    static int price;
public:
    Parcel(int id=0) {
        this->id=id;
    }
    static void setProcessingPrice (int p) {
        price = p;
    }
    int getId(){
        return id;
    }
};

int Parcel::price = 150;

class Envelope : public Parcel{
private:
    int width;
    int height;
    char receiver[50];
public:
    Envelope(int id = 0, char * receiver = "", int width = 0, int height = 0) : Parcel(id){
        this->width=width;
        this->height=height;;
        strcpy(this->receiver, receiver);
    }

    Envelope(const Envelope & p) : Parcel (p){
        this->width=p.width;
        this->height=p.height;
        strcpy(this->receiver,p.receiver);
    }
    void setReceiver(char rec[50]) {
        strcpy(receiver,rec);
    }

    int price() {
       return Parcel::price + ((height*width)*0.3);
    }
    char *getReceiver(){
        return receiver;
    }
    int getId(){
        return Parcel::id;
    }
    void setId(int idd) {
        id=idd;
    }
};
class PostOffice {
private:
    Envelope envelopes[100];
    int size;
public:
    PostOffice(int n=0) {
        this->size=n;
    }
    PostOffice(const PostOffice &p) {
        this->size=p.size;
    }

    int sendEnvelope(int id, char * receiver, int width, int height){
        Envelope b(id,receiver,width,height);
        addEnvelope(b);
        return b.price();
    }

    void addEnvelope (Envelope s) {
        envelopes[size++] = s;
    }

    void printEnvelopsTo(char *receiver) {
        cout<<"For"<<" "<<receiver<<" are envelops with ids: ";
        for(int i=0; i < size; i++){
            if(strcmp(receiver,envelopes[i].getReceiver())==0)
                cout<<envelopes[i].getId()<<" ";
        }
        cout<<endl;
    }
};


int main() {

    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.price() << endl;
        }
    }
    return 0;
}


