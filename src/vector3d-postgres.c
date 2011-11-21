#include "postgres.h"
#include "fmgr.h"
#include "lib/stringinfo.h"
#include "vector3d.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

// FUNCTION TO READ-IN A VECTOR3D
PG_FUNCTION_INFO_V1(vector3d_in);
Datum vector3d_in(PG_FUNCTION_ARGS)
{
    char       *str = PG_GETARG_CSTRING(0);
    double      x,y,z;
    pgvector3d   *vector3d;

    if (sscanf(str, " ( %lf , %lf , %lf )", &x, &y, &z) != 3)
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("Invalid input syntax for pgvector3d: \"%s\"", str)));

    vector3d = (pgvector3d *) palloc(sizeof(pgvector3d));
    vector3d->x = x;
    vector3d->y = y;
    vector3d->z = z;
    
    PG_RETURN_POINTER(vector3d);
}

PG_FUNCTION_INFO_V1(vector3d_out);
Datum vector3d_out(PG_FUNCTION_ARGS)
{
    pgvector3d  *vector3d = PG_GETARG_VECTOR3D(0);
    char      *result;

    result = (char *) palloc(100);
    snprintf(result, 100, "(%g,%g,%g)", vector3d->x, vector3d->y, vector3d->z);
    
    PG_RETURN_CSTRING(result);
}

// BINARY INPUT OF VECTOR3D TYPE
PG_FUNCTION_INFO_V1(vector3d_recv);
Datum vector3d_recv(PG_FUNCTION_ARGS)
{
    StringInfo  buf = (StringInfo) PG_GETARG_POINTER(0);
    pgvector3d   *result;

    result = (pgvector3d *) palloc(sizeof(pgvector3d));
    result->x = pq_getmsgfloat8(buf);
    result->y = pq_getmsgfloat8(buf);
    result->z = pq_getmsgfloat8(buf);
    PG_RETURN_POINTER(result);
}

// BINARY OUTPUT OF VECTOR3D TYPE
PG_FUNCTION_INFO_V1(vector3d_send);
Datum vector3d_send(PG_FUNCTION_ARGS)
{
    pgvector3d *vector3d = PG_GETARG_VECTOR3D(0);
    StringInfoData buf;

    pq_begintypsend(&buf);
    pq_sendfloat8(&buf, vector3d->x);
    pq_sendfloat8(&buf, vector3d->y);
    pq_sendfloat8(&buf, vector3d->y);
    
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}

// TEST IF FIRST VECTOR IS LESS THAN SECOND
PG_FUNCTION_INFO_V1(vector3d_cmp);
Datum vector3d_cmp(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_INT32(vector3DCmp(u,v));
}


// TEST IF FIRST VECTOR IS LESS THAN SECOND
PG_FUNCTION_INFO_V1(vector3d_lt);
Datum vector3d_lt(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_BOOL(vector3DCmp(u,v) == 1);
}

// TEST IF FIRST VECTOR IS LESS THAN OR EQUAL TO SECOND
PG_FUNCTION_INFO_V1(vector3d_le);
Datum vector3d_le(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_BOOL(vector3DCmp(u,v) >= 0);
}

// TEST IF VECTORS ARE IDENTICAL
PG_FUNCTION_INFO_V1(vector3d_eq);
Datum vector3d_eq(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_BOOL(vector3DCmp(u,v) == 0);
}

// TEST IF FIRST VECTOR IS GREATER THAN OR EQUAL TO SECOND
PG_FUNCTION_INFO_V1(vector3d_ge);
Datum vector3d_ge(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_BOOL(vector3DCmp(u,v) <= 0);
}

// TEST IF FIRST VECTOR IS GREATER THAN SECOND
PG_FUNCTION_INFO_V1(vector3d_gt);
Datum vector3d_gt(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_BOOL(vector3DCmp(u,v) == -1);
}

// TEST IF VECTORS ARE DISTINCT
PG_FUNCTION_INFO_V1(vector3d_ne);
Datum vector3d_ne(PG_FUNCTION_ARGS)
{
    pgvector3d    *u = PG_GETARG_VECTOR3D(0);
    pgvector3d    *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_BOOL(vector3DCmp(u,v) != 0);
}

//
PG_FUNCTION_INFO_V1(vector3d_union);
Datum vector3d_union(PG_FUNCTION_ARGS)
{
    pgvector3d *v1 = PG_GETARG_VECTOR3D(0);
    pgvector3d *v2 = PG_GETARG_VECTOR3D(1);

    pgvector3d *v3 = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DUnion(v1,v2,v3);

    PG_RETURN_POINTER(v3);
}

