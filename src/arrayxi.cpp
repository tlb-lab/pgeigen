#include "eigen.h"
#include "arrayxi.h"

using namespace Eigen;

inline int intersect_size(const ArrayXi &a, const ArrayXi &b)
{
    return (a == b).cast<int>().min(a).count();
}

inline int unique_left_size(const ArrayXi &a, const ArrayXi &b)
{
    return (a != b).cast<int>().min(a).count();
}

inline int unique_right_size(const ArrayXi &a, const ArrayXi &b)
{
    return (a != b).cast<int>().min(b).count();
}

// CONVERTS A POSTGRESQL ARRAYTYPE INTO AN EIGEN ARRAY OF INTEGERS
inline ArrayXi arraytype_to_arrayxi(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO EIGEN ARRAYXI
    Map<ArrayXi> arrayxi((int *) ARR_DATA_PTR(array), arraytype_num_elems(array));
    
    return arrayxi;
}

// RETURNS ARRAY WITH GIVEN CONSTANT VALUE
extern "C"
ArrayType *ArrayXiCopy(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi((int *) ARR_DATA_PTR(array), arraytype_num_elems(array));

    return densebase_to_int32_arraytype(arrayxi);
}

// RETURNS ARRAY WITH GIVEN CONSTANT VALUE
extern "C"
ArrayType *ArrayXiConstant(int size, int value)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::Constant(size, value);

    return densebase_to_int32_arraytype(arrayxi);
}

// RETURNS ARRAY WITH RANDOM ELEMENTS
extern "C"
ArrayType *ArrayXiRandom(int size)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::Random(size);

    return densebase_to_int32_arraytype(arrayxi);
}

// RETURNS AN ARRAYS WITH ELEMENTS EQUALLY SPACE BETWEEN LOW AND HIGH
extern "C"
ArrayType *ArrayXiLinSpaced(int size, int low, int high)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::LinSpaced(size, low, high);

    return densebase_to_int32_arraytype(arrayxi);
}

// RETURNS THE NUMBER OF COEFFICIENTS
extern "C"
int ArrayXiSize(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);
    
    // RETURNS THE SIZE FOR 1D ARRAY
    return arrayxi.innerSize();
}

// RETURNS THE NUMBER OF NON-NULL COEFFICIENTS
extern "C"
int ArrayXiNonZeros(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return arrayxi.count();
}

// RETURNS THE SMALLEST COEFFICIENT OF THE ARRAY
extern "C"
int ArrayXiMinCoeff(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return arrayxi.minCoeff();
}

// RETURNS THE LARGEST COEFFICIENT OF THE ARRAY
extern "C"
int ArrayXiMaxCoeff(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return arrayxi.maxCoeff();
}

// RETURNS THE SUM OF ALL ELEMENTS OF AN ARRAY
extern "C"
long ArrayXiSum(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return arrayxi.sum();
}

// RETURNS THE MEAN OF THE ARRAY
extern "C"
double ArrayXiMean(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return arrayxi.mean();
}

// RETURNS THE ABSOLUTE OF THE ARRAY
extern "C"
ArrayType *ArrayXiAbs(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return densebase_to_int32_arraytype(arrayxi.abs());
}

// RETURNS A BINARY VERSION OF THE ARRAY, I.E. ALL ELEMENTS > 0 WILL BE 1
extern "C"
ArrayType *ArrayXiBinary(ArrayType *array)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return densebase_to_int32_arraytype((arrayxi > 0).cast<int>());
}

// SUM TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiAdd(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);
    
    return densebase_to_int32_arraytype(arrayxi1 + arrayxi2);
}

// SUBTRACTS TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiSub(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return densebase_to_int32_arraytype(arrayxi1 - arrayxi2);
}

// MULTIPLIES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiMul(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return densebase_to_int32_arraytype(arrayxi1 * arrayxi2);
}

// DIVIDES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiDiv(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return densebase_to_int32_arraytype(arrayxi1 / arrayxi2);
}


////////////////////////////SCALAR ARITHMETIC///////////////////////////////////


// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXiAddScalar(ArrayType *array, int scalar)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return densebase_to_int32_arraytype(arrayxi + scalar);
}

// SUBTRACT SCALAR FROM EVERY ELEMENT
extern "C"
ArrayType *ArrayXiSubScalar(ArrayType *array, int scalar)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return densebase_to_int32_arraytype(arrayxi - scalar);
}

