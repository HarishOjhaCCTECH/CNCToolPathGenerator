#pragma once

class Triangle {
public:
    Triangle();
    Triangle(int v1, int v2, int v3);
    ~Triangle();

    int v1()const;
    int v2()const;
    int v3()const;

private:
    int mv1; // vertex 1
    int mv2; // vertex 2
    int mv3; // vertex 3
};