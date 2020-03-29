#include "Vec.hpp"
#include "Matrix.hpp"

#include <math.h>

using namespace std;

Vec::Vec( const Vec &in )
{
    y = in.y;
    data = new double[y];
    for( int i = 0; i < y; i++ )
        this->data[i] = in.data[i];
}

Vec::Vec( int yin ): y(yin)
{
    data = new double[yin];
}

Vec::Vec()
{
    y = DEFAULT_VEC;
    data = new double[DEFAULT_VEC];
}
Vec& Vec::operator= (const Vec &rhs)
{
    if (this == &rhs)      // Same object?
      return *this;        

    if( y != rhs.y )
    {
        Vec *bad = new Vec(0);
        return *bad;
    }

    for( int i = 0; i < y; i++ )
    {
        this->data[i] = rhs.data[i];
    }

    return *this;
}
Vec Vec::operator *(Vec &rhs)
{

    if( y != rhs.y )
    {
        Vec bad(0);// = new Vec(0);
        return bad;
    }

    Vec ret(y);// = new Vec(y);

    for( int i = 0; i < y; i++ )
        ret.data[i] = data[i] * rhs.data[i];

    return ret;
}

double Vec::operator[] (int index)
{
    return data[index];
}

double Vec::mag( void )
{
    double ret = 0;
    for( int i = 0; i < y; i++ )
    {
        ret += data[i]*data[i];
    }

    ret = sqrt( ret );
    return ret;
}

double Vec::dot( Vec &rhs )
{
    if( y != rhs.y )
    {
        return 0;
    }

    Vec tmp = (*this)*rhs;
    double ret = 0;

    for( int i = 0; i < y; i++ )
        ret += tmp[i];

    return ret;
        
}
Vec Vec::operator* ( double rhs )
{
    Vec ret(y);// = new Vec(y);
    for( int i = 0; i < y; i++ )
    {
        ret.data[i] = data[i] * rhs;
    }
    return ret;
}

Vec Vec::operator/ ( double rhs )
{
    Vec ret(y);// = new Vec(y);
    for( int i = 0; i < y; i++ )
    {
        ret.data[i] = data[i] / rhs;
    }
    return ret;
}

Vec Vec::operator+ ( Vec &rhs )
{
    if( y != rhs.y )
    {
        Vec bad(0);// = new Vec(0);
        return bad;
    }
    Vec ret(y);// = new Vec(y);
    for( int i = 0; i < y; i++ )
    {
        ret.data[i] = data[i] + rhs.data[i];
    }
    return ret;
}
Vec Vec::operator- ( Vec &rhs )
{
    if( y != rhs.y )
    {
        Vec bad(0);// = new Vec(0);
        return bad;
    }
    Vec ret(y);// = new Vec(y);
    for( int i = 0; i < y; i++ )
    {
        ret.data[i] = data[i] - rhs.data[i];
    }
    return ret;
}

Vec cross( Vec &left, Vec &right )
{

    if( left.y != right.y || left.y != 3 )
    {
        Vec bad(0);// = new Vec(0);
        return bad;
    }

    Vec ret(3);
    ret.data[0] = left[1] * right[2] - left[2]*right[1];
    ret.data[1] = left[2] * right[0] - left[0] * right[2];
    ret.data[2] = left[0] * right[1] - left[1] * right[0];
    return ret;


}

void Vec::rot_y( double theta )
{
    Vec orig(4), transformed(4);
    Matrix rotM( 4, 4 );

    orig.data[3] = 1;

    rotM.data[0][0] = cos( theta );
    rotM.data[1][0] = 0;
    rotM.data[2][0] = sin(theta);;
    rotM.data[3][0] = 0;


    rotM.data[0][1] = 0;
    rotM.data[1][1] = 1;
    rotM.data[2][1] = 0;
    rotM.data[3][1] = 0;

    rotM.data[0][2] = -1*sin( theta );;
    rotM.data[1][2] = 0;
    rotM.data[2][2] = cos(theta);
    rotM.data[3][2] = 0;

    rotM.data[0][3] = 0;
    rotM.data[1][3] = 0;
    rotM.data[2][3] = 0;
    rotM.data[3][3] = 1;

    orig.data[0] = data[0];
    orig.data[1] = data[1];
    orig.data[2] = data[2];

    transformed = rotM*orig;

    data[0] = transformed[0];
    data[1] = transformed[1];
    data[2] = transformed[2];
}


void Vec::rot_x( double theta )
{
    Vec orig(4), transformed(4);
    Matrix rotM( 4, 4 );

    orig.data[3] = 1;

    rotM.data[0][0] = 1;
    rotM.data[1][0] = 0;
    rotM.data[2][0] = 0;
    rotM.data[3][0] = 0;


    rotM.data[0][1] = 0;
    rotM.data[1][1] = cos(theta);
    rotM.data[2][1] = -1*sin( theta );
    rotM.data[3][1] = 0;

    rotM.data[0][2] = 0;
    rotM.data[1][2] = sin(theta);;
    rotM.data[2][2] = cos( theta );
    rotM.data[3][2] = 0;

    rotM.data[0][3] = 0;
    rotM.data[1][3] = 0;
    rotM.data[2][3] = 0;
    rotM.data[3][3] = 1;

    orig.data[0] = data[0];
    orig.data[1] = data[1];
    orig.data[2] = data[2];

    transformed = rotM*orig;

    data[0] = transformed[0];
    data[1] = transformed[1];
    data[2] = transformed[2];
}

std::string Vec::str(void) const {
    return std::string("");
}

Vec::~Vec( void )
{
    if( data && y != 0)
        delete data;
}
