/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
using namespace std;

class Circle {
  float radius;
  const float PI = 3.14;
public:
    Circle(float radiu = 1){

        radius = radiu;
    }
    float perimeter (){
        return 2 * PI * radius;
    }
    float area (){
        return PI * (radius * radius);
    }
    bool equal(){
        return perimeter() == area();
    }
};

int main() {
    float r;
    cin >> r;
    //instanciate object from class Circle
    Circle c(r);

    cout << c.perimeter() << endl;
    cout << c.area() << endl;
    cout << c.equal() <<endl;
    return 0;
}