/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;
class ImaMasa {
protected:
    const static double density;
    const static double mass;
public:
    virtual double vratiMasa()=0;
    virtual void pecati()=0;
};

const double ImaMasa::density=0.8;
const double ImaMasa::mass=0.2;


class PaketPijalok: public ImaMasa {
protected:
    double VolumenEden;
    int kolicina;
public:
    PaketPijalok (double VolumenEden=0.0, int kolicina=0) {
        this->VolumenEden=VolumenEden;
        this->kolicina=kolicina;
    }
    PaketPijalok (const PaketPijalok & p) {
        this->VolumenEden=p.VolumenEden;
        this->kolicina=p.kolicina;
    }
    double vratiMasa() {
        return (VolumenEden*density+mass)*kolicina;
    }

    void pecati() {
        cout<<"quantity "<<kolicina;
    }
    int getKolicina() {
        return kolicina;
    }

};
class PaketSok:public PaketPijalok {
private:
    bool daliGaziran;
public:
    PaketSok(double VolumenEden=0.0, int kolicina=0, bool daliGaziran=false)
            :PaketPijalok(VolumenEden,kolicina ) {
        this->daliGaziran=daliGaziran;
    }
    PaketSok(const PaketSok &ps)
            :PaketPijalok(ps) {
        this->daliGaziran=ps.daliGaziran;

    }
    double vratiMasa() {
        if(daliGaziran==true) {
            return PaketPijalok::vratiMasa();
        } else {
            return PaketPijalok::vratiMasa()+(0.1*PaketPijalok::getKolicina());
        }
    }
    void pecati() {
        cout << "PaketSok" << endl;
        cout << "quantity " << kolicina << ", each of " << VolumenEden*density << " l(dm3)" << endl;
    }

};
class PaketVino:public PaketPijalok {
private:
    double procentAlkohol;
public:

    PaketVino(double VolumenEden=0.0, int kolicina=0, double procentAlkohol=0.0)
            :PaketPijalok(VolumenEden,kolicina ) {
        try {
            this->procentAlkohol=procentAlkohol;
            if(procentAlkohol<0 || procentAlkohol>1) {
                throw 1;
            }
        } catch (int) {
            this->procentAlkohol=0;
            cout<<"Incorrect alcohol percentage!"<<endl;
        }


    }
    PaketVino(const PaketVino &pv)
            :PaketPijalok(pv) {
        this->procentAlkohol=pv.procentAlkohol;

    }
    double getProcentAlkohol() {
        return procentAlkohol;
    }
    double vratiMasa() {
        return PaketPijalok::vratiMasa()*(0.9+procentAlkohol);
    }
    void pecati() {
        cout << "PaketVino" << endl;
        cout << "quantity " << kolicina << ", " << procentAlkohol*100 << "% alcohol each of " << VolumenEden*density << " l(dm3)" << endl;
    }
};

class Kamion {
private:
    char * registration;
    char * driver;
    ImaMasa ** im;
    int n;
public:

    Kamion(char* r ="", char* d="") {
        if(!(isalpha(r[0])&&isalpha(r[1])&&isalpha(r[7])&&isalpha(r[6]))) {
            throw 0;
        }
        this->n=0;
        registration= new char [strlen(r)];
        strcpy(registration,r);
        driver= new char [strlen(d)];
        strcpy(driver, d);

    }

    void dodadiElement(ImaMasa *m) {
        ImaMasa **tmp=new ImaMasa * [n+1];
        for(int i=0; i<n; i++) {
            tmp[i]=im[i];
        }
        tmp[n++]=m;

        im=tmp;
    }
    double vratiVkupnaMasa() {
        double total=0;
        for(int i=0; i<n; i++) {
            total+=im[i]->vratiMasa();
        }
        return total;
    }
    void pecati() {
        cout << "Truck with registration " << registration << " and driver " << driver << " transports: " << endl;
        for(int i=0; i<n; i++) {
            im[i]->pecati();
        }
    }
    Kamion pretovar(char* registration , char* driver) {
        Kamion A(registration,driver);
        int pos=0;
        double maxmass=im[0]->vratiMasa();
        for(int i=0; i<n; i++) {
            if(maxmass<im[i]->vratiMasa()) {
                maxmass=im[i]->vratiMasa();
                pos=i;
            }
        }

        for(int i=0; i<n; i++) {
            if(i!=pos) {

                A.dodadiElement(im[i]);
            }
        }
        return A;
    }


};
int main() {
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;
    try {
        cin>>reg;
        cin>>ime;
        Kamion A(reg, ime);
        ImaMasa **d = new ImaMasa*[5];
        cin>>vol>>kol;
        cin>>g;
        d[0] = new PaketSok(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[1] = new PaketVino(vol, kol, proc);
        cin>>vol>>kol;
        cin>>proc;
        d[2] = new PaketVino(vol, kol, proc);
        cin>>vol>>kol;
        cin>>g;
        d[3] = new PaketSok(vol, kol, g);
        cin>>vol>>kol;
        cin>>proc;
        d[4] = new PaketVino(vol, kol, proc);

        A.dodadiElement(d[0]);
        A.dodadiElement(d[1]);
        A.dodadiElement(d[2]);
        A.dodadiElement(d[3]);
        A.dodadiElement(d[4]);
        A.pecati();
        cout<<"Total mass: "<<A.vratiVkupnaMasa()<<endl;
        cin>>reg;
        cin>>ime;
        Kamion B = A.pretovar(reg, ime);
        B.pecati();
        cout<<"Total mass: "<<B.vratiVkupnaMasa()<<endl;
    } catch(int) {
        cout<<"Incorrect registration!";
    }

}