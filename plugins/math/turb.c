#include <math.h>       // floor()
#include <stdlib.h>     // rand(), srand()
#include "turb.h"

#define INDEX(ix)       ((ix)&255)
#define INDEX_2D(ix,iy)       (( (ix)+perm[(iy)&255])&255)

static unsigned char perm[256] = {
        225,155,210,108,175,199,221,144,203,116, 70,213, 69,158, 33,252,
          5, 82,173,133,222,139,174, 27,  9, 71, 90,246, 75,130, 91,191,
        169,138,  2,151,194,235, 81,  7, 25,113,228,159,205,253,134,142,
        248, 65,224,217, 22,121,229, 63, 89,103, 96,104,156, 17,201,129,
         36,  8,165,110,237,117,231, 56,132,211,152, 20,181,111,239,218,
        170,163, 51,172,157, 47, 80,212,176,250, 87, 49, 99,242,136,189,
        162,115, 44, 43,124, 94,150, 16,141,247, 32, 10,198,223,255, 72,
         53,131, 84, 57,220,197, 58, 50,208, 11,241, 28,  3,192, 62,202,
         18,215,153, 24, 76, 41, 15,179, 39, 46, 55,  6,128,167, 23,188,
        106, 34,187,140,164, 73,112,182,244,195,227, 13, 35, 77,196,185,
         26,200,226,119, 31,123,168,125,249, 68,183,230,177,135,160,180,
         12,  1,243,148,102,166, 38,238,251, 37,240,126, 64, 74,161, 40,
        184,149,171,178,101, 66, 29, 59,146, 61,254,107, 42, 86,154,  4,
        236,232,120, 21,233,209, 45, 98,193,114, 78, 19,206, 14,118,127,
         48, 79,147, 85, 30,207,219, 54, 88,234,190,122, 95, 67,143,109,
        137,214,145, 93, 92,100,245,  0,216,186, 60, 83,105, 97,204, 52
};


void TURB_Init( int sr )
{
    int i;

    srand( sr );
    for( i=0; i<256; i++ )
        vtable[i] = (float)(rand()&255)/255.0;
}

float noise1d( float x)
{
    signed int  ix;
    float       fx;
    float       a,b;
    float       l1;
    
    ix = (signed int)floor(x);

    fx = x - ix;

    a = vtable[ INDEX(ix) ];
    b = vtable[ INDEX(ix+1) ];    

    l1 = a + fx*(b-a);
    
    return( l1 );

}


float noise2d( float x, float y )
{
    signed int  ix,iy;
    float       fx,fy;
    float       a,b,c,d;
    float       l1,l2;
    
    ix = (signed int)floor(x);
    iy = (signed int)floor(y); 

    fx = x - ix;
    fy = y - iy;

    a = vtable[ INDEX_2D( ix,  iy   ) ];
    b = vtable[ INDEX_2D( ix+1,iy   ) ];
    c = vtable[ INDEX_2D( ix,  iy+1 ) ];
    d = vtable[ INDEX_2D( ix+1,iy+1 ) ];

    l1 = a + fx*(b-a);
    l2 = c + fx*(d-c);
    
    return( l1 + fy*(l2-l1) );

}


float TURB_Turbulence2d( float *table, float x, float y, long octaves )
{
    float   t, s;

    t = 0.0;
    s = 0.5;

    while( octaves-- )
        {
        t += noise2d(x,y)*s;
        s*=0.5;
        x*=2.0;
        y*=2.0;
        }

    if( t>1.0 ) t=1.0;
    if( t<0.0 ) t=0.0;

    return( t );
}
