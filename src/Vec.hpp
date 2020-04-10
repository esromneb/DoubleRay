#pragma once

#include <string>

class Vec {
public:
    static const int x = 1; // the x dimension, forced to 1 (and never used)
    int y = 3; // the y dimension, must match DEFAULT_VEC // fixme change to unsigned
    double *data = 0;
    explicit Vec(); //default will be DEFAULT_VEC
    Vec( const Vec &in );
    virtual ~Vec( void );
    Vec( int yin );
    Vec& operator= (const Vec &rhs);
    Vec operator* ( const Vec &rhs ) const;
    Vec operator* ( double rhs );
    Vec operator/ ( double rhs );
    Vec operator+ ( Vec &rhs );
    Vec operator- ( Vec &rhs );
    double operator[] (int index);
    double mag( void ) const;
    double dot( const Vec &rhs ) const;
    void rot_y( const double theta );
    void rot_x( const double theta );
    void rot_z( const double theta );
    static const unsigned DEFAULT_VEC = 3;
    std::string str(bool vertical = false) const;
    template <bool degrees = true>
    static double angle(const Vec &v0, const Vec &v1);
};

Vec cross( Vec &left, Vec &right ); // fixme move to static