// VECTOR ADDITION
PG_FUNCTION_INFO_V1(vector3d_add);
Datum vector3d_add(PG_FUNCTION_ARGS)
{
    pgvector3d *v1 = PG_GETARG_VECTOR3D(0);
    pgvector3d *v2 = PG_GETARG_VECTOR3D(1);

    pgvector3d *v3 = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DAdd(v1,v2,v3);

    PG_RETURN_POINTER(v3);
}

// VECTOR SUBSTRACTION
PG_FUNCTION_INFO_V1(vector3d_sub);
Datum vector3d_sub(PG_FUNCTION_ARGS)
{
    pgvector3d *v1 = PG_GETARG_VECTOR3D(0);
    pgvector3d *v2 = PG_GETARG_VECTOR3D(1);

    pgvector3d *v3 = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DSub(v1,v2,v3);

    PG_RETURN_POINTER(v3);
}

// VECTOR DIVISION BY SCALAR
PG_FUNCTION_INFO_V1(vector3d_div);
Datum vector3d_div(PG_FUNCTION_ARGS)
{
    pgvector3d *u = PG_GETARG_VECTOR3D(0);
    double      scalar = PG_GETARG_FLOAT8(1);
    
    pgvector3d *v = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DDiv(u,v,scalar);

    PG_RETURN_POINTER(v);
}

// VECTOR MULTIPLICATION BY SCALAR
PG_FUNCTION_INFO_V1(vector3d_mul);
Datum vector3d_mul(PG_FUNCTION_ARGS)
{
    pgvector3d *u = PG_GETARG_VECTOR3D(0);
    double      scalar = PG_GETARG_FLOAT8(1);
    
    pgvector3d *v = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DMul(u,v,scalar);

    PG_RETURN_POINTER(v);
}

// VECTOR DOT PRODUCT
PG_FUNCTION_INFO_V1(vector3d_dot);
Datum vector3d_dot(PG_FUNCTION_ARGS)
{
    pgvector3d *v1 = PG_GETARG_VECTOR3D(0);
    pgvector3d *v2 = PG_GETARG_VECTOR3D(1);

    PG_RETURN_FLOAT8(vector3DDot(v1,v2));
}

// CALCULATES THE NORM/LENGTH OF THE VECTOR
PG_FUNCTION_INFO_V1(vector3d_norm);
Datum vector3d_norm(PG_FUNCTION_ARGS)
{
    pgvector3d *vector3d = PG_GETARG_VECTOR3D(0);

    PG_RETURN_FLOAT8(vector3DNorm(vector3d));
}

// NORMALIZE VECTOR
PG_FUNCTION_INFO_V1(vector3d_normalize);
Datum vector3d_normalize(PG_FUNCTION_ARGS)
{
    pgvector3d *u = PG_GETARG_VECTOR3D(0);
    pgvector3d *v = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DNormalize(u,v);

    PG_RETURN_POINTER(v);
}

// VECTOR CROSS PRODUCT
PG_FUNCTION_INFO_V1(vector3d_cross);
Datum vector3d_cross(PG_FUNCTION_ARGS)
{
    pgvector3d *v1 = PG_GETARG_VECTOR3D(0);
    pgvector3d *v2 = PG_GETARG_VECTOR3D(1);

    pgvector3d *v3 = (pgvector3d *) palloc(sizeof(pgvector3d));

    vector3DCross(v1,v2,v3);

    PG_RETURN_POINTER(v3);
}

// DISTANCE BETWEEN VECTORS
PG_FUNCTION_INFO_V1(vector3d_distance);
Datum vector3d_distance(PG_FUNCTION_ARGS)
{
    pgvector3d *u = PG_GETARG_VECTOR3D(0);
    pgvector3d *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_FLOAT8(vector3DDistance(u,v));
}

// ANGLE BETWEEN VECTORS
PG_FUNCTION_INFO_V1(vector3d_angle);
Datum vector3d_angle(PG_FUNCTION_ARGS)
{
    pgvector3d *u = PG_GETARG_VECTOR3D(0);
    pgvector3d *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_FLOAT8(vector3DAngle(u,v));
}

// ABSOLUTE ANGLE BETWEEN VECTORS
PG_FUNCTION_INFO_V1(vector3d_abs_angle);
Datum vector3d_abs_angle(PG_FUNCTION_ARGS)
{
    pgvector3d *u = PG_GETARG_VECTOR3D(0);
    pgvector3d *v = PG_GETARG_VECTOR3D(1);

    PG_RETURN_FLOAT8(vector3DAbsAngle(u,v));
}