#include "arrayxd.h"
#include "fmgr.h"

/*
 OPERATIONS ON SINGLE ARRAYS
*/

// RETURNS THE NUMBER OF ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxd_size);
Datum arrayxd_size(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxdSize(array));
}

// RETURNS THE NUMBER OF NON-ZERO ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxd_nonzeros);
Datum arrayxd_nonzeros(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxdNonZeros(array));
}

// RETURNS SMALLEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxd_min);
Datum arrayxd_min(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayxdMinCoeff(array));
}

// RETURNS LARGEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxd_max);
Datum arrayxd_max(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayxdMaxCoeff(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxd_sum);
Datum arrayxd_sum(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayxdSum(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxd_mean);
Datum arrayxd_mean(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayxdMean(array));
}

PG_FUNCTION_INFO_V1(arrayxd_abs);
Datum arrayxd_abs(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(ArrayxdAbs(array));
}

/*
 ARRAY ARITHMETIC FUNCTIONS
*/

PG_FUNCTION_INFO_V1(arrayxd_add);
Datum arrayxd_add(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdAdd(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxd_sub);
Datum arrayxd_sub(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdSub(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxd_mul);
Datum arrayxd_mul(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdMul(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxd_div);
Datum arrayxd_div(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdDiv(a1,a2));
}

/* ARRAY SCALAR ARITHMETIC FUNCTIONS */

//
PG_FUNCTION_INFO_V1(arrayxd_add_scalar);
Datum arrayxd_add_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdAddScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxd_sub_scalar);
Datum arrayxd_sub_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdSubScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxd_mul_scalar);
Datum arrayxd_mul_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxdMulScalar(array,scalar));
}


/* DISTANCE AND SIMILARITY METRICS */


// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxd_euclidean);
Datum arrayxd_euclidean(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxdEuclidean(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxd_manhattan);
Datum arrayxd_manhattan(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxdManhattan(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxd_usrsim);
Datum arrayxd_usrsim(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxdUSRSim(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxd_usrcatsim);
Datum arrayxd_usrcatsim(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    float      ow = PG_GETARG_FLOAT4(2);
    float      hw = PG_GETARG_FLOAT4(3);
    float      rw = PG_GETARG_FLOAT4(4);
    float      aw = PG_GETARG_FLOAT4(5);
    float      dw = PG_GETARG_FLOAT4(6);
    
    PG_RETURN_FLOAT8(ArrayxdUSRCatSim(a1,a2,ow,hw,rw,aw,dw));
}