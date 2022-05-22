#include <iostream>
#include <cstring>
using namespace std;

class Automobile{
private:
    char * brand;
    int * registration;
    int maxspeed;
    void copy(const Automobile & a){
    	this->brand = new char [strlen(a.brand)+1];
        strcpy(this->brand,a.brand);
        this->maxspeed=a.maxspeed;
        this->registration = new int [5];
        for(int i=0; i<5; i++){
        	this->registration[i]=a.registration[i];
        }
    }
public:
    Automobile(){
    }
    Automobile(char * brand, int * registration, int maxspeed){
    	this->brand = new char [strlen(brand)+1];
        strcpy(this->brand,brand);
        this->maxspeed=maxspeed;
        this->registration = new int [5];
        for(int i=0; i<5; i++){
        	this->registration[i]=registration[i];
        }
    }
    Automobile(const Automobile & a){
    	copy(a);
    }
    Automobile & operator = (const Automobile & a){
        if(this!=&a){
        	delete [] registration;
            delete [] brand;
            copy(a);
        }
        return *this;
    }
    bool operator == (const Automobile & a){
        for(int i=0; i<5; i++){
        	if(this->registration[i]!=a.registration[i])
                return false;
        }
        return true;
    }
    int getSpeed(){
    	return maxspeed;
    }
    friend ostream & operator << (ostream & out, const Automobile & a){
        out<<"FINKI-Car"<<endl;
    	 out<<"Marka\t"<<a.brand<<"\tRegistracija";
         out<<"[ ";
        for (int i=0;i<5;i++)
        	out<<a.registration[i]<<" ";
    		out<<"]";
        return out;
    }
};



class RentACar{
private:
    char name[100];
    Automobile * autos;
    int n;
public:
    RentACar(char * name = "no name"){
		strcpy(this->name,name);
        n=0;
        autos = new Automobile [0];
    }
    RentACar & operator +=(const Automobile & a){
    	Automobile * tmp = new Automobile [n+1];
        for(int i=0; i<n; i++)
            tmp[i] = autos[i];
        tmp[n++] = a;
        delete [] autos;
        autos=tmp;
        return *this;
    }
    RentACar & operator -= (const Automobile & a){
    	bool flag = false;
        for(int i=0; i<n; i++){
        	if(autos[i]==a)
                flag=true;
        }
        if(flag){
        	Automobile * tmp = new Automobile [n-1];
            int j=0;
            for(int i=0; i<n; i++){
                if(!(autos[i]==a)){
                	tmp[j++] = autos[i];
                }
            }
            delete [] autos;
            autos=tmp;
            --n;
        }
        return *this;
    }

    void printWithSpeedOver(int max){
        for(int i=0; i<n; i++){
        	if(autos[i].getSpeed()>150)
                cout<<autos[i];
        }
    }
};



int main()
{
   RentACar agencija("FINKI-Car");
   int n;
   cin>>n;

   for (int i=0;i<n;i++)
   {
    	char marka[100];
    	int regisracija[5];
    	int maximumBrzina;

       	cin>>marka;

       	for (int i=0;i<5;i++)
    		cin>>regisracija[i];

    	cin>>maximumBrzina;

       	Automobile nov=Automobile(marka,regisracija,maximumBrzina);

    	//dodavanje na avtomobil
       	agencija+=nov;

   }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
    cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.printWithSpeedOver(150);

    return 0;
}