// MULTIPLY SCALAR WITH EVERY ELEMENT
extern "C"
ArrayType *ArrayXiMulScalar(ArrayType *array, int scalar)
{
    ArrayXi arrayxi = arraytype_to_arrayxi(array);

    return densebase_to_int32_arraytype(arrayxi * scalar);
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
extern "C"
bool ArrayXiEqual(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);
    
    return (arrayxi1==arrayxi2).all();
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
extern "C"
bool ArrayXiContains(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return ((arrayxi1 > 0) == (arrayxi2 > 0)).count() == arrayxi2.count();
}

// RETURNS TRUE IF THE ARRAYS HAVE AT LEAST ONE NON-NULL ELEMENT IN COMMON
extern "C"
bool ArrayXiOverlaps(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return ((arrayxi1 > 0) == (arrayxi2 > 0)).any();
}

// RETURNS THE INTERSECTION BETWEEN THE ARRAYS
extern "C"
ArrayType *ArrayXiIntersection(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return densebase_to_int32_arraytype((arrayxi1==arrayxi2).select(arrayxi1, 0));
}

// RETURNS THE UNION OF BOTH ARRAYS AS THE MAXIMUM OF COFFICIENTS
extern "C"
ArrayType *ArrayXiUnion(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // DEFINE UNION AS THE MAXIMUM OF BOTH ARRAYS: A(2,3,4), B(4,2,3) = C(4,3,4)
    return densebase_to_int32_arraytype(arrayxi1.max(arrayxi2));
}

// RETURNS THE BINARY UNION OF BOTH ARRAYS
extern "C"
ArrayType *ArrayXiBinaryUnion(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    ArrayXi binary_union = (arrayxi1.max(arrayxi2) > 0).cast<int>();
    
    return densebase_to_int32_arraytype(binary_union);
}


///////////////////////NORMALIZED SIMILARITY METRICS////////////////////////////


// RETURNS THE BRAY-CURTIS DISSIMILARITY
extern "C"
double ArrayXiBrayCurtis(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return 1.0 - ((arrayxi1-arrayxi2).abs().sum() / (double) (arrayxi1+arrayxi2).sum());
}

// RETURNS THE DICE SIMILARITY
extern "C"
double ArrayXiDice(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);
    
    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    if (A != 0 && B != 0) similarity = 2 * c / (double) (A+B);
    
    return similarity;
}

// RETURNS THE KULCZYNSKI SIMILARITY
extern "C"
double ArrayXiKulczynski(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();
    
    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c * (A + B) / (double) (2 * A * B);
    
    return similarity;
}

// RETURNS THE NORMALIZED EUCLIDEAN SIMILARITY
extern "C"
double ArrayXiNormEuclidean(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    return sqrt((A + B - 2 * c) / (double) arrayxi1.size());
}

// RETURNS THE NORMALIZED MANHATTAN SIMILARITY
extern "C"
double ArrayXiNormManhattan(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    return (A + B - 2 * c) / (double) arrayxi1.size();
}

// RETURNS THE OCHIAI/COSINE SIMILARITY
extern "C"
double ArrayXiOchiai(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / sqrt(A*B);
    
    return similarity;
}

// RETURNS THE RUSSELL-RAO SIMILARITY
extern "C"
double ArrayXiRussellRao(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    return c / (double) arrayxi1.size();
}

// RETURNS THE SIMPSON SIMILARITY - FUZCAV DEFAULT SIMILARITY
extern "C"
double ArrayXiSimpson(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / (double) std::min(A,B);
    
    return similarity;
}

// RETURNS THE SIMPSON SIMILARITY WITH MAX() INSTEAD OF MIN()
extern "C"
double ArrayXiSimpsonGlobal(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / (double) std::max(A,B);
    
    return similarity;
}

// RETURNS THE TANIMOTO/JACCARD SIMILARITY (I.E. TVERSKY ALPHA=1, BETA=1)
extern "C"
double ArrayXiTanimoto(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / (double) (A + B - c);

    return similarity;
}

// RETURNS THE TVERSKY SIMILARITY
extern "C"
double ArrayXiTversky(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) 
    {
        similarity = c / (double) (arrayxi_tversky_alpha * A + 
                                  arrayxi_tversky_beta * B + 
                                  (1 - arrayxi_tversky_alpha - arrayxi_tversky_beta) * c);
    }
        
    return similarity;
}

////////////////////////////////QUANTITATIVE/NON-BINARY METRICS///////////////////////////////

// RETURNS THE TANIMOTO/JACCARD SIMILARITY
extern "C"
double ArrayXiTanimotoNB(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);
    
    ArrayXi arrayxi1_sq = arrayxi1 * arrayxi1;
    ArrayXi arrayxi2_sq = arrayxi2 * arrayxi2;
    ArrayXi arrayxiC_sq = arrayxi1 * arrayxi2;

    unsigned int A = arrayxi1_sq.sum();
    unsigned int B = arrayxi2_sq.sum();

    unsigned int c = arrayxiC_sq.sum();

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / (double) (A + B - c);

    return similarity;
}

// RETURNS THE DICE SIMILARITY
extern "C"
double ArrayXiDiceNB(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);
    
    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1_sq = arrayxi1 * arrayxi1;
    ArrayXi arrayxi2_sq = arrayxi2 * arrayxi2;
    ArrayXi arrayxiC_sq = arrayxi1 * arrayxi2;
    
    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1_sq.sum();
    unsigned int B = arrayxi2_sq.sum();

    // COMMON COUNTS
    unsigned int c = arrayxiC_sq.sum();

    if (A != 0 && B != 0) similarity = 2 * c / (double) (A+B);
    
    return similarity;
}

