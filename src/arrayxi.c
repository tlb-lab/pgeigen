#include "arrayxi.h"
#include "fmgr.h"

bool array_contains_nulls(ArrayType *array)
{
    int         nelems;
    bits8      *bitmap;
    int         bitmask;

    /* Easy answer if there's no null bitmap */
    if (!ARR_HASNULL(array))
        return false;

    nelems = ArrayGetNItems(ARR_NDIM(array), ARR_DIMS(array));

    bitmap = ARR_NULLBITMAP(array);

    /* check whole bytes of the bitmap byte-at-a-time */
    while (nelems >= 8)
    {
        if (*bitmap != 0xFF)
            return true;
        bitmap++;
        nelems -= 8;
    }

    /* check last partial byte */
    bitmask = 1;
    while (nelems > 0)
    {
        if ((*bitmap & bitmask) == 0)
            return true;
        bitmask <<= 1;
        nelems--;
    }

    return false;
}

//
PG_FUNCTION_INFO_V1(array_has_nulls);
Datum array_has_nulls(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_BOOL(array_contains_nulls(array));
}

/*
 ARRAY CREATION FUNCTIONS
*/

PG_FUNCTION_INFO_V1(arrayxi_random);
Datum arrayxi_random(PG_FUNCTION_ARGS)
{
    int size = PG_GETARG_INT32(0);

    PG_RETURN_ARRAYTYPE_P(ArrayxiRandom(size));
}

PG_FUNCTION_INFO_V1(arrayxi_constant);
Datum arrayxi_constant(PG_FUNCTION_ARGS)
{
    int size = PG_GETARG_INT32(0);
    int value = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiConstant(size, value));
}

/*
 OPERATIONS ON SINGLE ARRAYS
*/

// RETURNS THE NUMBER OF ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxi_size);
Datum arrayxi_size(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxiSize(array));
}

// RETURNS THE NUMBER OF NON-ZERO ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxi_nonzeros);
Datum arrayxi_nonzeros(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxiNonZeros(array));
}

// RETURNS SMALLEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxi_min);
Datum arrayxi_min(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxiMinCoeff(array));
}

// RETURNS LARGEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxi_max);
Datum arrayxi_max(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxiMaxCoeff(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxi_sum);
Datum arrayxi_sum(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT64(ArrayxiSum(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxi_mean);
Datum arrayxi_mean(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayxiMean(array));
}

PG_FUNCTION_INFO_V1(arrayxi_abs);
Datum arrayxi_abs(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(ArrayxiAbs(array));
}

/*
 ARRAY ARITHMETIC FUNCTIONS
*/

PG_FUNCTION_INFO_V1(arrayxi_add);
Datum arrayxi_add(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiAdd(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_sub);
Datum arrayxi_sub(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiSub(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_mul);
Datum arrayxi_mul(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiMul(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_div);
Datum arrayxi_div(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiDiv(a1,a2));
}

/* ARRAY SCALAR ARITHMETIC FUNCTIONS */

//
PG_FUNCTION_INFO_V1(arrayxi_add_scalar);
Datum arrayxi_add_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiAddScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxi_sub_scalar);
Datum arrayxi_sub_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiSubScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxi_mul_scalar);
Datum arrayxi_mul_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiMulScalar(array,scalar));
}

/* ARRAY SET ALGEBRA */


// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
PG_FUNCTION_INFO_V1(arrayxi_contains);
Datum arrayxi_contains(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayxiContains(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_contained);
Datum arrayxi_contained(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayxiContains(a2,a1));
}

// RETURNS TRUE IF THE ARRAYS HAVE OVERLAPPING NON-NULL ELEMENTS
PG_FUNCTION_INFO_V1(arrayxi_overlaps);
Datum arrayxi_overlaps(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayxiOverlaps(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_intersection);
Datum arrayxi_intersection(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiIntersection(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_union);
Datum arrayxi_union(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayxiUnion(a1,a2));
}


/* DISTANCE AND SIMILARITY METRICS */


// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_euclidean);
Datum arrayxi_euclidean(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiEuclidean(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_manhattan);
Datum arrayxi_manhattan(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiManhattan(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_kulcz);
Datum arrayxi_kulcz(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiKulczynski(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_bray_curtis);
Datum arrayxi_bray_curtis(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiBrayCurtis(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_ochiai);
Datum arrayxi_ochiai(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiOchiai(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_fuzcavsim);
Datum arrayxi_fuzcavsim(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiFuzCavSim(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_fuzcavsim_global);
Datum arrayxi_fuzcavsim_global(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayxiFuzCavSimGlobal(a1,a2));
}