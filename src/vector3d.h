#ifdef __cplusplus
extern "C"
{
#endif
    
    #include "postgres.h"
    
    // STRUCTURE THAT WILL BE USED TO REPRESENT A 3D VECTOR IN POSTGRES
    typedef struct pgvector3d { double x, y, z; } pgvector3d;
    
    int    vector3DCmp(pgvector3d *u, pgvector3d *v);
    
    void   vector3DMul(pgvector3d *u, pgvector3d *v, double scalar);
    void   vector3DDiv(pgvector3d *u, pgvector3d *v, double scalar);
    void   vector3DAdd(pgvector3d *u, pgvector3d *v, pgvector3d *t);
    void   vector3DSub(pgvector3d *u, pgvector3d *v, pgvector3d *t);
    
    double vector3DDot(pgvector3d *u, pgvector3d *v);
    void   vector3DCross(pgvector3d *u, pgvector3d *v, pgvector3d *cp);
    
    double vector3DNorm(pgvector3d *v);
    void   vector3DNormalize(pgvector3d *u, pgvector3d *v);
    
    double vector3DDistance(pgvector3d *u, pgvector3d *v);
    double vector3DAngle(pgvector3d *u, pgvector3d *v);
    double vector3DAbsAngle(pgvector3d *u, pgvector3d *v);

#ifdef __cplusplus
}
#endif
