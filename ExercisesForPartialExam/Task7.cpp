/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;

class nonDigitException{
public:
    void showMessage(){
        cout<<"The id number has a non-digit character"<<endl;
    }
};

class longerIdException{
public:
    void showMessage(){
        cout<<"The id number has more than 9 characters"<<endl;
    }
};

class DonationAction {
private:
    char * name;
    char * idnumber;
    int collectedFund;
    int neededFund;
    void copy(const DonationAction & da){
        this->name = new char [strlen(da.name)+1];
        strcpy(this->name,da.name);
        this->idnumber = new char [strlen(da.idnumber)+1];
        strcpy(this->idnumber,da.idnumber);
        this->neededFund=da.neededFund;
        this->collectedFund = da.collectedFund;
    }

public:
    DonationAction(char * name = "", char *idnumber = "", int neededFund = 0){
        if(strlen(idnumber)>9)
            throw longerIdException();

        for(int i=0; i<strlen(idnumber); i++)
            if(!isdigit(idnumber[i]))
                throw nonDigitException();


        this->name = new char [strlen(name)+1];
        strcpy(this->name,name);
        this->idnumber = new char [strlen(idnumber)+1];
        strcpy(this->idnumber,idnumber);
        this->neededFund=neededFund;
        collectedFund = 0;
    }

    DonationAction (const DonationAction & da){
        copy(da);
    }

    DonationAction & operator = (const DonationAction & da){
        if(this!=&da){
            delete [] idnumber;
            delete [] name;
            copy(da);
        }
        return *this;
    }

    friend ostream & operator << (ostream & out, const DonationAction & da){
        if(da.collectedFund > da.neededFund)
            out<<da.idnumber<<" "<<da.name<<" collected"<<endl;
        else
            out<<da.idnumber<<" "<<da.name<<" "<<da.neededFund-da.collectedFund<<" more denars are needed"<<endl;
        return out;
    }

    DonationAction & operator += (int donation){
        this->collectedFund+=donation;
        return *this;
    }

    bool operator < (DonationAction & right){
        if(neededFund-collectedFund == right.neededFund-right.collectedFund)
            return strlen(idnumber)>strlen(right.idnumber);
        else
            return ((neededFund-collectedFund) < (right.neededFund-right.collectedFund));
    }

    char *getId() const{
        return idnumber;
    }
};

class DonationSociety{
private:
    char presidentName[30];
    DonationAction * donations;
    int n;
public:
    DonationSociety(char * presidentName = ""){
        strcpy(this->presidentName,presidentName);
        this->donations = new DonationAction [0];
        n = 0;
    }

    bool takeDonation(char * idd, int donatedFund){
        for(int i=0; i<n; i++){
            if(strcmp(donations[i].getId(),idd)==0){
                donations[i]+=donatedFund;
                return true;
            }
        }
        return false;
    }

    DonationSociety & operator += (const DonationAction & da){
        for(int i=0; i<n; i++){
            if(strcmp(da.getId(),donations[i].getId())==0)
                return *this;
        }

        DonationAction * tmp = new DonationAction [n+1];
        for(int i=0; i<n; i++)
            tmp[i]=donations[i];
        tmp[n++]=da;
        delete [] donations;
        donations=tmp;
        return *this;
    }


    void sorting(DonationAction * d, int n) const{
        DonationAction copy;
        for(int i=0; i<n-1; i++){
            for (int j = 0; j < n-i-1; j++)
                if (d[j] < d[j+1]){
                    copy=d[j+1];
                    d[j+1]=d[j];
                    d[j]=copy;
                }
        }
    }

    friend ostream & operator << (ostream & out, const DonationSociety & ds){

        ds.sorting(ds.donations,ds.n);
        for(int i=0; i<ds.n; i++)
            out<<ds.donations[i];
        out<<"President:"<<ds.presidentName;
        return out;
    }

};

int main(){


    DonationSociety donacii("Velko Velkovski");
    int n;
    char naziv[50],id[50];
    int potrebnasuma,doniranasuma;
    cin>>n;

    for (int i=0;i<n;i++){
        cin.get();
        cin.getline(naziv,50);
        cin>>id>>potrebnasuma;
        try{
            DonationAction edna(naziv,id,potrebnasuma);
            donacii+=edna;
        }
        catch(longerIdException & e){
            e.showMessage();
        }
        catch(nonDigitException & e1){
            e1.showMessage();
        }
    }

    //donation
    cin>>n;
    for (int i=0;i<n;i++){

        cin>>id>>doniranasuma;

        if(!donacii.takeDonation(id,doniranasuma))
            cout<<"The donation is not taken. Wrong ID."<<endl;
    }
    cout<<"==============="<<endl;
    cout<<donacii;

}
