#include<iostream>
#include<cstring>
using namespace std;

class Recipe {
private:
    int in;
    char name [100];
    char * content;

    void copy (const Recipe &r) {
        this->in=r.in;
        strcpy(this->name, r.name);
        this->content=new char [strlen(r.content)+1];
        strcpy(this->content, r.content);
    }
public:
    Recipe ( ) {
        this->in=0;
        strcpy(this->name, " ");
    }
    Recipe (int in, char * name, char * content) {
        this->in=in;
        strcpy(this->name, name);
        this->content=new char [strlen(content)+1];
        strcpy(this->content, content);
    }
    Recipe (const Recipe &r) {
        copy (r);
    }
    void set_num_ing(int in) {
        this->in=in;
    }
    void set_name (char * name) {
        strcpy(this->name, name);
    }
    void set_contents(char * contents) {
        strcpy(this->content, contents);
    }
    int getin () {
        return in;
    }
    Recipe & operator ++ () {
        ++this->in;
        return *this;
    }
    Recipe operator ++ (int) {
        Recipe copy (*this);
        ++this->in;
        return copy;
    }
    void print() {
        cout<<in<<endl;
        cout<<name<<endl;
        cout<<content<<endl;
    }
    bool Eq (Recipe r) {
        return (strcmp(this->name,r.name)==0);
    }
};
class RecipesBook {
private:
    char name [100];
    Recipe * recipies;
    int size;
    void copy (const RecipesBook &r) {
        strcpy(this->name, r.name);
        this->recipies = new Recipe [r.size];
        for (int i=0;i<r.size;i++)
            recipies[i]=r.recipies[i];
        this->size=r.size;
    }
public:
    RecipesBook (char * name = " ") {
        strcpy(this->name, name);
        recipies = new Recipe [0];
        size = 0;
    }
    RecipesBook (const RecipesBook &r) {
        copy(r);
    }
    void setName (char * name) {
        strcpy(this->name, name);
    }
    void add (Recipe & r) {
        for (int i=0; i<size; i++) {
            if (recipies[i].Eq(r)) {
                return ;
            }
        }
        Recipe * tmp = new Recipe [size+1];

        for (int i=0; i<size; i++) {
            tmp[i] = recipies[i];
        }
        tmp[size++] = r;
        delete [] recipies;
        recipies = tmp;
    }
    void print () {
        cout<<name<<endl;
        for (int i=0; i<size; i++)
            recipies[i].print();
    }
    RecipesBook novaBrosura(Recipe &r) {
        RecipesBook newbook;
        newbook.setName(this->name);
        Recipe tmp;
        for(int i=0; i<size; i++) {
            if(recipies[i].getin()<r.getin()) {
                tmp =recipies[i];
                tmp++;
                newbook.add(tmp);
            }
        }
        return newbook;
    }
    ~ RecipesBook () {
        delete [] recipies;
    }
};
int main() {
    Recipe rec;
    int n;
    char name[100], contents[200];
    int num_ing;
    cin >> name >> n;
    RecipesBook b1(name);
    Recipe last;
    for(int i = 0; i < n; i++) {
        cin >> num_ing >> name >> contents;
        Recipe r(num_ing, name, contents);
        b1.add(r);
        last = r;
    }
    b1.print();
    cin >> num_ing >> name >> contents;
    rec.set_num_ing(num_ing);
    rec.set_name(name);
    rec.set_contents(contents);
    b1.add(rec);
    b1.print();
    RecipesBook b2 = b1.novaBrosura(rec);
    b2.print();
    // testing copy constructor
    cout << "b2 copy" << endl;
    RecipesBook rb = b2;
    last.set_name("changed-name");
    rb.add(last);
    rb.print();
    cout << "original" << endl;
    b2.print();
    return 0;
}