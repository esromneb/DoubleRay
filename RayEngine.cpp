#include "RayEngine.hpp"
#include <math.h>

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
            trace( r, 0, 0, color, false, nUsedB, nUsedI, false );
            this->r[i+j*px] = color[0];
            this->g[i+j*px] = color[1];
            this->b[i+j*px] = color[2];

        }
}

void RayEngine::trace(
    const Ray& r,
    const int depthIn,
    const double effect,
    Vec3 &color,
    const bool click,
    bool &bSphere, // fixme should be const, needs to be copied below
    Vec3 &objectNum,
    const bool shdFeeling ) {

    if( depthIn > this->depth ) {
        return;
    }

    double b,c,t0,t1;
    Vec3 intersect;
    Vec3 from, fp, refl, lightRefl, tmp, norm;
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
    Ray shadowFeeler;
    Vec3 shadowColor;
    bool tmpBool;
    double savedKr;
    bool hitSphere;
    objectNum[0] = -1;

    for( int iP = 0; iP < this->numPoly; iP++ )
    {
        const Poly &poly = polygons[iP];
        for( int iTri = 0; iTri < poly.trianglePointCount / 3; iTri++ )
        {
            //continue;
            vd = poly.abcnorm[iTri].dot( r.d );
            if( !vd )
                continue; //the ray lies in the plane
            vo = -1* (poly.abcnorm[iTri].dot(r.o) + poly.d[iTri]);
            t = vo / vd;
            if( t < 0 )
                continue; //plane is behind ray's origin

            intersect = r.o + r.d*t;
            //if( vd > 0 )
            //    intersection = intersection * -1 ;

            tmp[0] = poly.x[poly.triangles[iTri+0]];
            tmp[1] = poly.y[poly.triangles[iTri+0]];
            tmp[2] = poly.z[poly.triangles[iTri+0]];

            d1 = tmp - intersect;

            tmp[0] = poly.x[poly.triangles[iTri+1]];
            tmp[1] = poly.y[poly.triangles[iTri+1]];
            tmp[2] = poly.z[poly.triangles[iTri+1]];

            d2 = tmp - intersect;

            tmp[0] = poly.x[poly.triangles[iTri+2]];
            tmp[1] = poly.y[poly.triangles[iTri+2]];
            tmp[2] = poly.z[poly.triangles[iTri+2]];

            d3 = tmp - intersect;


            mat->data[0][0] = d1[0];
            mat->data[0][1] = d1[1];
            mat->data[0][2] = d1[2];
            mat->data[1][0] = d2[0];
            mat->data[1][1] = d2[1];
            mat->data[1][2] = d2[2];
            mat->data[2][0] = 1;
            mat->data[2][1] = 1;
            mat->data[2][2] = 1;

            const float det1 = mat->det();

            mat->data[0][0] = d2[0];
            mat->data[0][1] = d2[1];
            mat->data[0][2] = d2[2];
            mat->data[1][0] = d3[0];
            mat->data[1][1] = d3[1];
            mat->data[1][2] = d3[2];

            const float det2 = mat->det();

            mat->data[0][0] = d3[0];
            mat->data[0][1] = d3[1];
            mat->data[0][2] = d3[2];
            mat->data[1][0] = d1[0];
            mat->data[1][1] = d1[1];
            mat->data[1][2] = d1[2];

            const float det3 = mat->det();

            //at this point we know we hit the plane
            //now we have to check if we hit inside the triangle
            if( ( det1 < 0 && det2 < 0 && det3 < 0 )
                || ( det1 > 0 && det2 > 0 && det3 > 0 ) )
            {

                if( shdFeeling )
                {
                    color[0] = 1;
                    return;
                }

                //if we are the closest intersection so far
                if( min( t, minHit ) == t )
                {
                    hitSphere = false;
                    objectNum[0] = iP;
                    objectNum[1] = iTri;
                    minHit = t;
                    
                    savedRefl = poly.abcnorm[iTri]*2*( poly.abcnorm[iTri].dot( r.d ) ) - (r.d);
                    savedKr = poly.kr;
                    savedIntersect = intersect;



                    savedColor = this->ia * poly.ka;

                    if( !click ) {
                        for( int iLight = 0; iLight < lights.size(); iLight++ )
                        {
                            shadowFeeler.o = intersect;
                            shadowFeeler.d = lights[iLight].d * -1;
                            shadowColor[0] = shadowColor[1] = shadowColor[2] = 0;
                            trace( shadowFeeler, depth, effect, shadowColor, false, bSphere, objectNum, true );
                            if( shadowColor[0] != 0 || shadowColor[1] != 0 || shadowColor[2] != 0 )
                                continue;
                            tmp = poly.abcnorm[iTri] - lights[iLight].d;
                            lightRefl = tmp * 2 * poly.abcnorm[iTri].dot(lights[iLight].d);
                            lightRefl.normalize();

                            savedColor = savedColor + ( lights[iLight].color / ( fp.mag() + this->c )  )*( poly.kd * lights[iLight].d.dot( poly.abcnorm[iTri] ) + poly.ks * pow( lightRefl.dot( r.d ), poly.n) );
                        }
                    }


                    //savedColor = Vec3( 1.0f, 0.0f, 0.0f );

                }
            }
            else
            {
                continue;
            }

            //color = Vec3( 1.0, 0, 0 );
        }

    }


    const int nSphere = spheres.size();
    for( int i = 0; i < nSphere; i++ )
    {
        const Sphere &s = spheres[i];

        b = 2*(r.d[0] * (r.o[0] - s.c[0]) + r.d[1] * (r.o[1] - s.c[1]) + r.d[2] * (r.o[2] - s.c[2]));
        c = pow((r.o[0] - s.c[0]),2) + pow((r.o[1] - s.c[1]),2) + pow((r.o[2] - s.c[2]),2) - s.r*s.r;
        if( b*b - 4*c < 0 )
            continue;
        
        if( i == 1 )
            i = 1;

        t0 = (-1* b - sqrt(b*b - 4*c)) / 2;
        t1 = (-1* b + sqrt(b*b - 4*c)) / 2;


        if( shdFeeling && t0 < 0 )
        {
            color[0] = 1;
            continue;
        }

        t0 = min( t0, t1 );

        if( shdFeeling )
        {
            //color[0] = 1;
            //return;
        }


        if( min( t0, minHit ) == t0 )
        {
            hitSphere = true;
            objectNum[0] = i;
            minHit = t0;
            intersect = Vec3( r.o[0] + r.d[0]*t0,
                              r.o[1] + r.d[1]*t0,
                              r.o[2] + r.d[2]*t0 );
            srInverse = 1.0f/s.r;

            norm = Vec3( ( intersect[0] - s.c[0] )*srInverse, ( intersect[1] - s.c[1] )*srInverse, ( intersect[2] - s.c[2] )*srInverse );
            //norm = intersect - s.c;
            norm.normalize();

            //refl = r.d - norm * 2 * (camera.d.dot(norm));
            refl = norm*2* norm.dot( r.d ) - r.d;

            //lighting
            fp = r.o - intersect;
            
            
            //we aleways have ambient light
            color = this->ia * s.ka;
    
            if( !click ) {
                for( int iLight = 0; iLight < lights.size(); iLight++ )
                {
                    shadowFeeler.o = intersect;
                    shadowFeeler.d = lights[iLight].d * -1;
                    shadowFeeler.o = shadowFeeler.o + shadowFeeler.d * 2;
                    shadowColor[0] = shadowColor[1] = shadowColor[2] = 0;
                    trace( shadowFeeler, depth, effect, shadowColor, false, bSphere, objectNum, true );
                    if( shadowColor[0] != 0 || shadowColor[1] != 0 || shadowColor[2] != 0 )
                        continue;
                    tmp = norm - lights[iLight].d;
                    lightRefl = tmp * 2 * norm.dot(lights[iLight].d);
                    lightRefl.normalize();

                    const Vec3 diffuse = (s.kd * lights[iLight].d.dot( norm ) );

                    const Vec3 lightPlusOrigin = r.d + lights[iLight].d;

                    const float specular = s.ks * pow( lightRefl.dot( lightPlusOrigin ), s.n);

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
        

    }//spheres


    //final actions after main loops--------

    //if this was from a click we don't care about colors etc
    if( click ) {
        bSphere = hitSphere;
        return;
    }


    if( minHit != 999999 ) {
        Ray reflRay;
        reflRay.o = savedIntersect;
        reflRay.d = savedRefl;
        Vec3 newColor(0,0,0);
        trace( reflRay, depthIn+1, effect, newColor, false, bSphere, objectNum, false );
        color = savedColor + newColor * savedKr;
    } else {
        //we hit nothing
        color = Vec3( 0, 0, 0 );
    }
}


