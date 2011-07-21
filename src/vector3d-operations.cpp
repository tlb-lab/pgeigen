#include <Eigen/Dense>
#include "vector3d.h"

using namespace Eigen;

// COPY EIGEN ALIGNED VECTOR TO POSTGRESQL VECTOR STRUCT
void vector3DCopy(Vector3d &av, pgvector3d *v)
{
    v->x = av[0];
    v->y = av[1];
    v->z = av[2];
}

// COMPARISON OF VECTORS
int vector3DCmp(pgvector3d *u, pgvector3d *v)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    // CHECK EQUALITY BY DISTANCE
    if (!((au-av).norm() > 0)) return 0;    
    
    // FIRST VECTOR IS SHORTER THAN SECOND
    else if (au.norm() < av.norm()) return -1;
    
    // SECOND VECTOR IS LARGER
    return 1;
}

void vector3DAdd(pgvector3d *u, pgvector3d *v, pgvector3d *t)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    // DO ADDITION
    Vector3d at = au + av;
    
    // COPY TO POSTGRES VECTOR3D STRUCT
    vector3DCopy(at,t);
}

void vector3DSub(pgvector3d *u, pgvector3d *v, pgvector3d *t)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    // DO SUBTRACTION
    Vector3d at = au - av;
    
    // COPY TO POSTGRES VECTOR3D STRUCT
    vector3DCopy(at,t);
}

// SCALAR MULTIPLICATION OF VECTOR
void vector3DMul(pgvector3d *u, pgvector3d *v, double scalar)
{
    Vector3d au(u->x, u->y, u->z);
    
    // MULTIPLY INLINE WITH SCALAR
    au *= scalar;
    
    // COPY TO POSTGRES VECTOR3D STRUCT
    vector3DCopy(au,v);
}

// SCALAR DIVISION OF VECTOR
void vector3DDiv(pgvector3d *u, pgvector3d *v, double scalar)
{
    Vector3d au(u->x, u->y, u->z);
    
    // MULTIPLY INLINE WITH SCALAR
    au /= scalar;
    
    // COPY TO POSTGRES VECTOR3D STRUCT
    vector3DCopy(au,v);
}


// DOT PRODUCT BETWEEN VECTORS
double vector3DDot(pgvector3d *u, pgvector3d *v)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    return au.dot(av);
}

// CROSS PRODUCT BETWEEN VECTORS
void vector3DCross(pgvector3d *u, pgvector3d *v, pgvector3d *cp)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    Vector3d acp = au.cross(av);
    
    // COPY TO POSTGRES VECTOR3D STRUCT
    vector3DCopy(acp,cp);
}

// CALCULATES THE NORM/LENGTH OF THE VECTOR
double vector3DNorm(pgvector3d *v)
{
    Vector3d av(v->x, v->y, v->z);
    
    return av.norm();
}

// NORMALIZE VECTOR
void vector3DNormalize(pgvector3d *u, pgvector3d *v)
{
    Vector3d au(u->x, u->y, u->z);
    
    // NORMALIZE VECTOR INLINE
    au.normalize();
    
    // COPY TO POSTGRES VECTOR3D STRUCT
    vector3DCopy(au,v);
}

// EUCLIDEAN DISTANCE BETWEEN VECTORS
double vector3DDistance(pgvector3d *u, pgvector3d *v)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    return (au-av).norm();
}

// ANGLE BETWEEN TWO VECTORS
double vector3DAngle(pgvector3d *u, pgvector3d *v)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    return acos(au.dot(av) / (au.norm() * av.norm()));
}

// ABSOLUTE ANGLE BETWEEN TWO VECTORS -- NOT WORKING
double vector3DAbsAngle(pgvector3d *u, pgvector3d *v)
{
    Vector3d au(u->x, u->y, u->z);
    Vector3d av(v->x, v->y, v->z);
    
    return acos(fabs(au.dot(av)) / (au.norm() * av.norm()));
}