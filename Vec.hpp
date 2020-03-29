#pragma once

#include <string>

class Vec {
public:
    static const int x = 1; // the x dimension, forced to 1 (and never used)
    int y = 3; // the y dimension, must match DEFAULT_VEC // fixme change to unsigned
    double *data;
    explicit Vec(); //default will be DEFAULT_VEC
    Vec( const Vec &in );
    ~Vec( void );
    Vec( int yin );
    Vec& operator= (const Vec &rhs);
    Vec operator* ( Vec &rhs );
    Vec operator* ( double rhs );
    Vec operator/ ( double rhs );
    Vec operator+ ( Vec &rhs );
    Vec operator- ( Vec &rhs );
    double operator[] (int index);
    double mag( void );
    double dot( Vec &rhs );
    void rot_y( double theta );
    void rot_x( double theta );
    static const unsigned DEFAULT_VEC = 3;
    std::string str(bool vertical = false) const;
};

Vec cross( Vec &left, Vec &right ); // fixme move to static
