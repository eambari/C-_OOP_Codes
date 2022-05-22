/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>

using namespace std;

enum COLOR {RED, GREEN, BLUE};

class Shape{
private:
 COLOR color;
 char id[5];
 double area;
public:
    Shape(char *_id = "", COLOR _color = RED, double _area = 0.0){
        color = _color;
        strcpy(id, _id);
        area = _area;
    }
    Shape(const Shape& s){
        color = s.color;
        strcpy(id, s.id);
        area = s.area;
    }
    void printColor(){
        switch(color){
            case RED:
                cout << "RED"; break;
            case BLUE:
                cout << "BLUE"; break;
            case GREEN:
                cout << "GREEN"; break;
        }
    }

    void draw(){
        cout << id << " ";
        printColor();
        cout << " " << area << endl;
    }
    COLOR getColor(){
        return color;
    }
    double getArea(){
        return area;
    }
    void reducedArea(){
        area/=2;
    }
};
class Canvas {
private:
    int number;
    Shape shapes[100];
public:
    Canvas(){number = 0;}
    Canvas(const Canvas& c){
        number = c.number;
        for(int i = 0; i < c.number; i++){
            shapes[i] = c.shapes[i];
        }
    }
    void addShape(Shape s){
        shapes[number++] = s;
    }
    void drawAll() {
        for(int i = 0; i < number;i++){
            shapes[i].draw();
        }
    }
    void drawOnly(COLOR color){
        for(int i = 0; i < number; i++){
            if(shapes[i].getColor() == color){
                shapes[i].draw();
            }
        }
    }
    double totalArea(){
        double sum = 0.0;
        for(int i = 0; i < number; i++){
            sum+=shapes[i].getArea();
        }
        return sum;
    }
    Canvas getHalfCanvas(){
        Canvas copy(*this);
        for(int i = 0;i < copy.number; i++){
            copy.shapes[i].reducedArea();
        }
        return copy;
    }
};
int main () {

    int n;
    cin>>n;
    cout<<"ADITION OF SHAPES IN THE CANVAS"<<endl;
    Canvas canvas;

    for (int i=0;i<n;i++) {
        char id [5];
        int color;
        double area;

        cin>>id>>color>>area;
        Shape s (id, (COLOR) color, area);
        canvas.addShape(s);
    }

    cout<<"TESTING DRAW ALL"<<endl;

    canvas.drawAll();

    cout<<"TESTING DRAW RED SHAPES"<<endl;

    canvas.drawOnly(RED);

    cout<<"TESTING TOTAL AREA"<<endl;

    cout<<canvas.totalArea()<<endl;

    cout<<"TESTING HALF CANVAS"<<endl;
    Canvas reducedCanvas = canvas.getHalfCanvas();
    cout<<canvas.totalArea()<<" "<<reducedCanvas.totalArea()<<endl;

    if (reducedCanvas.totalArea() == canvas.totalArea()) {
        cout<<"DO NOT CHANGE THE AREA OF THE OBJECT IN THE CURRENT CANVAS. JUST IN THE NEW CANVAS"<<endl;
    }

    return 0;
}
