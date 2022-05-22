/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;
enum Color {red, green, blue};
class Shape{
protected:
    Color color;
    char id[5];
    char *description;
public:
    Shape(char *id = " ", char *description = " ", Color color = red){
        this->color = color;
        strcpy(this->id, id);
        this->description = new char[strlen(description)+1];
        strcpy(this->description, description);
    }
    virtual ~Shape(){
        delete [] description;
    }
    void drawColor(){
        switch (color) {
            case red:
                cout << "RED";
                break;
            case green:
                cout << "GREEN";
                break;
            case blue:
                cout << "BLUE";
                break;
        }
    }
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual double draw() = 0;
    bool operator > (Shape& other) {
        return perimeter() > other.perimeter();
    }
};
class Square: public Shape{
private:
    double side;
public:
    Square(char *id = " ", char *description = " ", Color color = red, double side = 0): Shape(id, description, color){
     this->side = side;
    }
    double area(){
        return double(side*side);
    }
    double perimeter(){
        return double(4*side);
    }
    double draw(){
        cout << id << " ";
        drawColor();
        cout << " " << description << " type: square " << perimeter() << " " << area() << endl;
    }
};
class Rectangle: public Shape{
private:
    double base;
    double height;
public:
    Rectangle(char *id = " ", char *description = " ", Color color = red, double base = 0, double height = 0): Shape(id, description, color){
        this->base = base;
        this->height = height;
    }
    double area(){
        return double(base*height);
    }
    double perimeter(){
        return double(2*(base+height));
    }
    double draw(){
        cout << id << " ";
        drawColor();
        cout << " " << description << " type: rectangle " << perimeter() << " " << area() << endl;
    }
};
class Circle: public Shape{
private:
    double radius;
public:
    Circle(char *id = " ", char *description = " ", Color color = red, double radius = 0): Shape(id, description, color){
        this->radius = radius;
    }
    double area(){
        return double(radius*radius*3.14);
    }
    double perimeter(){
        return double(2*radius*3.14);
    }
    double draw(){
        cout << id << " ";
        drawColor();
        cout << " " << description << " type: circle " << perimeter() << " " << area() << endl;
    }
};
double totalArea (Shape **shapes, int n){
    double max = 0.0;
    for(int i = 0; i < n; i++){
        max+=shapes[i]->area();
    }
    return max;
}
Shape * maxPerimeter (Shape **shapes, int n){
  Shape *max = shapes[0];
  for(int i = 1; i < n; i++){
      if(*shapes[i] > *max){
          max = shapes[i];
      }
  }
  return max;
}
void drawAllFromType(Shape **shapes, int n, char *name){
    bool check;
    if(strcmp(name,"circle")==0){
        for(int i = 0; i < n; i++){
            Shape *tmp = dynamic_cast<Circle*>(shapes[i]);
            if(tmp != NULL){
                check = true;
                shapes[i]->draw();
            }
        }
    }
    else if(strcmp(name,"rectangle")==0){
        for(int i = 0; i < n; i++){
            Shape *tmp = dynamic_cast<Rectangle*>(shapes[i]);
            if(tmp != NULL){
                check = true;
                shapes[i]->draw();
            }
        }
    }
    else{
        for(int i = 0; i < n; i++){
            Shape *tmp = dynamic_cast<Square*>(shapes[i]);
            if(tmp != NULL){
                check = true;
                shapes[i]->draw();
            }
        }
    }
   if(check == false){
       cout<<"There are no shapes from type "<<name<<endl;
   }
}
int main () {

    int n;
    cin>>n;
    //cout<<size;
    Shape ** shapes = new Shape * [n];

    int type;
    char id [5];
    char description[20];
    int color;
    double radius, a, b;
    for (int i=0;i<n;i++) {
        cin>>type>>id>>description>>color;
        //cout<<i;
        switch(type) {
            case 0: //circle
                cin>>radius;
                shapes[i] = new Circle (id, description, (Color) color, radius);
                break;
            case 1: //square
                cin>>a;
                shapes[i] = new Square (id, description, (Color) color, a);
                break;
            case 2: //rectangle
                cin>>a>>b;
                shapes[i] = new Rectangle (id, description, (Color) color, a, b);
                break;
            default:
                break;

        }
    }
    cout<<"Total area: "<<totalArea(shapes,n)<<endl;
    cout<<"Max perimeter of a shape is: "<<(maxPerimeter(shapes,n))->perimeter()<<endl;

    cout<<"Draw only circles"<<endl;
    drawAllFromType(shapes,n,"circle");

    cout<<"Draw only squares"<<endl;
    drawAllFromType(shapes,n,"square");

    cout<<"Draw only rectangle"<<endl;
    drawAllFromType(shapes,n,"rectangle");

    return 0;
}
