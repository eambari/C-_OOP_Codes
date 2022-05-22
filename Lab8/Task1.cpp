/*
Created by Endrit Ambari on 2022.
*/
#include<iostream>
#include<cstring>
using namespace std;

class Course{
private:
    char name[50];
    int classes;
    float students;
    void copy(const Course &other){
        strcpy(this->name, other.name);
        this->classes = other.classes;
        this->students = other.students;
    }
public:
    Course(char *name = " ", int classes = 0, float students = 0.0){
        strcpy(this->name, name);
        this->classes = classes;
        this->students = students;
    }
    Course(const Course &other){
        copy(other);
    }
    Course &operator=(const Course &other){
        if(this != &other){
            copy(other);
        }
        return *this;
    }
    int getClasses(){
        return classes;
    }
    float getStudents(){
        return students;
    }
};
class TeachingStaff{
protected:
    char name[50];
    static int value;
    Course courses[4];
    int size;
public:
    TeachingStaff(char *name, Course *courses, int size){
        strcpy(this->name, name);
        this->size = size;
        for(int i = 0; i < size; i++){
            this->courses[i] = courses[i];
        }
    }
    static void setValue(int other){
        value = other;
    }
    static int getValue(){
        return value;
    }
    char * getName(){
        return name;
    }
    virtual int salary() = 0;
};

int TeachingStaff::value = 50;

