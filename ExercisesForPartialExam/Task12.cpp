/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;

class InvestmentPlan{
private:
    char name[80];
    float sum;
    float shares;
    bool currentPlan;

    void copy(const InvestmentPlan &other){
        strcpy(this->name, other.name);
        this->sum = other.sum;
        this->shares = other.shares;
        this->currentPlan = other.currentPlan;
    }
public:
    InvestmentPlan(char *name = " ", float sum = 0.0, float shares = 0.0, bool currentPlan = false){
        strcpy(this->name, name);
        this->sum = sum;
        this->shares = shares;
        this->currentPlan = currentPlan;
    }
    InvestmentPlan(const InvestmentPlan &other){
        copy(other);
    }
    InvestmentPlan &operator=(const InvestmentPlan &other){
        if(this != &other){
            copy(other);
        }
        return *this;
    }
    float getSum(){
        return sum;
    }
};

class InvestmentFund{
protected:
    char name[80];
    InvestmentPlan *plans;
    int size;
    float share;
public:
    InvestmentFund(char *name = " ", float share = 0.0){
        strcpy(this->name, name);
        this->share = share;
        this->size = 0;
        plans = new InvestmentPlan [0];
    }
    virtual double profit() = 0;
};

class MoneyFund: public InvestmentFund{
    static float provision;
public:
    MoneyFund(char *name = " ", float share = 0.0): InvestmentFund(name, share){

    }
    double profit(){
        float total = 0.0;
        for(int i = 0; i < size; i++){
            total+=plans[i].getSum();
        }
        return (total * provision/100)/365;
    }
};
float MoneyFund::provision = 0.1;

class ActionFund: public InvestmentFund{
    static float yearlyProvision;
    static float entryProvision;
public:
    ActionFund(char *name = " ", float share = 0.0): InvestmentFund(name, share){

    }
    double profit(){
        float total = 0.0;
        for(int i = 0; i < size; i++){
            total+=plans[i].getSum();
        }
        return ((total * yearlyProvision/100)/365);
    }
};
float ActionFund::yearlyProvision = 0.15;
float ActionFund::entryProvision = 0.3;


int main(){

    char investitor[80], ime[50];
    double plan, brUdeli, udel;
    bool flag = false;
    int n, m;
    cin >> n;
    InvestmentFund **fondovi = new InvestmentFund*[n];
    for(int i = 0; i < n; i++){
        cin >> ime;
        cin >> m;
        InvestmentPlan *ip = new InvestmentPlan[m];
        for(int j = 0; j < m; j++){
            cin >> investitor >> plan >> brUdeli;
            if(j % 2) flag = true;
            else flag = false;
            InvestmentPlan IP(investitor, plan, brUdeli, flag);
            ip[j] = IP;
        }
        cin >> udel;
        if(i % 2){
            fondovi[i] = new ActionFund(ime, ip, m, udel);

        }
        else{
            fondovi[i] = new MoneyFund(ime, ip, m, udel);
        }
    }
    cout << totalProfit(fondovi, n);
    return 0;
}

