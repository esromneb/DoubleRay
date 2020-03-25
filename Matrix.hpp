#pragma once

class Matrix {
public:
    int x;
    int y;
    Matrix( int xin, int yin );
    ~Matrix( void );
//    vec operator* ( vec &rhs );
    double ** data;
    double det( void );
    Matrix *m1, *m2, *m3;
};
