#include <string>

class vec3 {
public:
	double data[3];
	explicit vec3();
	vec3( const vec3 &in );
	//~vec3( void );
	vec3( const double x, const double y, const double z );
	vec3& operator= (const vec3 &rhs);
	vec3 operator* ( const vec3 &rhs );
	vec3 operator* ( double rhs );
	vec3 operator/ ( double rhs );
	const vec3 operator+ ( const vec3 &rhs ) const;
	const vec3 operator- ( const vec3 &rhs ) const;
	const vec3 operator+ ( const double rhs ) const;
	const double operator[] ( const int index ) const;
	double& operator[] ( const int index );
	double mag( void );
	double dot( vec3 &rhs );
	void rot_y( double theta );
	void rot_x( double theta );
	void normalize( void );
	std::string str(void) const;
};
vec3 cross( const vec3 &left, const vec3 &right );
