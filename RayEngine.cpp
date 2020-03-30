#include "RayEngine.hpp"
#include <math.h>
#include <iostream>

Ray::Ray()
{

}

RayEngine::RayEngine( void )
{
    numPoly = 0;
    this->polygons.resize(POLYGONS);
    this->hits.resize(POLYGONS+30);

    r = g = b = 0;
    px = 0;
    makeObjects();

    mat = new Matrix( 3, 3 );
    mat->m1 = new Matrix( 2, 2 );
    mat->m2 = new Matrix( 2, 2 );
    mat->m3 = new Matrix( 2, 2 );
    
}

/*

// original scene submitted for homework
void RayEngine::scene1(void) {
    //camera
    camera.o = Vec3( 0, 1, -2 );
    camera.d = Vec3( 0, -0.2, 1 );
    camera.d.normalize();
    up = Vec3( 0, 1, 0 );


    //spheres
    spheres[0].c = Vec3( 1, 0, 3.0f );
    spheres[0].r = 1.0f;
    spheres[0].ka = 0.4f;
    spheres[0].kd = Vec3( 0.0f, 1.0f, 0.0f );
    spheres[0].ks = 0.7f;
    spheres[0].n = 8;
    spheres[0].kr = 0.7f;
    spheres[0].kt = 0.0f;

    // spheres[1].c = Vec3( -1, 0.5f, 4.0f );
    // spheres[1].r = 1.0f;
    // spheres[1].ka = 0.4f;
    // spheres[1].kd = Vec3( 1.0f, 0.0f, 0.0f );
    // spheres[1].ks = 0.7f;
    // spheres[1].n = 3;
    // spheres[1].kr = 0.7f;
    // spheres[1].kt = 0.0f;


    spheres[1].c = Vec3( -1.0f, 0, 3.0 );
    spheres[1].r = 0.7f;
    spheres[1].ka = 1.0f;
    spheres[1].kd = Vec3( 1.0f, 0.8f, 0.0f );
    spheres[1].ks = 0.7f;
    spheres[1].n = 7;
    spheres[1].kr = 0.5f;
    spheres[1].kt = 0.0f;

    spheres[2].c = Vec3( .4, 1.5, 3.0 );
    spheres[2].r = 0.2f;
    spheres[2].ka = 1.0f;
    spheres[2].kd = Vec3( 0.4f, 0.8f, 0.0f );
    spheres[2].ks = 0.7f;
    spheres[2].n = 10;
    spheres[2].kr = 0.5f;
    spheres[2].kt = 0.0f;

    spheres[3].c = Vec3( -.7, 1.7, 3.0 );
    spheres[3].r = 0.3f;
    spheres[3].ka = 1.0f;
    spheres[3].kd = Vec3( 1.0f, 1, 1 );
    spheres[3].ks = 0.7f;
    spheres[3].n = 11;
    spheres[3].kr = 0.5f;
    spheres[3].kt = 0.0f;


    spheres[4].c = Vec3( 0, -11, 0 );
    spheres[4].r = 10;
    spheres[4].ka = 1.0f;
    spheres[4].kd = Vec3( 0.5, 0.5, 0.5 );
    spheres[4].ks = 0.7f;
    spheres[4].n = 11;
    spheres[4].kr = 0.3f;
    spheres[4].kt = 0.0f;


    //objects

    polygons[1].kr = 1.0f;

    //lights
    lights[0].color = Vec3( 5, 10, 8 );
    lights[0].d = Vec3( 1, 1, -0.7f );
    lights[0].d.normalize();

    lights[1].color = Vec3( 7, 2, 2 );
    lights[1].d = Vec3( 0, -1, -0.5 );
    lights[1].d.normalize();

    //global
    ia = Vec3( 0.2f, 0.2f, 0.2f );
    c = 7;
    depth = 3;

    nSphere = 5;
}

*/

