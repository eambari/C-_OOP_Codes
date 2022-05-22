/*
Created by Endrit Ambari on 2022.
*/
#include <iostream>
#include<cstring>
using namespace std;
// your code here
class Matrix {
private:
    int m;
    int n;
    float mat[10][10];
public:
    Matrix(){};
    Matrix(int m, int n)
    {
        this->m=m;
        this->n=n;
        for(int i=0;i<m;i++)
        {
        for(int j=0; j<n; j++)
         {
            this->mat[i][j]=0;

            }
        }
    }
    Matrix(int m,int n,float mat) {
        this->m=m;
        this->n=n;
    }
    Matrix(const Matrix &x) {
        this->m=x.m;
        this->n=x.n;
        for(int i=0;i<x.m;i++)
            for(int j=0;j<x.n;j++)
            this->mat[i][j]=x.mat[i][j];
    }
    Matrix & operator +(int scalar) {
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                mat[i][j]+=scalar;
            }
        }
        return *this;
    }
    Matrix & operator -(const Matrix &x) {
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                this->mat[i][j]-=x.mat[i][j];
            }
        }
        return *this;
    }
    Matrix operator *(const Matrix &x) {
       Matrix  newMatrix(this->m,this->n);

       for(int i=0;i<m; i++)
        {
        for(int j=0;j<n; j++)

         {
            for(int t=0; t<n; t++){

           newMatrix.mat[i][j]+=this->mat[i][t]*x.mat[t][j];
            }

            }
        }
        return newMatrix;
    }
    friend istream &operator >>(istream &in, Matrix &x) {
        in>>x.m;
        in>>x.n;
        for(int i=0; i<x.m; i++) {
            for(int j=0; j<x.n; j++) {
                in>>x.mat[i][j];
            }
        }
        return in;
    }
    friend ostream &operator <<(ostream &out, const Matrix &x){
    for(int i=0; i<x.m; i++) {
            for(int j=0; j<x.n; j++) {
                out<<x.mat[i][j]<<" ";
            }
        out<<endl;
        }
        return out;
    }
};
int main() {
    Matrix A,B,C;
    cin >> A >> B >> C;
    Matrix D = B * C;
    Matrix R = A - D + 2;
    cout << R;
}
