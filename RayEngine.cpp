#include "RayEngine.hpp"
#include <math.h>
#include <iostream>
#include <tuple>

RayEngine::RayEngine( void )
{
    numPoly = 0;
    this->polygons.resize(POLYGONS);
    // this->hits.resize(POLYGONS+30);

    r = g = b = 0;
    px = 0;
    makeObjects();

    mat = new Matrix( 3, 3 );
    mat->m1 = new Matrix( 2, 2 );
    mat->m2 = new Matrix( 2, 2 );
    mat->m3 = new Matrix( 2, 2 );
    
}

void RayEngine::makeObjects( void )
{
    // scene1();
    // scene2();
    // scene3();
}

void RayEngine::paint( void )
{

}

void RayEngine::resize( const int _x )
{
    px = _x;
    if( r && g && b )
    {
        delete r;
        delete g;
        delete b;
    }

    r = new float[_x*_x];
    g = new float[_x*_x];
    b = new float[_x*_x];
}

int g_i = 0;
int g_j = 0;

bool g_print = false;

void RayEngine::render( void )
{
    // bool nUsedB = false;
    // Vec3 nUsedI;
    Ray r;
    Vec3 pixel;
    double cu,cv;
    //float red, green, blue;
    Vec3 color;

    Vec3 e = camera.o;
    Vec3 a = e + camera.d;
    Vec3 w = e-a;
    w.normalize();

    Vec3 u = Vec3::cross( up, e-a );
    u.normalize();
    Vec3 v = Vec3::cross( w, u );

    for( int j = 0; j < px; j++ )
        for( int i = 0; i < px; i++ )
        {
            cu = ((2.0f*i + 1)/(2.0f*px) - 0.5f);
            cv = ((2.0f*j + 1)/(2.0f*px) - 0.5f);
            pixel = a + u*cu + v*cv;
            r.o = e;
            r.d = pixel-e;
            r.d.normalize();
            //red = green = blue = 0;
            g_i = i;
            g_j = j;

            if( (i > il && i < ih) && (j > jl && j < jh ) ) {

                g_print = false;
                if( (i >= 198 && i < 200) && (j > 198 && j < 200)) {
                    g_print = true;
                }

                trace( r, 0, color, false );
                if( print ) {
                    cout << "\n Final: " << color[0] << "\n";
                }
            } else {
                color = Vec3(0,0,0);
            }

            this->r[i+j*px] = color[0];
            this->g[i+j*px] = color[1];
            this->b[i+j*px] = color[2];

        }
}

// Vec3 intersect;
// Vec3 norm;
// Vec3 refl;
// Vec3 fp;

std::tuple<Vec3, Vec3, Vec3, Vec3> intersectSphere(const Ray& r, const Sphere &s, const double t0) {
    Vec3 intersect;
    Vec3 norm;
    Vec3 refl;
    Vec3 fp;

    intersect = r.pointAt(t0);

    const double srInverse = 1.0f/s.r;


    norm = Vec3( ( intersect[0] - s.c[0] )*srInverse, ( intersect[1] - s.c[1] )*srInverse, ( intersect[2] - s.c[2] )*srInverse );
    //norm = intersect - s.c;
    norm.normalize();

    //refl = r.d - norm * 2 * (camera.d.dot(norm));
    // refl = norm*2* norm.dot( r.d ) - r.d;
    refl = Vec3::reflect(r.d, norm);

    //lighting
    fp = r.o - intersect;

    return {intersect, norm, refl, fp};
}

#define NO_HIT ((double)9999999)

#define HIT_SPHERE ((uint8_t)0)
#define HIT_POLY   ((uint8_t)1)


// intersecetion
// norm
typedef std::tuple<uint8_t, size_t> hit_t;

