/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class Toy {
public:
    virtual float getVolume() = 0;
    virtual float getWeight() = 0;
};
class Shape {
protected:
    char color[100];
    int density;
public:
    Shape(char *color = "", int density = 0){
     strcpy(this->color, color);
     this->density = density;
    }
};
class Cubes: public Toy, public Shape{
private:
    int height;
    int width;
    int depth;
public:
    Cubes(char *color = "", int density = 0, int height = 0, int width = 0, int depth = 0): Shape(color, density){
        this->height = height;
        this->width = width;
        this->depth = depth;
    }
    float getVolume(){
        return (height*width*depth);
    }
    float getWeight(){
        return (density*getVolume());
    }
};
class Balls: public Toy, public Shape{
private:
    int radius;
public:
    Balls(char *color = "", int density = 0, int radius = 0): Shape(color, density){
        this->radius = radius;
    }
    float getVolume(){
        return 4/3.0*(3.14*radius*radius*radius);
    }
    float getWeight(){
        return (density*getVolume());
    }
};

void totalWeight(Toy **toys, int n, float petrasWeight){
 int max = 0;
 for(int i = 0; i < n; i++){
     max+=toys[i]->getWeight();
 }
 if(max > petrasWeight){
     cout << "YES" << endl;
 } else {
     cout << "NO" << endl;
 }
}
void maxVolume(Toy **toys, int n, float petrasVolume){
    float max = 0.0;
    for(int i = 0; i < n; i++){
        float volume = toys[i]->getVolume();
        if(volume>max){
            max = volume;
        }
    }
    cout << "The difference is: " << abs(max-petrasVolume);
}
int main(){
    Toy **toys;
    int n;
    cin >> n;
    int input, density, radius, height, width, depth;;
    char color[15];
    for(int i = 0; i < n; i++){
        cin >> input >> color >> density;
        if(input == 1){
            cin >> radius;
            toys[i] = new Balls(color, density, radius);
        } else {
            cin >> height >> width >> depth;
            toys[i] = new Cubes(color, density, height, width, depth);
        }
    }
    cin >> color >> density >> height >> width >> depth;
    Cubes petras(color, density, height, width, depth);
    totalWeight(toys, n, petras.getWeight());
    maxVolume(toys, n, petras.getVolume());
    return 0;
}