#include "vec3.h"
#include <math.h>

vec3::vec3( const vec3 &in )
{
//	y = in.y;
//	data = new double[y];
	for( int i = 0; i < 3; i++ )
		this->data[i] = in.data[i];
}

vec3::vec3()
{
	//y = DEFAULT_vec3;
	//data = new double[DEFAULT_vec3];
}

vec3::vec3( double x, double y, double z )
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}
vec3& vec3::operator= (const vec3 &rhs)
{
	if (this == &rhs)      // Same object?
      return *this;        
/*
	if( y != rhs.y )
	{
		vec3 *bad = new vec3(0);
		return *bad;
	}
*/
	for( int i = 0; i < 3; i++ )
	{
		this->data[i] = rhs.data[i];
	}

	return *this;
}


const double vec3::operator[] (const int index) const
{
	return data[index];
}

double& vec3::operator[] (const int index)
{
	return data[index];
}
double vec3::mag( void )
{
	double ret = 0;
	for( int i = 0; i < 3; i++ )
	{
		ret += data[i]*data[i];
	}

	ret = sqrt( ret );
	return ret;
}

double vec3::dot( vec3 &rhs )
{

	vec3 tmp = (*this)*rhs;
	double ret = 0;

	for( int i = 0; i < 3; i++ )
		ret += tmp[i];

	return ret;
		
}

vec3 vec3::operator *( const vec3 &rhs)
{
	vec3 ret;

	for( int i = 0; i < 3; i++ )
		ret.data[i] = data[i] * rhs.data[i];

	return ret;
}

vec3 vec3::operator* ( double rhs )
{
	vec3 ret;
	for( int i = 0; i < 3; i++ )
	{
		ret.data[i] = data[i] * rhs;
	}
	return ret;
}

vec3 vec3::operator/ ( double rhs )
{
	vec3 ret;// = new vec3(y);
	for( int i = 0; i < 3; i++ )
	{
		ret.data[i] = data[i] / rhs;
	}
	return ret;
}

const vec3 vec3::operator+ ( const vec3 &rhs ) const
{
	vec3 ret;// = new vec3(y);
	for( int i = 0; i < 3; i++ )
	{
		ret.data[i] = data[i] + rhs.data[i];
	}
	return ret;
}
const vec3 vec3::operator- ( const vec3 &rhs ) const
{
	vec3 ret;// = new vec3(3);
	for( int i = 0; i < 3; i++ )
	{
		ret.data[i] = data[i] - rhs.data[i];
	}
	return ret;
}
const vec3 vec3::operator+ ( const double rhs ) const
{
	vec3 ret;// = new vec3(y);
	for( int i = 0; i < 3; i++ )
	{
		ret.data[i] = data[i] + rhs;
	}
	return ret;
}
vec3 cross( const vec3 &left, const vec3 &right )
{
	vec3 ret;
	ret.data[0] = left[1] * right[2] - left[2]*right[1];
	ret.data[1] = left[2] * right[0] - left[0] * right[2];
	ret.data[2] = left[0] * right[1] - left[1] * right[0];
	return ret;
}

void vec3::normalize( void )
{
	double mag = this->mag();
	data[0] = data[0] / mag;
	data[1] = data[1] / mag;
	data[2] = data[2] / mag;
}
