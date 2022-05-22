/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>

using namespace std;

enum Color{
    RED,GREEN,BLUE
};

class Shape{
private:
    Color color;
    char id[5];
    char * description;
    double area;

    void copy(const Shape & s){
        this->color = s.color;
        strcpy(this->id, s.id);
        this->area = s.area;
        this->description = new char [strlen(s.description)+1];
        strcpy(this->description,s.description);
    }
public:
    Shape(char * id="", char * description="", Color color = RED, double area=0.0){
        this->color = color;
        strcpy(this->id, id);
        this->area = area;
        this->description = new char [strlen(description)+1];
        strcpy(this->description,description);
    }
    Shape(const Shape & s){
        copy(s);
    }
    Shape & operator = (const Shape & s){
        if (this!=&s){
            delete [] description;
            copy(s);
        }
        return *this;
    }
    ~Shape(){
        delete [] description;
    }
    void printColor() {
        if (color == 0)
            cout << "RED";
        else if (color == 1) cout << "GREEN";
        else cout << "BLUE";
    }
    void draw() {
        cout << id << " ";
        printColor();
        cout << " " << area << " ["<<description<<"]"<<endl;
    }
    char *getId(){
        return id;
    }

    int getColor() {
        return color;
    }

    double getArea() {
        return area;
    }
    void setArea(double area1) {
        area = area1;
    }
};
class Canvas{
private:
    Shape * shapes;
    int n;

    void copy(const Canvas & c){
        this->shapes=c.shapes;
        this->n=c.n;
        shapes=new Shape[this->n];
        for(int i=0;i<this->n;i++){
            shapes[i] = c.shapes[i];
        }
    }
public:
    Canvas(){
        n=0;
        shapes = new Shape[0];

    }
    Canvas(const Canvas & c){
        copy(c);

    }
    Canvas &operator = (const Canvas & c){
        if (this!=&c){
            delete [] shapes;
            copy(c);
        }
        return *this;
    }
    ~Canvas(){
        delete [] shapes;
    }

    void addShape(Shape s) {
        Shape * tmp = new Shape[n+1];
        for(int i=0; i<n; i++)
            tmp[i] = shapes[i];
        tmp[n++]=s;
        delete [] shapes;
        shapes=tmp;
    }
    void setN(int nn){
        n=nn;
    }
    void removeShapeById (char * id){

        Shape * tmp = new Shape [n];
        int j=0;
        for(int i=0; i<n; i++){
            if(!(strcmp(shapes[i].getId(),id)==0)){
                tmp[j]=shapes[i];
                ++j;
            }
        }
        delete [] shapes;
        shapes=tmp;
        n=j;
    }

    void removeShapesByColor (Color color){
        Shape * tmp = new Shape [n];
        int j=0;
        for(int i=0; i<n; i++){
            if(shapes[i].getColor()!=color){
                tmp[j]=shapes[i];
                ++j;
            }
        }
        delete [] shapes;
        shapes=tmp;
        n=j;
    }

    Canvas & expandAll (double percent){

        for (int i = 0; i<n; i++) {
            shapes[i].setArea(shapes[i].getArea() * (1.0+percent));
        }
        return *this;
    }

    void drawAll() {
        for (int i = 0; i < n; i++) {
            shapes[i].draw();
        }
    }
    void drawOnly(Color color) {
        for (int i = 0; i < n; i++) {
            if (color == shapes[i].getColor())
                shapes[i].draw();
        }
    }
    double totalArea() {
        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            sum += shapes[i].getArea();
        }
        return sum;
    }
    Canvas getHalfCanvas() {
        Canvas halfCanvas(*this);
        for (int i = 0; i < n; i++) {
            halfCanvas.shapes[i].setArea(shapes[i].getArea() / 2.0);
        }
        return halfCanvas;
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
        char description [100];

        cin>>id>>description>>color>>area;
        Shape s (id, description, (Color) color, area);
        canvas.addShape(s);
    }

    cout<<"TESTING = FOR CLASS CANVAS"<<endl;
    Canvas c;
    c = canvas;

    cout<<"TESTING DRAW ALL"<<endl;

    c.drawAll();

    cout<<"TESTING DRAW RED SHAPES"<<endl;

    c.drawOnly(RED);

    cout<<"TESTING TOTAL AREA"<<endl;

    cout<<c.totalArea()<<endl;

    cout<<"TESTING HALF CANVAS"<<endl;
    Canvas reducedCanvas = c.getHalfCanvas();
    cout<<c.totalArea()<<" "<<reducedCanvas.totalArea()<<endl;

    if (reducedCanvas.totalArea() == c.totalArea()) {
        cout<<"DO NOT CHANGE THE AREA OF THE OBJECT IN THE CURRENT CANVAS. JUST IN THE NEW CANVAS"<<endl;
    }

    cout<<"TESTING EXPAND ALL"<<endl;
    c.expandAll(0.10);
    cout<<c.totalArea()<<endl;

    cout<<"TESTING REMOVE BY ID"<<endl;
    c.removeShapeById("A1");
    c.removeShapeById("Z11");

    c.drawAll();

    cout<<"TESTING REMOVE BY COLOR"<<endl;
    c.removeShapesByColor(RED);

    c.drawAll();

    return 0;
}