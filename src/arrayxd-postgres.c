#include "arrayxd.h"
#include "fmgr.h"

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

//
PG_FUNCTION_INFO_V1(array_has_nulls);
Datum array_has_nulls(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_BOOL(ArrayGetNItems(ARR_NDIM(array), ARR_DIMS(array)) == 0);
}


/*
 OPERATIONS ON SINGLE ARRAYS
*/

// RETURNS THE NUMBER OF ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxd_size);
Datum arrayxd_size(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXdSize(array));
}

// RETURNS THE NUMBER OF NON-ZERO ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxd_nonzeros);
Datum arrayxd_nonzeros(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXdNonZeros(array));
}

// RETURNS SMALLEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxd_min);
Datum arrayxd_min(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayXdMinCoeff(array));
}

// RETURNS LARGEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxd_max);
Datum arrayxd_max(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayXdMaxCoeff(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxd_sum);
Datum arrayxd_sum(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayXdSum(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxd_mean);
Datum arrayxd_mean(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_FLOAT8(ArrayXdMean(array));
}

PG_FUNCTION_INFO_V1(arrayxd_abs);
Datum arrayxd_abs(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(ArrayXdAbs(array));
}

/*
 ARRAY ARITHMETIC FUNCTIONS
*/

PG_FUNCTION_INFO_V1(arrayxd_add);
Datum arrayxd_add(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdAdd(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxd_sub);
Datum arrayxd_sub(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdSub(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxd_mul);
Datum arrayxd_mul(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdMul(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxd_div);
Datum arrayxd_div(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdDiv(a1,a2));
}

/* ARRAY SCALAR ARITHMETIC FUNCTIONS */

//
PG_FUNCTION_INFO_V1(arrayxd_add_scalar);
Datum arrayxd_add_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdAddScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxd_sub_scalar);
Datum arrayxd_sub_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdSubScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxd_mul_scalar);
Datum arrayxd_mul_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXdMulScalar(array,scalar));
}


/* DISTANCE AND SIMILARITY METRICS */


// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxd_euclidean);
Datum arrayxd_euclidean(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXdEuclidean(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxd_manhattan);
Datum arrayxd_manhattan(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXdManhattan(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxd_usrsim);
Datum arrayxd_usrsim(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXdUSRSim(a1,a2));
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

    PG_RETURN_FLOAT8(ArrayXdUSRCatSim(a1,a2,ow,hw,rw,aw,dw));
}