// trying to debug whats wrong
void RayEngine::scene2(void) {
    //camera
    camera.o = Vec3( 0, 1, -2 );
    camera.d = Vec3( 0, -0.2, 1 );
    camera.d.normalize();

    up = Vec3( 0, 1, 0 );
    up.normalize();

    spheres.resize(3);


    //spheres
    spheres[0].r = 1.0f;
    spheres[0].c = Vec3( 1, 0, 3.0f ); // center
    spheres[0].ka = 0.4f;
    spheres[0].ks = 0.2f;
    spheres[0].kr = 0.0f;
    spheres[0].kd = Vec3( 0.0f, 1.0f, 0.0f );
    spheres[0].n = 8;
    spheres[0].kt = 0.7f;
/*
    spheres[1].c = Vec3( -1, 0.5f, 4.0f );
    spheres[1].r = 1.0f;
    spheres[1].ka = 0.4f;
    spheres[1].kd = Vec3( 1.0f, 0.0f, 0.0f );
    spheres[1].ks = 0.7f;
    spheres[1].n = 3;
    spheres[1].kr = 0.7f;
    spheres[1].kt = 0.0f;
*/

    spheres[1].r = 0.7f;
    spheres[1].c = Vec3( -1.0f, 0, 3.0 );
    spheres[1].ka = 0.0f;
    spheres[1].ks = 0.0f;
    spheres[1].kr = 1.0f;
    spheres[1].kd = Vec3( 1.0f, 0.8f, 0.0f );
    spheres[1].n = 7;
    spheres[1].kt = 0.0f; //*/

    // spheres[2].c = Vec3( .4, 1.5, 3.0 );
    // spheres[2].r = 0.2f;
    // spheres[2].ka = 1.0f;
    // spheres[2].kd = Vec3( 0.4f, 0.8f, 0.0f );
    // spheres[2].ks = 0.7f;
    // spheres[2].n = 10;
    // spheres[2].kr = 0.5f;
    // spheres[2].kt = 0.0f;

    // spheres[3].c = Vec3( -.7, 1.7, 3.0 );
    // spheres[3].r = 0.3f;
    // spheres[3].ka = 1.0f;
    // spheres[3].kd = Vec3( 1.0f, 1, 1 );
    // spheres[3].ks = 0.7f;
    // spheres[3].n = 11;
    // spheres[3].kr = 0.5f;
    // spheres[3].kt = 0.0f;


    spheres[2].r = 10;
    spheres[2].c = Vec3( 0, -11, 0 );
    spheres[2].ka = 0.4f;
    spheres[2].ks = 0.0f;
    spheres[2].kr = 1.0f;
    spheres[2].kt = 0.0f;
    spheres[2].kd = Vec3( 0.0, 0.0, 0.0 );
    spheres[2].n = 11;

    // spheres.resize(2); // delete last one

    // nSphere = 2;

    //objects

    numPoly = 1;

    polygons[0].kr = 1.0f;
    polygons[0].ka = 0.7f;
    polygons[0].ks = 0.0f;
    polygons[0].kd = Vec3( 0.2, 0.4, 0.2 );
    polygons[0].n = 7;

    // polygons[0].insert(0,0,0);
    // polygons[0].insert(0,1,0);
    // polygons[0].insert(0,1,1);
    // polygons[0].insert(0,0,1);

    //lights
    // lights[0].color = Vec3( 0, 0, 0 );
    // lights[0].d = Vec3( 1, 1, -0.7f );
    // lights[0].d.normalize();

    lights.resize(1);

    lights[0].color = Vec3( 10, 10, 10 );
    lights[0].d = Vec3( 0, -1, -0.5 );
    lights[0].d.normalize();

    // nLight = 1;

    // global
    ia = Vec3( 0.4f, 0.4f, 0.4f ); // Global Ambient color
    c = 7;
    depth = 3;

}

