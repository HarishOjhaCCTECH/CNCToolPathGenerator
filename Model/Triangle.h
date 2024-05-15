// this is header file for class Triangle
// purpose - its vertices contains the index position(address) of the points(stored in vector)
#pragma once
class Triangle {
public:
    Triangle(); // default constructor
    Triangle(int v1, int v2, int v3); // parameterized constructor
    ~Triangle(); // destructor
    int v1()const; // getter
    int v2()const; // getter
    int v3()const; // getter
private:
    int mv1; // vertex 1
    int mv2; // vertex 2
    int mv3; // vertex 3
};