/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

class Camera{
protected:
    char manufacturer[20];
    char model[20];
    int year;
    float resolution;
public:
    Camera(char *manufacturer = "Sony", char *model = "X4", int year = 2022, float resolution = 12.0){
        strcpy(this->manufacturer, manufacturer);
        strcpy(this->model, model);
        this->year = year;
        this->resolution = resolution;
    }
    Camera &operator=(Camera *p){
        strcpy(this->manufacturer, p->manufacturer);
        strcpy(this->model, p->model);
        this->year = p->year;
        this->resolution = p->resolution;
    }
    virtual float price() = 0;
    virtual float rentalPrice(int days) = 0;

    char *getModel(){
        return model;
    }
};
class PhotoCamera: public Camera{
    bool raw;
public:
    PhotoCamera(char *manufacturer = "Sony", char *model = "X4", int year = 2022, float resolution = 12.0, bool raw = false): Camera(manufacturer, model, year, resolution){
        this->raw = raw;
    }
    float price(){
        return raw == true ? (150 + (resolution*20)) : (100 + (resolution*20));
    }
    float rentalPrice(int days){
        return days > 7 ? ((days * (price()/100))*0.8) : (days * (price()/100));
    }
};
class VideoCamera: public Camera{
    int length;
public:
    VideoCamera(char *manufacturer = "Sony", char *model = "X4", int year = 2022, float resolution = 12.0, int length = 30): Camera(manufacturer, model, year, resolution){
        this->length = length;
    }
    float price(){
        return (length/60) > 60 ? ((resolution*80)*1.4) : (resolution*80);
    }
    float rentalPrice(int days){
        return days > 7 ? ((days * (price()/100))*0.8) : (days * (price()/100));
    }
};
class FilmCamera: public Camera{
    int fps;
public:
    FilmCamera(char *manufacturer = "Sony", char *model = "X4", int year = 2022, float resolution = 12.0, int fps = 30): Camera(manufacturer, model, year, resolution){
        this->fps = fps;
    }
    float price(){
        return fps > 30 ? 50000+(5000*(fps-30)) : 50000;
    }
    float rentalPrice(int days){
        return fps > 60 ? ((500*days)*2) : 500*days;
    }
};
bool operator < (Camera & left, Camera & right){
    return left.price() < right.price();
}
double production(Camera **p, int n, int days){
    double total = 0.0;
        for(int i = 0; i < n; i++){
            total+=p[i]->rentalPrice(days);
        }
    return total;
}
char * mostExpensiveCamera(Camera **p, int n){
    Camera *tmp = p[0];
    for(int i = 1; i < n; i++){
        if(*tmp < *p[i]){
            tmp = p[i];
        }
    }
    return tmp->getModel();
}

int main(int argc, char *argv[])
{
    // Variables for reading input
    char model[20], producer[20];
    int year, length, fps, n;
    float resolution;
    bool raw;

    int t;

    // Array of cameras
    Camera *c [10];

    // Read number of cameras
    cin>>n;

    for(int i = 0; i < n; ++i){

        // Camera type: 1 - Photo, 2 - Video, 3 - Film
        cin>>t;

        if (t==1){
            cin >> producer >> model >> year >> resolution;
            cin >> raw;
            c[i] = new PhotoCamera(producer, model, year, resolution, raw);
        }
        else if (t==2){
            cin >> producer >> model >> year >> resolution;
            cin >> length;
            c[i] = new VideoCamera(producer, model, year, resolution, length);
        }
        else if (t==3){
            cin >> producer >> model >> year >> resolution;
            cin >> fps;
            c[i] = new FilmCamera(producer, model, year, resolution, fps);
        }
    }


    // Production days
    int days;
    cin >> days;


    cout<< "Price of production is: " << production(c, n, days) << endl;
    cout<< "Most expensive camera used in production is: " << mostExpensiveCamera(c, n);


    return 0;
}

