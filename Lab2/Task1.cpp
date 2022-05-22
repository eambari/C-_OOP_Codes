/*
Created by Endrit Ambari on 2022.
*/
/*
Define a class Angle that is described with:

degrees, minutes and seconds (int).
For the class implement:

constructor
get and set methods
method for computing the angle in seconds.
Define a method for checking if the angle is valid (the values for attributes are in the valid range). One angle is valid if it is in the range of [0,0,0 ; 360,0,0],

For example:

Input	Result
180 45 45
650745
 */
#include <iostream>
using namespace std;

class Angle {
    int degrees, minutes, seconds;
public:
    Angle (int degree = 360, int minute = 0, int second = 0){

        degrees = degree;
        minutes = minute;
        seconds = second;
    }
    int getDegrees (){
        return degrees;
    }
    int getMinutes (){
        return minutes;
    }
    int getSeconds (){
        return seconds;
    }
    void setDegrees (int degree){
        degrees = degree;
    }
    void setMinutes (int minute){
        minutes = minute;
    }
    void setSeconds (int second){
        seconds = second;
    }
    int toSeconds(){
        return (degrees*3600) + (minutes * 60) + seconds;
    }
};

bool checkAngle (Angle a1, int deg, int min, int sec) {
    return a1.getDegrees()==deg && a1.getMinutes()==min && a1.getSeconds()==sec;
}
bool check(int degrees,int minutes, int seconds){
    if((degrees+minutes+seconds)>360||(degrees+minutes+seconds)<0)
        return false;
    else if(degrees>360||degrees<0) return false;
    else if(minutes>60||minutes<0) return false;
    else if(seconds>60||seconds<0) return false;
    else return true;
}

int main() {

    //instanciate object of class Angle, named a1
    Angle a1;

    int deg, min, sec;

    cin >> deg >> min >> sec;

    if (check(deg, min, sec)) {

        a1.setDegrees(deg);
        a1.setMinutes(min);
        a1.setSeconds(sec);
        cout << a1.toSeconds();

        if (!checkAngle(a1,deg,min,sec)) {
            cout<<"Don't change the internal state of the private variables in the class!!!!";
        }

    } else {
        cout << "Invalid values" << endl;
    }

    return 0;
}