extern "C"
double ArrayXiCosineNB(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);
    
    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);    
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1_sq = arrayxi1 * arrayxi1;
    ArrayXi arrayxi2_sq = arrayxi2 * arrayxi2;
    ArrayXi arrayxiC_sq = arrayxi1 * arrayxi2;

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1_sq.sum();
    unsigned int B = arrayxi2_sq.sum();

    // COMMON COUNTS
    unsigned int c = arrayxiC_sq.sum();

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / sqrt(A*B);
    
    return similarity;
}


////////////////////////////////DISTANCE METRICS////////////////////////////////


// RETURNS THE EUCLIDEAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayXiEuclideanDist(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return sqrt((arrayxi1-arrayxi2).square().sum());
}

// RETURNS THE MANHATTAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayXiManhattanDist(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    return (arrayxi1-arrayxi2).abs().sum();
}

// RETURNS THE MEAN HAMMING DISTANCE
extern "C"
double ArrayXiMeanHammingDist(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // UNIQUE COUNTS IN BOTH ARRAYS
    unsigned int a = unique_left_size(arrayxi1,arrayxi2);
    unsigned int b = unique_right_size(arrayxi1,arrayxi2);
    
    return (a + b) / (double) arrayxi1.size();
}


/////////////////////FUZCAV-SPECIFIC SIMILARITY METRICS/////////////////////////


// RETURNS THE FUZCAV SIMILARITY
extern "C"
double ArrayXiFuzCavSimGlobal(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);

    // COUNTS THAT ARE SHARED BETWEEN THE FUZCAV FINGERPRINTS
    unsigned int c = intersect_size(arrayxi1,arrayxi2);

    return (c / (double) std::max(arrayxi1.count(), arrayxi2.count()));
}

/* Returns the maximum possible similarity value between two arrays for a given 
 * metric. This is necessary to calculate similarity values for inner gist nodes, 
 * which are not real fingerprints.
 * 
 * From: Swamidass SJ, Baldi P. Bounds and algorithms for fast exact searches of 
 *       chemical fingerprints in linear and sublinear time.    
 *       j chem inf model. 2007 mar-apr;47(2):302-17 
 * 
 * Where:
 *        a is the count of values > 0 in array A but not in array B.
 *        b is the count of values > 0 in array B but not in array A.
 *        c is the count of equal position in both array A and array B.
 *        d is the count of the zeros in both array A and array B.
 *      
 *        In addition:
 * 
 *        n = ( a + b + c + d ) total number of positions in arrays A or B.
 *        A = ( a + c ) the count of the values > 0 in object A.
 *        B = ( b + c ) the count of the values > 0 in object B.
 */
extern "C"
float SimilarityUpperBound(ArrayType *a1, ArrayType *a2, char *metric)
{
    float upper_bound = 0.0;
    
    // MAP DATA TO EIGEN ARRAYS
    ArrayXi arrayxi1 = arraytype_to_arrayxi(a1);
    ArrayXi arrayxi2 = arraytype_to_arrayxi(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxi1,arrayxi2);
    
    // QUERY ARRAY HAS TO BE CONVERTED TO BINARY VERSION TO BE COMPATIBLE WITH
    // THE GIST INTERNAL NODES
    unsigned int c = intersect_size(arrayxi1, (arrayxi2 > 0).cast<int>());
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();
    
    // IN GIST CONTEXT, A1 IS KEY A2 IS QUERY

    if (strcmp(metric,"dice") == 0) 
    {
        upper_bound = 2 * c / (float) B;
    }
    
    else if (strcmp(metric,"euclidean") == 0) 
    {
        upper_bound = sqrt((B - 2 * c) / (float) arrayxi1.size());
    }
    
    else if (strcmp(metric,"kulczynski") == 0) 
    {
        upper_bound = A + B / (float) (2 * std::max(A,B));
    }
    
    else if (strcmp(metric,"manhattan") == 0) 
    {
        upper_bound = (B - 2 * c) / (float) arrayxi1.size();
    }
    
    else if (strcmp(metric,"ochiai") == 0) 
    {
        upper_bound = c / sqrt(B);
    }
    
    else if (strcmp(metric,"russell-rao") == 0) 
    {
        upper_bound = B / (float) arrayxi1.size();
    }
    
    // NO REDUCTION OF SEARCH SPACE HERE
    else if (strcmp(metric,"simpson") == 0) 
    {
        upper_bound = c / (float) std::min(A,B);
    }
    
    else if (strcmp(metric,"tversky") == 0) 
    {
        upper_bound = c / (arrayxi_tversky_beta * B);
    }
    
    else 
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("unknown metric for similarity upper bound calculation: %s", metric)));
    }
    
    return upper_bound;
}