#ifdef __cplusplus
extern "C"
{
#endif
    
    #include "postgres.h"
    
    #define PG_GETARG_VECTOR3D(n)   ((pgvector3d *) PG_GETARG_POINTER(n))
    #define PG_RETURN_VECTOR3D(x)   return pgvector3dGetDatum(x)
    
    #define Vector3DDistanceStrategy    (1)
    #define Vector3DOrderByDistanceStrategy (2)
    
    // STRUCTURE THAT WILL BE USED TO REPRESENT A 3D VECTOR IN POSTGRES
    typedef struct pgvector3d { double x, y, z; } pgvector3d;
    
    int    vector3DCmp(pgvector3d *u, pgvector3d *v);
    
    void   vector3DMul(pgvector3d *u, pgvector3d *v, double scalar);
    void   vector3DDiv(pgvector3d *u, pgvector3d *v, double scalar);
    void   vector3DAdd(pgvector3d *u, pgvector3d *v, pgvector3d *t);
    void   vector3DSub(pgvector3d *u, pgvector3d *v, pgvector3d *t);
    void   vector3DUnion(pgvector3d *u, pgvector3d *v, pgvector3d *t);
    
    double vector3DDot(pgvector3d *u, pgvector3d *v);
    void   vector3DCross(pgvector3d *u, pgvector3d *v, pgvector3d *cp);
    
    double vector3DNorm(pgvector3d *v);
    void   vector3DNormalize(pgvector3d *u, pgvector3d *v);
    
    double vector3DDistance(pgvector3d *u, pgvector3d *v);
    double vector3DAngle(pgvector3d *u, pgvector3d *v);
    double vector3DAbsAngle(pgvector3d *u, pgvector3d *v);
    
    // USED FOR THE GIST INDEX
    extern float4 vector3d_dist_cutoff;

#ifdef __cplusplus
}
#endif
