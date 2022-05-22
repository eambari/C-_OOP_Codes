/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include <cstring>
using namespace std;

class IndexOutOfBounds{
private:
    int i;
public:
    IndexOutOfBounds(int i){
        this->i = i;
    }
    void printMessage(){
        cout << "Index '" << i << "' is out of bounds" << endl;
    }
};

class String{
private:
    char *chars;
    int length;

    void copy(const String &other){
        this->length = other.length;
        this->chars = new char [other.length];
        strcpy(this->chars, chars);
    }
public:
    String(char *chars = " "){
        this->length = strlen(chars)+1;
        this->chars = new char [length];
        strcpy(this->chars, chars);
    }
    String (const String &other){
        copy(other);
    }
    String &operator=(const String &other){
        if(this != &other){
            delete [] chars;
            copy(other);
        }
        return *this;
    }
    char &operator [](int i){
        if(i < 0 || i > length-2){
            throw IndexOutOfBounds(i);
        }
        return chars[i];
    }
    friend ostream &operator<<(ostream &out, const String &s){
        return out << s.chars;
    }
    int getLength() const{
        return length;
    }
    char * getString() const{
        return chars;
    }
};

class StringBuilder{
private:
    char *chars;
    int size;
    int capacity;
public:
    StringBuilder(int capacity = 0){
        this->capacity = capacity;
        this->size = 0;
        chars = new char [0];
    }
    StringBuilder(const StringBuilder &other){
        this->capacity = other.capacity;
        this->size = other.size;
        chars = new char [other.size+1];
        strcpy(this->chars, other.chars);
    }
    /*StringBuilder &operator+=(const String &other){
        if(capacity > size + other.getLength()){
            strcat(chars, other.getString());
            size += other.getLength();
            return *this;
        } else {
            capacity *= 2;
            if(capacity < size + other.getLength()){
                capacity = size + other.getLength()+1;
            }
            char *tmp = new char [size += other.getLength()];
            strcpy(tmp,chars);
            strcat(tmp,other.getString());
            delete [] chars;
            chars = tmp;
            return *this;
        }
    }
     */
    StringBuilder & operator +=(const String & s){
        if(size+strlen(s.getString())>=capacity){
            strcat(chars,s.getString());

            if(size+strlen(s.getString())>capacity*2)
                capacity=size+strlen(s.getString());
            else
                capacity*=2;
            size=strlen(chars);
            return *this;
        }

        else {
            strcat(chars,s.getString());
            size=strlen(chars);
            return *this;
        }
    }
    friend ostream &operator<<(ostream &out, const StringBuilder &sb){
        out<<"Capacity: "<<sb.capacity<<endl;
        out<<"Size: "<<sb.size<<endl;
        return out<<"Contents: "<<sb.chars;
    }

};
int main() {
    int n;
    cin >> n;
    StringBuilder sb(n);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        char input[100];
        cin >> input;
        String s(input);
        int x;
        cin >> x;
        try {
            cout << "s[" << x << "] = " << s[x] << endl;
            sb += s;
        } catch (IndexOutOfBounds i){
            i.printMessage();
        }
    }
    cout << sb;
    return 0;
}