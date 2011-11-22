#include "arrayxi.h"
#include "fmgr.h"
#include <utils/builtins.h>

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


////////////////////////////ARRAY CREATION FUNCTIONS////////////////////////////


PG_FUNCTION_INFO_V1(arrayxi_random);
Datum arrayxi_random(PG_FUNCTION_ARGS)
{
    int size = PG_GETARG_INT32(0);

    PG_RETURN_ARRAYTYPE_P(ArrayXiRandom(size));
}

PG_FUNCTION_INFO_V1(arrayxi_constant);
Datum arrayxi_constant(PG_FUNCTION_ARGS)
{
    int size = PG_GETARG_INT32(0);
    int value = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiConstant(size, value));
}


//////////////////////////OPERATIONS ON SINGLE ARRAYS///////////////////////////


// RETURNS THE NUMBER OF ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxi_size);
Datum arrayxi_size(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXiSize(array));
}

// RETURNS THE NUMBER OF NON-ZERO ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(arrayxi_nonzeros);
Datum arrayxi_nonzeros(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXiNonZeros(array));
}

// RETURNS SMALLEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxi_min);
Datum arrayxi_min(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXiMinCoeff(array));
}

// RETURNS LARGEST COEFFICIENT IN ARRAY
PG_FUNCTION_INFO_V1(arrayxi_max);
Datum arrayxi_max(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXiMaxCoeff(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxi_sum);
Datum arrayxi_sum(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT64(ArrayXiSum(array));
}

// SUMS ARRAY
PG_FUNCTION_INFO_V1(arrayxi_mean);
Datum arrayxi_mean(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(ArrayXiMean(array));
}

PG_FUNCTION_INFO_V1(arrayxi_abs);
Datum arrayxi_abs(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(ArrayXiAbs(array));
}

PG_FUNCTION_INFO_V1(arrayxi_binary);
Datum arrayxi_binary(PG_FUNCTION_ARGS)
{
    ArrayType  *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(ArrayXiBinary(array));
}


//////////////////////////ARRAY ARITHMETIC FUNCTIONS////////////////////////////


PG_FUNCTION_INFO_V1(arrayxi_add);
Datum arrayxi_add(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiAdd(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_sub);
Datum arrayxi_sub(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiSub(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_mul);
Datum arrayxi_mul(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiMul(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_div);
Datum arrayxi_div(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiDiv(a1,a2));
}


//////////////////////ARRAY SCALAR ARITHMETIC FUNCTIONS/////////////////////////


//
PG_FUNCTION_INFO_V1(arrayxi_add_scalar);
Datum arrayxi_add_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiAddScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxi_sub_scalar);
Datum arrayxi_sub_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiSubScalar(array,scalar));
}

//
PG_FUNCTION_INFO_V1(arrayxi_mul_scalar);
Datum arrayxi_mul_scalar(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    int        scalar = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiMulScalar(array,scalar));
}

/* ARRAY SET ALGEBRA */


// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
PG_FUNCTION_INFO_V1(arrayxi_contains);
Datum arrayxi_contains(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayXiContains(a1,a2));
}

PG_FUNCTION_INFO_V1(arrayxi_contained);
Datum arrayxi_contained(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayXiContains(a2,a1));
}

// RETURNS TRUE IF THE ARRAYS HAVE OVERLAPPING NON-NULL ELEMENTS
PG_FUNCTION_INFO_V1(arrayxi_overlaps);
Datum arrayxi_overlaps(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayXiOverlaps(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_intersection);
Datum arrayxi_intersection(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiIntersection(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_union);
Datum arrayxi_union(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiUnion(a1,a2));
}


///////////////////////NORMALIZED SIMILARITY METRICS////////////////////////////


// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_bray_curtis);
Datum arrayxi_bray_curtis(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiBrayCurtis(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_dice);
Datum arrayxi_dice(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiKulczynski(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_kulcz);
Datum arrayxi_kulcz(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiKulczynski(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_ochiai);
Datum arrayxi_ochiai(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiOchiai(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_russell_rao);
Datum arrayxi_russell_rao(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiRussellRao(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_simpson);
Datum arrayxi_simpson(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiSimpson(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_tversky);
Datum arrayxi_tversky(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiTversky(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_fuzcavsim_global);
Datum arrayxi_fuzcavsim_global(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiFuzCavSimGlobal(a1,a2));
}


//////////////////////////NORMAL DISTANCE METRICS///////////////////////////////


// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_euclidean_dist);
Datum arrayxi_euclidean_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiEuclideanDist(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_manhattan_dist);
Datum arrayxi_manhattan_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiManhattanDist(a1,a2));
}



///////////////////DEFAULT METRIC CUTOFF GETTERS & SETTERS//////////////////////


// DEFAULT LIMITS (USED FOR GIST FUNCTIONS)
float4 arrayxi_tversky_alpha   = 1.0f;
float4 arrayxi_tversky_beta    = 1.0f;

// RETURNS THE CURRENT LIMIT FOR THE SPECIFIED METRIC
PG_FUNCTION_INFO_V1(show_arrayxi_similarity_limit);
Datum show_arrayxi_similarity_limit(PG_FUNCTION_ARGS)
{
    char  *metric = PG_GETARG_TEXT_AS_CSTRING(0);
    float4  limit;

    if (strcmp(metric, "tversky_alpha") == 0) limit = arrayxi_tversky_alpha;
    else if (strcmp(metric, "tversky_beta") == 0) limit = arrayxi_tversky_beta;

    else
    {
        ereport(ERROR,
                    (errcode(ERRCODE_DATA_EXCEPTION),
                     errmsg("unknown similarity metric or parameter: \"%s\"", metric))
                );
    }

    PG_RETURN_FLOAT4(limit);
}

// SETS THE LIMIT FOR THE SPECIFIED METRIC
PG_FUNCTION_INFO_V1(set_arrayxi_similarity_limit);
Datum set_arrayxi_similarity_limit(PG_FUNCTION_ARGS)
{
    float4  limit  = PG_GETARG_FLOAT4(0);
    char   *metric = PG_GETARG_TEXT_AS_CSTRING(1);

    if (limit < 0 || limit > 1.0)
    {
        ereport(ERROR,
                    (errcode(ERRCODE_DATA_EXCEPTION),
                     errmsg("invalid limit %f for parameter \"%s\": value has to be in the range [0.0 1.0].",
                            limit, metric)));
    }

    if (strcmp(metric, "tversky_alpha") == 0) arrayxi_tversky_alpha = limit;
    else if (strcmp(metric, "tversky_beta") == 0) arrayxi_tversky_beta = limit;

    else
    {
        ereport(ERROR,
                    (errcode(ERRCODE_DATA_EXCEPTION),
                     errmsg("unkknown similarity metric: \"%s\"", metric))
                );
    }

    PG_RETURN_FLOAT4(limit);
 }