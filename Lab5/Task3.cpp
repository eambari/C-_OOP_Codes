/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>

using namespace std;
enum Color {
    RED, GREEN, BLUE
};
class Shape {
private:
    Color color;
    char id[5];
    char *description;
    double area;
    void copy(const Shape &s) {
        this->color=s.color;
        strcpy(this->id,s.id);
        this->description = new char[strlen(s.description)+1];
        strcpy(this->description,s.description);
        this->area = s.area;
    }
public:
    Shape(char *id="", char *description="", Color color=RED, double area=0.0) {
        this->color=color;
        strcpy(this->id,id);
        this->description = new char[strlen(description)+1];
        strcpy(this->description,description);
        this->area = area;
    }
    Shape &operator =(const Shape&s) {
        if(this!=&s) {
            delete []description;
            copy(s);
        }
        return *this;
    }
    Shape(const Shape &s) {
        copy(s);
    }
    char *printColor() const {
        if (color == 0)
            return "RED";
        else if (color == 1)
            return "GREEN";
        else
            return "BLUE";
    }
    int getColor() {
        return (Color)color;
    }
    void setArea(double arr) {
        area=arr;
    }
    double getArea() {
        return area;
    }
    ~Shape() {
        delete [] description;
    }
    void setId(char *idd) {
        strcpy(id,idd);
    }
    char *getId() {
        return id;
    }
    friend ostream &operator <<(ostream &out, const Shape &s) {
        out<<s.id<<" ";
        out<<s.printColor()<<" "<<s.area<<" ["<<s.description<<"]"<<endl;
        return out;
    }
    friend istream &operator >>(istream &in, Shape &s) {
        in>>s.id>>s.description;
        int color;
        in>>color>>s.area;
        s.color = (Color)color;
        return in;
    }
    Shape &operator *=(double coef) {

        this->area*=coef;
        return *this;
    }

    bool operator == (Color color) {
        return this->color == color;
    }

    bool operator == (char * id) {
        return strcmp(this->id, id)==0;
    }

    bool operator != (Color color) {
        return !(this->color == color);
    }

    bool operator != (char * id) {
        return !(strcmp(this->id, id)==0);
    }


    bool operator >(const Shape &s) {
        return this->area > s.area;
    }
    Shape operator +(Shape shape) {
        double sum = this->area + shape.area;
        //cout<<sum<<endl;
        if (this->area >= shape.area)
            return Shape (this->id, this->description, this->color, sum);
        else
            return Shape (shape.id, shape.description, shape.color, sum);

        //return Shape(this->area + res);
    }
};
class Canvas {
private:
    Shape *shapes;
    int n;
    void copy(const Canvas &c) {
        this->n=c.n;
        shapes=new Shape[this->n];
        for(int i=0; i<this->n; i++)
            shapes[i]=c.shapes[i];
    }
public:
    Canvas() {
        n=0;
        shapes = new Shape [0];
    }
    Canvas(const Canvas &c) {
        copy(c);
    }
    Canvas &operator =(const Canvas &c) {
        if(this!=&c) {
            delete [] shapes;
            copy(c);
        }
        return *this;
    }
    Canvas &operator +=(const Shape &s) {
        Shape *temp = new Shape[n+1];
        for(int i=0; i<n; i++)
            temp[i] = shapes[i];
        temp[n++]=s;
        delete [] shapes;
        shapes=temp;
        return *this;
    }

    bool containsId (char * id) {
        for (int i=0; i<n; i++)
            if (shapes[i]==id)
                return true;

        return false;
    }
    Canvas &operator -= (char *id) {

        if (!containsId(id))
            return *this;

        Shape * temp=new Shape[n-1];
        int j=0;
        for(int i=0; i<n; i++) {
            if(shapes[i]!=id) {
                temp[j++]=shapes[i];
            }
        }
        delete [] shapes;
        shapes=temp;
        --n;
        return *this;
    }

    int containsColor (Color color) {
        int count = 0;
        for (int i=0;i<n;i++)
            if (shapes[i]==color)
                ++count;
        return count;
    }

    Canvas &operator -=(Color color) {

        int count = containsColor (color);
        if (count==0)
            return *this;

        Shape *temp=new Shape[n-count];
        int j=0;
        for(int i=0; i<n; i++) {
            if(shapes[i]!=color)
                temp[j++]=shapes[i];

        }
        delete [] shapes;
        shapes=temp;
        n=j;
        return *this;
    }

    double totalArea() {
        double res=0.0;
        for (int i=0; i<n; i++) {
            res+=shapes[i].getArea();
        }
        return res;
    }
    Canvas getHalfCanvas() {
        Canvas halfCanvas(*this);
        for(int i=0; i<n; i++) {
            halfCanvas.shapes[i]*=0.5;
        }
        return halfCanvas;
    }
    Canvas &expandAll(double percent) {
        for(int i=0; i<n; i++) {
            shapes[i]*=(1+percent);

        }
        return *this;
    }

    friend ostream & operator << (ostream & out, const Canvas & c) {
        for (int i=0;i<c.n;i++)
            out<<c.shapes[i];
        return out;
    }

    Shape & operator [] (int idx) {
        return shapes[idx];
    }

    Shape sum () {
        Shape shape;
        for (int i=0;i<n;i++)
            shape = shape + shapes[i];
        return shape;
    }
};
int main () {

    int n;
    cin>>n;

    Canvas canvas;

    cout<<"TEST FOR &gt;&gt; AND &lt;&lt; IN SHAPE CLASS"<<endl;
    Shape s;
    cin>>s;
    cout<<s;

    cout<<"TEST FOR += OF CLASS CANVAS"<<endl;
    canvas+=s;
    for (int i=1; i<n; i++) {
        cin>>s;
        canvas+=s;
    }

    cout<<"TESTING + FOR CLASS SHAPE AND [] FOR CLASS CANVAS"<<endl;
    //cout<<canvas[0];
    //cout<<canvas[3];
    cout<<(canvas[0]+canvas[3]);

    cout<<"TESTING = FOR CLASS CANVAS"<<endl;
    Canvas c;
    c = canvas;

    cout<<"TESTING &lt;&lt; FOR CLASS CANVAS"<<endl;
    cout<<c;


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

    cout<<"TESTING OPERATOR -= (REMOVE BY ID)"<<endl;
    c-=("A1");
    c-=("Z11");

    cout<<c;

    cout<<"TESTING OPERATOR -= (REMOVE BY COLOR)"<<endl;
    c-=(RED);
    cout<<c;

    cout<<"TESTING SUM METHOD AND + OPERATOR IN CLASS SHAPE"<<endl;
    cout<<c.sum();

    return 0;
}