// returns true for hitting anything
//
bool RayEngine::trace(
    const Ray& r,
    const int depthIn,
    Vec3 &color,
    const bool shdFeeling ) {

    if( depthIn > this->depth ) {
        if( print ) {
            cout << "Abort\n";
        }
        return false;
    }

    if( print ) {
        cout << "trace px " << g_i << ", " << g_j << " depth " << depthIn << "\n";
    }

    // Vec3 fp;
    color[0] = color[1] = color[2] = 0;

    // double vd, vo, t; // tri stuff
    // Vec3 d1,d2,d3; // tri stuff
    


    // double minHit = NO_HIT;

    // when we reflect a ray, we recurse
    // after the recursion is done, we add these to the results
    // these are set by lighting
    Vec3 savedColor(0,0,0);
    Vec3 savedRefl(0,0,0);
    Vec3 savedIntersect(0,0,0);
    double savedKr = 0;


    // distance of closest hit
    // this value is a magic number signifying "no hit"
    double hitDistance = NO_HIT;
    hit_t bestHit;


    // const int nSphere = spheres.size();
    for( unsigned i = 0; i < spheres.size(); i++ )
    {
        const Sphere &s = spheres[i];

        const Vec3 oc = r.o - s.c;
        const double a = r.d.dot(r.d);

        // const double b = 2*(r.d[0] * (r.o[0] - s.c[0]) + r.d[1] * (r.o[1] - s.c[1]) + r.d[2] * (r.o[2] - s.c[2]));
        const double b = 2.0 * oc.dot(r.d);

        // double c = pow((r.o[0] - s.c[0]),2) + pow((r.o[1] - s.c[1]),2) + pow((r.o[2] - s.c[2]),2) - s.r*s.r;
        const double c = oc.dot(oc) - (s.r*s.r);

        const double discriminant = (b*b) - (4*a*c);

        if(print) {
            cout << "Discr: " << discriminant << " " << i << "\n";
        }

        /// dis < 0   no intersection
        /// dis = 0   tangent intersection (1 point only)
        /// dis > 0   two points of intersection

        if( discriminant < 0 ) {
            if( print ) {
                cout << "sphere break A " << i << "\n";
            }
            continue;
        }

        double t0 = ((-b) - sqrt(discriminant)) / (2*a);
        double t1 = ((-b) + sqrt(discriminant)) / (2*a);

        if( print ) {
            cout << "t0 " << t0 << " t1 " << t1 << "\n";
        }

        ///
        /// 
        /// 

        double sphereBestT;

        // has hit detection issues
        if( false ) {
            sphereBestT = min( t0, t1 );
        }

        
        // the tolerance here can be changed to 0 if we "advance"
        // the reflected ray just a bit.  whichever is more efficient
        if( true ) {

            // this fixes shadow issues
            const double sphereLift = 1E-12;

            if( t0 > sphereLift && t1 > sphereLift ) {
                sphereBestT = min( t0, t1 );
            } else if( t0 > sphereLift && t1 <= sphereLift ) {
                sphereBestT = t0;
            } else if ( t0 <= sphereLift && t1 > sphereLift ) {
                sphereBestT = t1;
            } else {
                // sphere is behind ray
                continue;
            }
        }

        // if we are doing a shadow feeler
        // we are sending one single ray back to the light source
        // any hit, no matter the distance, means the light is blocked

        if( shdFeeling ) {
            if( print ) {
                cout << "sphere break shadow " << i << "\n";
            }

            return true;
        }


        // if this hit is closer then the last
        // save it
        if( sphereBestT < hitDistance ) {
            if( print ) {
                cout << "Update best hit to " << sphereBestT << "\n";
            }
            hitDistance = sphereBestT;
            bestHit = std::make_tuple(HIT_SPHERE, i);
        }
    } // for spheres

    if( hitDistance != NO_HIT ) {
        Vec3 intersect;
        Vec3 norm;
        Vec3 refl;
        Vec3 fp;
        Material material;
        const auto [ hitWhat, index ] = bestHit;

        if( hitWhat == HIT_SPHERE ) {
            std::tie(intersect, norm, refl, fp) = intersectSphere(r, spheres[index], hitDistance);
            material = spheres[index].m;
        }

        // we start with ambient light
        // we add the diffuse color of the object to the ambient light
        // and then multiply by the objecs ambient coeffient
        // this gives the best look I feel however I guessed for this
        color = (this->ia+material.kd) * material.ka;

        // a bad guess, don't want multiply
        // color = (this->ia+material.kd) * material.ka * material.kd;

        for( unsigned iLight = 0; iLight < lights.size(); iLight++ )
        {
            // decide if we can see this light

            Ray shadowFeeler;
            shadowFeeler.o = intersect;
            shadowFeeler.d = lights[iLight].d * -1;
            // shadowFeeler.o = shadowFeeler.o + shadowFeeler.d * 2;
            Vec3 shadowColor; // unused
            if(print) {
                cout << "looking at light " << iLight << " " << shadowFeeler.o.str(false) << " " << shadowFeeler.d.str(false) << "\n";
            }
            // trace( shadowFeeler, depth, effect, shadowColor, false, bSphere, objectNum, true );
            // set depth to maximum to prevent further bounces
            const bool lightBlocked = trace( shadowFeeler, this->depth, shadowColor, true );

            if( lightBlocked ) {
                continue;
            }



            // now that we know we can see the light
            const Vec3 negLightDirection = lights[iLight].d*-1;

            const Vec3 diffuse = (material.kd * norm.dot( negLightDirection ) );

            const Vec3 negRayDirection = r.d*-1;
            Vec3 idealR = Vec3::reflect(lights[iLight].d, norm );

            const float specular = material.ks * pow( std::max((double)0, idealR.dot( negRayDirection )), material.n);

            Vec3 lightEffects =
                  ( lights[iLight].color / ( fp.mag() + this->c ) ) 
                * (diffuse + specular);

            // Lights cannot have negative effect
            lightEffects.saturateMin(0.0);

            color = color + lightEffects;
        }

        savedColor = color;
        savedRefl = refl;
        savedKr = material.kr;
        savedIntersect = intersect;
    }




    //final actions after main loops--------



    if( hitDistance != NO_HIT ) {
        Ray reflRay;
        reflRay.o = savedIntersect;
        reflRay.d = savedRefl;


        if( savedKr > 0 ) {

            if( print ) {
                cout << "refl using " << reflRay.d.str(false) << "\n";
            }

            Vec3 newColor(0,0,0);
            trace( reflRay, depthIn+1, newColor, false );
            color = savedColor + (newColor * savedKr);
        } else {
            color = savedColor;
        }

        
        return true;
    } else {
        //we hit nothing
        color = Vec3( 0, 0, 0 );
        return false;
    }
}


