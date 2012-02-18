#include "vector3d.h"
#include "fmgr.h"



///////////////////////////VECTOR GENERATION METHODS////////////////////////////


// 
PG_FUNCTION_INFO_V1(vector3d_constant);
Datum vector3d_constant(PG_FUNCTION_ARGS)
{
    double value = PG_GETARG_FLOAT8(0);
    
    PG_RETURN_ARRAYTYPE_P(Vector3dConstant(value));
}

// 
PG_FUNCTION_INFO_V1(vector3d_random);
Datum vector3d_random(PG_FUNCTION_ARGS)
{
    PG_RETURN_ARRAYTYPE_P(Vector3dRandom());
}


//////////////////////////////VECTOR ARITHMETIC/////////////////////////////////


// VECTOR ADDITION
PG_FUNCTION_INFO_V1(vector3d_add);
Datum vector3d_add(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(Vector3dAdd(a1,a2));
}

// VECTOR SUBTRACTION
PG_FUNCTION_INFO_V1(vector3d_subtract);
Datum vector3d_subtract(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(Vector3dSubtract(a1,a2));
}

// VECTOR DIVISION BY SCALAR
PG_FUNCTION_INFO_V1(vector3d_scalar_division);
Datum vector3d_scalar_division(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);
    
    PG_RETURN_ARRAYTYPE_P(Vector3dScalarDivision(array, scalar));
}

// VECTOR MULTIPLICATION BY SCALAR
PG_FUNCTION_INFO_V1(vector3d_scalar_product);
Datum vector3d_scalar_product(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);
    
    PG_RETURN_ARRAYTYPE_P(Vector3dScalarProduct(array, scalar));
}

// VECTOR DOT PRODUCT
PG_FUNCTION_INFO_V1(vector3d_dot);
Datum vector3d_dot(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(Vector3dDot(a1,a2));
}

// VECTOR CROSS PRODUCT
PG_FUNCTION_INFO_V1(vector3d_cross);
Datum vector3d_cross(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(Vector3dCross(a1, a2));
}

// CALCULATES THE NORM/LENGTH OF THE VECTOR
PG_FUNCTION_INFO_V1(vector3d_norm);
Datum vector3d_norm(PG_FUNCTION_ARGS)
{
    ArrayType *vector3d = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(Vector3dNorm(vector3d));
}

// RETURNS THE NORMALIZED VECTOR
PG_FUNCTION_INFO_V1(vector3d_normalized);
Datum vector3d_normalized(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(Vector3dNormalized(array));
}

// DISTANCE BETWEEN VECTORS
PG_FUNCTION_INFO_V1(vector3d_distance);
Datum vector3d_distance(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(Vector3dDistance(a1,a2));
}

// ANGLE BETWEEN VECTORS
PG_FUNCTION_INFO_V1(vector3d_angle);
Datum vector3d_angle(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(Vector3dAngle(a1,a2));
}

// ABSOLUTE ANGLE BETWEEN VECTORS
PG_FUNCTION_INFO_V1(vector3d_abs_angle);
Datum vector3d_abs_angle(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(Vector3dAbsAngle(a1,a2));
}