class Professor: public TeachingStaff{
private:
    const int fixedPart = 30000;
    const float coefficient = 1.0;
public:
    Professor(char *name = "", Course courses[4] = 0, int size = 0): TeachingStaff(name, courses, size){}
    int salary() override {
        int salary = 0;
        for(int i = 0; i < size; i++){
            salary += courses[i].getClasses() * courses[i].getStudents();
        }
        return fixedPart+((salary*coefficient)*TeachingStaff::getValue());
    }
};
class AssistantProfessor: public TeachingStaff{
private:
    const int fixedPart = 24000;
    const float coefficient = 0.8;
public:
    AssistantProfessor(char *name = "", Course courses[4] = 0, int size = 0): TeachingStaff(name,courses, size){}
    int salary() override {
        int salary = 0;
        for(int i = 0; i < size; i++){
            salary += courses[i].getClasses() * courses[i].getStudents();
        }
        return fixedPart+((salary*coefficient)*TeachingStaff::getValue());
    }
};
class Assistant: public TeachingStaff{
private:
    const int fixedPart = 18000;
    const float coefficient = 0.6;
public:
    Assistant(char *name = "", Course courses[4] = 0, int size = 0): TeachingStaff(name,courses, size){}
    int salary() override {
        int salary = 0;
        for(int i = 0; i < size; i++){
            salary += courses[i].getClasses() * courses[i].getStudents();
        }
        return fixedPart+((salary*coefficient)*TeachingStaff::getValue());
    }
};
void highestSalary (TeachingStaff ** teachers, int n) {
    int professorSalary, assistantProfessorSalary, assistantSalary;
    int professor, assistantProfessor, assistant;
    for (int i = 0; i < n; i++) {
        Professor *t = dynamic_cast<Professor *>(teachers[i]);
        if (t != nullptr) {
            if (teachers[i]->salary() > professorSalary) {
                professorSalary = teachers[i]->salary();
                professor = i;
            }
        }
        AssistantProfessor *ap = dynamic_cast<AssistantProfessor *>(teachers[i]);
        if (ap != nullptr) {
            if (teachers[i]->salary() > assistantProfessorSalary) {
                assistantProfessorSalary = teachers[i]->salary();
                assistantProfessor = i;
            }
        }
        Assistant *a = dynamic_cast<Assistant *>(teachers[i]);
        if (a != nullptr) {
            if (teachers[i]->salary() > assistantSalary) {
                assistantSalary = teachers[i]->salary();
                assistant = i;
            }
        }
    }
    Professor *printProf = dynamic_cast<Professor*>(teachers[professor]);
    cout << printProf->getName() << endl;
    AssistantProfessor *printAssistantProf = dynamic_cast<AssistantProfessor*>(teachers[assistantProfessor]);
    cout << printAssistantProf->getName() << endl;
    Assistant *printAssistant = dynamic_cast<Assistant*>(teachers[assistant]);
    cout << printAssistant->getName() << endl;
}
int main(){
    int test;
    cin >> test;
    if(test == 1){
        cout << "==== Testing class Course ====" << endl;
        int noClasses;
        int noStudents;
        char course[50];
        cin.getline(course, 50);
        cin >> noClasses >>noStudents;
        Course p(course,noClasses,noStudents);
        cout << "==== class Course OK ====" << endl;
    }
    else if(test == 2){

        cout << "==== Testing class Profesor ====" << endl;
        char name[50];
        int n;
        Course courses[4];
        int noClasses;
        int noStudents;
        char course[50];
        cin >> n;
        cin.getline(name, 50);
        for(int i = 0; i < n; i++){
            cin.getline(course, 50);
            cin.ignore(50,'\n');
            cin >> noClasses >> noStudents;
            Course p(course, noClasses, noStudents);
            courses[i] = p;
        }
        Professor prof(name, courses, n);
        cout << prof.salary();
    }
    else if(test == 3){

        cout << "==== Testing class Docent ====" << endl;
        char name[50];
        int n;
        Course courses[4];
        int noClasses;
        int noStudents;
        char course[50];
        cin >> n;
        cin.getline(name, 50);
        for(int i = 0; i < n; i++){
            cin.getline(course, 50);
            cin.ignore(50,'\n');
            cin >> noClasses >> noStudents;
            Course p(course, noClasses, noStudents);
            courses[i] = p;
        }
        AssistantProfessor d(name, courses, n);
        cout << d.salary();

    }
    else if(test == 4){

        cout << "==== Testing class Asistent ====" << endl;
        char name[50];
        int n;
        Course courses[4];
        int noClasses;
        int noStudents;
        char course[50];
        cin >> n;
        cin.getline(name, 50);
        for(int i = 0; i < n; i++){
            cin.getline(course, 50);
            cin.ignore(50, '\n');
            cin >> noClasses >> noStudents;
            Course p(course, noClasses, noStudents);
            courses[i] = p;
        }
        Assistant a(name, courses, n);
        cout << a.salary();

    }
    else if(test == 5){

        cout << "==== Testing static variable and abstract class TeachingStaff ====" << endl;
        TeachingStaff *teachers[3];
        int n, noClasses, noStudents;
        char course[50];
        Course courses[4];
        cin >> n;
        for(int i = 0; i < n; i++){
            cin.getline(course, 50);
            cin.ignore(50, '\n');
            cin >> noClasses >> noStudents;
            Course p(course, noClasses, noStudents);
            courses[i] = p;
        }
        teachers[0] = new Professor("Dejan Gjorgjevikj", courses, n);
        teachers[1] = new AssistantProfessor("Hristina Mihajloska", courses, n);
        teachers[2] = new Assistant("Aleksandar Tenev", courses, n);
        for(int i = 0; i < 3; i++){
            cout << teachers[i]->salary() << endl;
        }
        cout << "==== Changing the point value ====" << endl;
        TeachingStaff::setValue(55);
        for(int i = 0; i < 3; i++){
            cout << teachers[i]->salary() << endl;
        }

    }
    else if(test == 6){

        cout << "==== Testing global function ====" << endl;
        TeachingStaff *teachers[5];
        int n, noClasses, noStudents;
        char course[50], name[50];
        Course courses[4];
        for(int j = 0; j < 5; j++){
            cin >> n;
            for(int i = 0; i < n; i++){
                cin.getline(course, 50);
                cin.ignore(50,'\n');
                cin >> noClasses >> noStudents;
                Course p(course, noClasses, noStudents);
                courses[i] = p;
            }
            cin.ignore(50,'\n');
            cin.getline(name, 50);
            if(j%3 == 0){
                teachers[j] = new Professor(name, courses, n);
            }
            else if(j%3 == 1){
                teachers[j] = new AssistantProfessor(name, courses, n);
            }
            else{
                teachers[j] = new Assistant(name, courses, n);
            }
        }
        //for(int i = 0; i < 5; i++)
        //	cout << teachers[i]->getName() << endl;
        highestSalary(teachers, 5);
    }
    return 0;
}
