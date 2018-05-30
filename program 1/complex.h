//
//  complex.h
//  Program 1
//
//  Created by Jerryshen on 4/11/17.
//  Copyright © 2017 Zeyu. All rights reserved.
//

#ifndef complex_h
#define complex_h
#include <iostream>
using namespace std;

class complex{
public:
    complex(double=0.0, double=0.0);// default constructor
    double getReal();    // return real part
    double getImaginary();// return imaginary part
    complex conjugate();  // return the conjugate of a complex number
    
    // Math Operators
    complex operator+(const complex &) const; // add 2 complex numbers
    complex operator-(const complex &) const; // subtract 2 complex numbers
    complex operator*(const complex &) const; // multiply 2 complex numbers
    complex operator/(const complex &) const; // divide 2 complex numbers
    
    // Comparison Operatot
    bool operator==(const complex &) const;// is object == parameter?
    bool operator!=(const complex &) const;//is object != parameter?
    
    // Assignment Operators
    complex&operator+=(const complex &); // current object += parameter
    complex&operator-=(const complex &); // current object -= parameter
    complex&operator*=(const complex &); // current object *= parameter
    complex&operator/=(const complex &); // current object /= parameter
    
    //Input & Output System
    friend ostream& operator<<(ostream&, const complex&); 
    friend istream& operator>>(istream&, complex&);
    
    
private:
    double X;//real part
    double Y;//imaginary part
    
    
};

#endif /* complex_h */
