//
//  complex.cpp
//  Program 1
//
//  Created by Jerryshen on 4/11/17.
//  Copyright © 2017 Zeyu. All rights reserved.
//
#include "complex.h"

//------------------------------ Complex ------------------------------------
// default constructor:  parameters are real part and imaginary part
complex::complex(double r, double i){
    X=r;
    Y=i;
}

//------------------------------ getReal ------------------------------------
// return the real part
double complex::getReal(){
    return X;
}

//------------------------------ getImaginary -------------------------------
// return the imaginary pary
double complex::getImaginary(){
    return Y;
}

//------------------------------ conjugate -------------------------------
// return the conjugate object
complex complex::conjugate(){
    complex Ncomplex(X,-Y);
    return Ncomplex;
}

// Math Operators
//------------------------------- operator+ --------------------------------
// return the sum of the object add parameter
complex complex:: operator+(const complex & a) const{
    complex sum;
    sum.X = X + a.X;
    sum.Y = Y + a.Y;
    return sum;
}

//------------------------------- operator- --------------------------------
// return the object minus parameter
complex complex::operator-(const complex & a) const{ // object minus parameter
    complex sub;
    sub.X = X - a.X;
    sub.Y = Y - a.Y;
    return sub;
}

//------------------------------- operator* --------------------------------
// return the product of object and parameter
complex complex::operator*(const complex & a) const{ // multiply 2 complex numbers
    complex pod;
    pod.X = X * a.X - Y * a.Y;
    pod.Y = Y* a.X - X * a.Y;
    return pod;
}

//------------------------------- operator/ --------------------------------
// return the divison of object and parameter
complex complex::operator/(const complex & a) const{ // divide 2 complex numbers
    complex div;
    if(a.X==0 && a.Y==0){
        cout<<"(DIVIDE BY ZERO ERROR!!!)";
        return *this;
    }
    div.X=(X*a.X + Y*a.Y)/(a.X*a.X + a.Y*a.Y);
    div.Y=(Y*a.X - X*a.Y)/(a.X*a.X + a.Y*a.Y);
    return div;
}

// Comparison Operatot
//------------------------------- operator== --------------------------------
// is object == parameter?
// return true when the object == parameter
bool complex::operator==(const complex & a) const{
    return (X==a.X&&Y==a.Y);
}
//------------------------------- operator!= --------------------------------
//is object != parameter?
// return true when the object != the parameter
bool complex::operator!=(const complex & a) const{
    return !(X==a.X&&Y==a.Y);
}

// Assignment Operators
//------------------------------- operator+= --------------------------------
// return current object += parameter
complex& complex::operator+=(const complex & a){
    *this = *this + a;
    return *this;
}

//------------------------------- operator-= --------------------------------
// return current object -= parameter
complex& complex::operator-=(const complex & a){
    *this = *this - a;
    return *this;
}

//------------------------------- operator*= --------------------------------
// return current object *= parameter
complex& complex::operator*=(const complex & a){
    *this = *this * a;
    return *this;
}

//------------------------------- operator/= --------------------------------
// return current object /= parameter
complex& complex::operator/=(const complex & a){ // current object /= parameter
    *this = *this / a;
    return *this;
}


//Input & Output System
//------------------------------- output --------------------------------
// case 1: imaginary part is 0, only output real part
// case 2: real part is 0, only output imaginary part
// case 3: if imaginary part greater than 0, add a "+" sign between two part,then return
// case 4: otherwise output a.X a.Y(which imaginary part is <0)
ostream& operator<<(ostream&output, const complex& a){
    if (a.Y==0.0)
        output << a.X;
    else if(a.X==0.0)
        output << a.Y << "i";
    else if(a.Y>=0.0)
        output << a.X << "+" << a.Y << "i";
    else
        output << a.X << a.Y << "i";
    return output;
}
//------------------------------- input --------------------------------
// first, input the real part to a.X
// secondly, input the imaginaty part to a.Y
istream& operator >> (istream& i, complex& a)
{
    i >> a.X;
    i >> a.Y;
    return i;
}
