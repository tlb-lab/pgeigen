#include "arrayxi.h"
#include "fmgr.h"
#include <utils/builtins.h>


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

PG_FUNCTION_INFO_V1(arrayxi_lin_spaced);
Datum arrayxi_lin_spaced(PG_FUNCTION_ARGS)
{
    int size = PG_GETARG_INT32(0);
    int low = PG_GETARG_INT32(1);
    int high = PG_GETARG_INT32(2);

    if (size > high)
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("the size of the linear-spaced array cannot be greater than the HIGH parameter.")));
    }
    
    PG_RETURN_ARRAYTYPE_P(ArrayXiLinSpaced(size, low, high));
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


// RETURNS TRUE IF BOTH ARRAYS HAVE THE SAME ELEMENTS
PG_FUNCTION_INFO_V1(arrayxi_eq);
Datum arrayxi_eq(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayXiEqual(a1,a2));
}

// RETURNS TRUE IF THE ARRAYS ARE DISTINCT
PG_FUNCTION_INFO_V1(arrayxi_ne);
Datum arrayxi_ne(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_BOOL(ArrayXiEqual(a1,a2)==false);
}

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

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_binary_union);
Datum arrayxi_binary_union(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(ArrayXiBinaryUnion(a1,a2));
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

    PG_RETURN_FLOAT8(ArrayXiDice(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxi_euclidean);
Datum arrayxi_euclidean(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiNormEuclidean(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_kulcz);
Datum arrayxi_kulcz(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiKulczynski(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxi_manhattan);
Datum arrayxi_manhattan(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiNormManhattan(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_ochiai);
Datum arrayxi_ochiai(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiOchiai(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxi_russell_rao);
Datum arrayxi_russell_rao(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiRussellRao(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxi_simpson);
Datum arrayxi_simpson(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiSimpson(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxi_simpson_global);
Datum arrayxi_simpson_global(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiSimpsonGlobal(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxi_tanimoto);
Datum arrayxi_tanimoto(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiTanimoto(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxi_tversky);
Datum arrayxi_tversky(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiTversky(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxi_fuzcavsim_global);
Datum arrayxi_fuzcavsim_global(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiFuzCavSimGlobal(a1,a2));
}

///////////////// QUANTITATIVE / NON-BINARY METRICS /////////////
//
PG_FUNCTION_INFO_V1(arrayxi_tanimoto_nb);
Datum arrayxi_tanimoto_nb(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiTanimotoNB(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxi_dice_nb);
Datum arrayxi_dice_nb(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiDiceNB(a1,a2));
}

//
PG_FUNCTION_INFO_V1(arrayxi_cosine_nb);
Datum arrayxi_cosine_nb(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiCosineNB(a1,a2));
}


//////////////////////////NORMAL DISTANCE METRICS///////////////////////////////


// RETURNS THE DICE DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_dice_dist);
Datum arrayxi_dice_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiDice(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxi_euclidean_dist);
Datum arrayxi_euclidean_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiNormEuclidean(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_kulcz_dist);
Datum arrayxi_kulcz_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiKulczynski(a1,a2));
}

// 
PG_FUNCTION_INFO_V1(arrayxi_manhattan_dist);
Datum arrayxi_manhattan_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiNormManhattan(a1,a2));
}

// RETURNS THE BRAY-CURTIS DISSIMILARITY
PG_FUNCTION_INFO_V1(arrayxi_ochiai_dist);
Datum arrayxi_ochiai_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiOchiai(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_russell_rao_dist);
Datum arrayxi_russell_rao_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiRussellRao(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_simpson_dist);
Datum arrayxi_simpson_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiSimpson(a1,a2));
}

// RETURNS THE INTERSECTION BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_tversky_dist);
Datum arrayxi_tversky_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(1 - ArrayXiTversky(a1,a2));
}

// RETURNS THE MEAN HAMMING DISTANCE BETWEEN BOTH ARRAYS
PG_FUNCTION_INFO_V1(arrayxi_mean_hamming_dist);
Datum arrayxi_mean_hamming_dist(PG_FUNCTION_ARGS)
{
    ArrayType  *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType  *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_FLOAT8(ArrayXiMeanHammingDist(a1,a2));
}


///////////////////DEFAULT METRIC CUTOFF GETTERS & SETTERS//////////////////////


// DEFAULT LIMITS (USED MOSTLY FOR GIST FUNCTIONS)

float4 arrayxi_dice_limit        = 0.5f;
float4 arrayxi_euclidean_limit   = 0.8f;
float4 arrayxi_kulcz_limit       = 0.5f;
float4 arrayxi_manhattan_limit   = 0.9f;
float4 arrayxi_ochiai_limit      = 0.7f;
float4 arrayxi_russell_rao_limit = 0.5f;
float4 arrayxi_simpson_limit     = 0.16f;
float4 arrayxi_tanimoto_limit    = 0.6f;
float4 arrayxi_tversky_limit     = 0.5f;
float4 arrayxi_tversky_alpha     = 1.0f;
float4 arrayxi_tversky_beta      = 1.0f;

// RETURNS THE CURRENT LIMIT FOR THE SPECIFIED METRIC
PG_FUNCTION_INFO_V1(show_arrayxi_similarity_limit);
Datum show_arrayxi_similarity_limit(PG_FUNCTION_ARGS)
{
    char  *metric = PG_GETARG_TEXT_AS_CSTRING(0);
    float4  limit;

    if (strcmp(metric, "dice") == 0) limit = arrayxi_dice_limit;
    else if (strcmp(metric, "euclidean") == 0) limit = arrayxi_euclidean_limit;
    else if (strcmp(metric, "kulczynski") == 0) limit = arrayxi_kulcz_limit;
    else if (strcmp(metric, "manhattan") == 0) limit = arrayxi_manhattan_limit;
    else if (strcmp(metric, "ochiai") == 0) limit = arrayxi_ochiai_limit;
    else if (strcmp(metric, "rusell-rao") == 0) limit = arrayxi_russell_rao_limit;
    else if (strcmp(metric, "simpson") == 0) limit = arrayxi_simpson_limit;
    else if (strcmp(metric, "tanimoto") == 0) limit = arrayxi_tanimoto_limit;
    else if (strcmp(metric, "tversky") == 0) limit = arrayxi_tversky_limit;
    else if (strcmp(metric, "tversky_alpha") == 0) limit = arrayxi_tversky_alpha;
    else if (strcmp(metric, "tversky_beta") == 0) limit = arrayxi_tversky_beta;

    else
    {
        ereport(ERROR,
                    (errcode(ERRCODE_DATA_EXCEPTION),
                     errmsg("unknown similarity metric or parameter: \"%s\"", metric))
                );
    }
    
    elog(INFO, "Current %s limit: %f", metric, limit);

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

    if (strcmp(metric, "dice") == 0) arrayxi_dice_limit = limit;
    else if (strcmp(metric, "euclidean") == 0) arrayxi_euclidean_limit = limit;
    else if (strcmp(metric, "kulczynski") == 0) arrayxi_kulcz_limit = limit;
    else if (strcmp(metric, "manhattan") == 0) arrayxi_manhattan_limit = limit;
    else if (strcmp(metric, "ochiai") == 0) arrayxi_ochiai_limit = limit;
    else if (strcmp(metric, "rusell-rao") == 0) arrayxi_russell_rao_limit = limit;
    else if (strcmp(metric, "simpson") == 0) arrayxi_simpson_limit = limit;
    else if (strcmp(metric, "tanimoto") == 0) arrayxi_tanimoto_limit = limit;
    else if (strcmp(metric, "tversky") == 0) arrayxi_tversky_limit = limit;
    else if (strcmp(metric, "tversky_alpha") == 0) arrayxi_tversky_alpha = limit;
    else if (strcmp(metric, "tversky_beta") == 0) arrayxi_tversky_beta = limit;

    else
    {
        ereport(ERROR,
                    (errcode(ERRCODE_DATA_EXCEPTION),
                     errmsg("unknown similarity metric or parameter: \"%s\"", metric))
                );
    }
    
    elog(INFO, "Post setting limit: %f", limit);

    PG_RETURN_FLOAT4(limit);
 }
 

///////////ARRAY SIMILARITY METRICS COMPARING WITH THE CUTOFF VALUES////////////


// 
PG_FUNCTION_INFO_V1(arrayxi_dice_is_above_limit);
Datum arrayxi_dice_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiDice(a1,a2) >= arrayxi_dice_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_euclidean_is_above_limit);
Datum arrayxi_euclidean_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiNormEuclidean(a1,a2) >= arrayxi_euclidean_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_kulcz_is_above_limit);
Datum arrayxi_kulcz_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiKulczynski(a1,a2) >= arrayxi_kulcz_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_manhattan_is_above_limit);
Datum arrayxi_manhattan_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiNormManhattan(a1,a2) >= arrayxi_manhattan_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_ochiai_is_above_limit);
Datum arrayxi_ochiai_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiOchiai(a1,a2) >= arrayxi_ochiai_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_russell_rao_is_above_limit);
Datum arrayxi_russell_rao_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiRussellRao(a1,a2) >= arrayxi_russell_rao_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_simpson_is_above_limit);
Datum arrayxi_simpson_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiSimpson(a1,a2) >= arrayxi_simpson_limit);
}

//
PG_FUNCTION_INFO_V1(arrayxi_tanimoto_is_above_limit);
Datum arrayxi_tanimoto_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiTversky(a1,a2) >= arrayxi_tanimoto_limit);
}

// 
PG_FUNCTION_INFO_V1(arrayxi_tversky_is_above_limit);
Datum arrayxi_tversky_is_above_limit(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);
    
    PG_RETURN_BOOL(ArrayXiTversky(a1,a2) >= arrayxi_tversky_limit);
}