/*

// original scene submitted for homework
void RayEngine::scene3(void) {
    //camera
    camera.o = Vec3( 0, 1, -2 );
    camera.d = Vec3( 0, -0.2, 1 );
    camera.d.normalize();
    up = Vec3( 0, 1, 0 );


    //spheres
    spheres[0].c = Vec3( 1, 0, 3.0f );
    spheres[0].r = 1.0f;
    spheres[0].ka = 0.4f;
    spheres[0].kd = Vec3( 0.0f, 1.0f, 0.0f );
    spheres[0].ks = 0.2f;
    spheres[0].n = 8;
    spheres[0].kr = 0.7f;
    spheres[0].kt = 0.0f;

    spheres[1].c = Vec3( -1.0f, 0, 3.0 );
    spheres[1].r = 0.7f;
    spheres[1].ka = 1.0f;
    spheres[1].kd = Vec3( 1.0f, 0.8f, 0.0f );
    spheres[1].ks = 0.2f;
    spheres[1].n = 7;
    spheres[1].kr = 0.5f;
    spheres[1].kt = 0.0f;

    spheres[2].c = Vec3( .4, 1.5, 3.0 );
    spheres[2].r = 0.2f;
    spheres[2].ka = 1.0f;
    spheres[2].kd = Vec3( 0.4f, 0.8f, 0.0f );
    spheres[2].ks = 0.1f;
    spheres[2].n = 10;
    spheres[2].kr = 0.5f;
    spheres[2].kt = 0.0f;

    spheres[3].c = Vec3( -.7, 1.7, 3.0 );
    spheres[3].r = 0.3f;
    spheres[3].ka = 1.0f;
    spheres[3].kd = Vec3( 1.0f, 1, 1 );
    spheres[3].ks = 0.2f;
    spheres[3].n = 11;
    spheres[3].kr = 0.5f;
    spheres[3].kt = 0.0f;


    spheres[4].c = Vec3( 0, -11, 0 );
    spheres[4].r = 10;
    spheres[4].ka = 1.0f;
    spheres[4].kd = Vec3( 0.5, 0.5, 0.5 );
    spheres[4].ks = 0.1f;
    spheres[4].n = 11;
    spheres[4].kr = 0.3f;
    spheres[4].kt = 0.0f;


    //objects

    polygons[1].kr = 1.0f;

    //lights
    lights[0].color = Vec3( 5, 10, 8 );
    lights[0].d = Vec3( 1, 1, -0.7f );
    lights[0].d.normalize();

    lights[1].color = Vec3( 7, 2, 2 );
    lights[1].d = Vec3( 0, -1, -0.5 );
    lights[1].d.normalize();

    //global
    ia = Vec3( 0.2f, 0.2f, 0.2f );
    c = 7;
    depth = 3;

    nSphere = 5;
}

*/


void RayEngine::makeObjects( void )
{
    // scene1();
    scene2();
    // scene3();
}

void RayEngine::paint( void )
{
/*    for( int asf=343; asf<4555; asf++)
    {
        r[asf] = 1.0f;
    }*/

    /*
    glBegin(GL_POINTS);
    for( int j = 0; j < px; j++ )
        for( int i = 0; i < px; i++ )
        {
            glColor3f( r[i+j*px], g[i+j*px], b[i+j*px] );
            glVertex2i( i, j );
        }
    glEnd();
    */

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
    bool nUsedB = false;
    Vec3 nUsedI;
    Ray r;
    Vec3 pixel;
    double cu,cv;
    //float red, green, blue;
    Vec3 color;

    Vec3 e = camera.o;//( -0.1, 0, 0 );
    Vec3 a = e + camera.d;//( 0.4f, 0, 0 );
    Vec3 w = e-a;
    w.normalize();

    Vec3 u = cross( up, e-a );
    u.normalize();
    Vec3 v = cross( w, u );

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

                trace( r, 0, 0, color, false, nUsedB, nUsedI, false );
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

// returns true for hitting anything
//
bool RayEngine::trace(
    const Ray& r,
    const int depthIn,
    const double effect,
    Vec3 &color,
    const bool click,
    bool &bSphere, // fixme should be const, needs to be copied below
    Vec3 &objectNum,
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

    Vec3 intersect;
    Vec3 fp;
    color[0] = color[1] = color[2] = 0;
    double srInverse;

    Vec3 pn;
    double vd, vo, t;
    
    Vec3 d1,d2,d3;
    //double normDotDir;
    numHit = 0;
    double minHit = 999999;
    Vec3 savedColor;
    Vec3 savedRefl;
    Vec3 savedIntersect;
    
    // bool tmpBool;
    double savedKr;
    bool hitSphere = false;
    objectNum[0] = -1;

    const int nSphere = spheres.size();
    for( int i = 0; i < nSphere; i++ )
    {
        const Sphere &s = spheres[i];

        Vec3 oc = r.o - s.c;
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

        double t0 = ((-1* b) - sqrt((b*b) - (4*a*c))) / (2*a);
        double t1 = ((-1* b) + sqrt((b*b) - (4*a*c))) / (2*a);

        if( print ) {
            cout << "t0 " << t0 << " t1 " << t1 << "\n";
        }



        if( shdFeeling && (t0 < 0 || t1 < 0)  )
        {
            if( print ) {
                cout << "sphere break shadow " << i << "\n";
            }
            color[0] = 1;    // what is the purpose of this? to signal upstream?
            // color[1] = 0;
            // color[2] = 0;
            continue;
        }

        ///
        /// 
        /// 

        t0 = min( t0, t1 );

        // if( t0 > 0 && t1 > 0 ) {
        //     t0 = min( t0, t1 );
        // } else if( t0 > 0 && t1 <= 0 ) {
        //     t0 = t0;
        // } else if ( t0 <= 0 && t1 > 0 ) {
        //     t0 = t1;
        // } else {
        //     t0 = minHit;
        //     // sphere is behind ray
        //     continue;
        // }




        if( min( t0, minHit ) == t0 )
        {

            if( print ) {
                cout << "hit sphere " << i << " t0 " << t0 << "\n";
            }

            hitSphere = true;
            objectNum[0] = i;
            minHit = t0;
            intersect = Vec3( r.o[0] + r.d[0]*t0,
                              r.o[1] + r.d[1]*t0,
                              r.o[2] + r.d[2]*t0 );
            srInverse = 1.0f/s.r;

            if( print ) {
                cout << "inv: " << srInverse << "\n";
            }

            Vec3 norm = Vec3( ( intersect[0] - s.c[0] )*srInverse, ( intersect[1] - s.c[1] )*srInverse, ( intersect[2] - s.c[2] )*srInverse );
            //norm = intersect - s.c;
            norm.normalize();

            //refl = r.d - norm * 2 * (camera.d.dot(norm));
            Vec3 refl = norm*2* norm.dot( r.d ) - r.d;

            //lighting
            fp = r.o - intersect;
            
            
            //we aleways have ambient light
            color = this->ia * s.ka;
    
            if( !click ) {
                for( unsigned iLight = 0; iLight < lights.size(); iLight++ )
                {
                    if( false ) {
                        Ray shadowFeeler;
                        shadowFeeler.o = intersect;
                        shadowFeeler.d = lights[iLight].d * -1;
                        shadowFeeler.o = shadowFeeler.o + shadowFeeler.d * 2;
                        Vec3 shadowColor;
                        shadowColor[0] = shadowColor[1] = shadowColor[2] = 0;
                        if(print) {
                            cout << "looking at light " << iLight << " " << shadowFeeler.o.str(false) << " " << shadowFeeler.d.str(false) << "\n";
                        }
                        // trace( shadowFeeler, depth, effect, shadowColor, false, bSphere, objectNum, true );
                        trace( shadowFeeler, depthIn+1, effect, shadowColor, false, bSphere, objectNum, true );
                        if( shadowColor[0] != 0 || shadowColor[1] != 0 || shadowColor[2] != 0 ) {
                            if(print) {
                                cout << "abandond light " << iLight << "\n";
                            }
                            continue;
                        }
                    }



                    const Vec3 negLightDirection = lights[iLight].d*-1;

                    // const Vec3 diffuse = (s.kd * negLightDirection.dot( norm ) );
                    const Vec3 diffuse = (s.kd * norm.dot( negLightDirection ) );
                    // const Vec3 diffuse = (s.kd * norm.dot( lights[iLight].d ) );




                    const Vec3 tmp = norm - lights[iLight].d;
                    Vec3 lightRefl = tmp * 2 * norm.dot(negLightDirection);
                    lightRefl.normalize();


                    const Vec3 lightPlusOrigin = r.d + negLightDirection;//lights[iLight].d;
                    // const Vec3 negRayDirection = r.d;
                    const Vec3 negRayDirection = r.d*-1; // opposite
                    // const Vec3 negRayDirection = fp*-1;
                    // const Vec3 negRayDirection = lightPlusOrigin;

                    Vec3 idealR = Vec3::reflect(lights[iLight].d, norm );

                    const float specular = s.ks * pow( std::max((double)0, idealR.dot( negRayDirection )), s.n);
                    // const float specular = s.ks * pow( idealR.dot( negRayDirection ), s.n);

                    const Vec3 lightEffects =
                          ( lights[iLight].color / ( fp.mag() + this->c ) ) 
                        * (diffuse + specular);
                    
                    color = color + lightEffects;
                        
                }
            }

            savedColor = color;
            savedRefl = refl;
            savedKr = s.kr;
            savedIntersect = intersect;
        }
        

    } // for spheres


    //final actions after main loops--------

    //if this was from a click we don't care about colors etc
    if( click ) {
        bSphere = hitSphere;
        return hitSphere; // FIXME PROBABLY WRONG FIXME REMOVE CLICK
    }


    if( minHit != 999999 ) {
        Ray reflRay;
        reflRay.o = savedIntersect;
        reflRay.d = savedRefl;

        if(print) {
            cout << "reenter " << intersect[0] << "\n";
        }

        Vec3 newColor(0,0,0);
        trace( reflRay, depthIn+1, effect, newColor, false, bSphere, objectNum, false );
        color = savedColor + newColor * savedKr;
        return true;
    } else {
        //we hit nothing
        color = Vec3( 0, 0, 0 );
        return false;
    }
}


