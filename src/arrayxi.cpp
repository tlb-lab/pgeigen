#include <Eigen/Dense>
#include "arrayxi.h"

using namespace Eigen;

// CONSTRUCTS A POSTGRESQL ARRAY FROM AN EIGEN OBJECTS
ArrayType *arrayxi_to_arraytype(const ArrayXi &arrayxi, int size)
{
    const int *data = arrayxi.data();
    Datum *d = (Datum *) palloc(sizeof(Datum) * size);

    for (int i = 0; i < size; i++) d[i] = Int32GetDatum(data[i]);

    // CONSTRUCT ARRAY
    return construct_array(d, size, INT4OID, sizeof(int4), true, 'i');
}

// RETURNS ARRAY WITH GIVEN CONSTANT VALUE
extern "C"
ArrayType *ArrayXiCopy(ArrayType *array)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(array);

    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS ARRAY WITH GIVEN CONSTANT VALUE
extern "C"
ArrayType *ArrayXiConstant(int size, int value)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::Constant(size, value);

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS ARRAY WITH RANDOM ELEMENTS
extern "C"
ArrayType *ArrayXiRandom(int size)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::Random(size);

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS AN ARRAYS WITH ELEMENTS EQUALLY SPACE BETWEEN LOW AND HIGH
extern "C"
ArrayType *ArrayXiLinSpaced(int size, int low, int high)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::LinSpaced(size, low, high);

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS THE NUMBER OF COEFFICIENTS
extern "C"
int ArrayXiSize(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    // RETURNS THE SIZE FOR 1D ARRAY
    return arrayxi.innerSize();
}

// RETURNS THE NUMBER OF NON-NULL COEFFICIENTS
extern "C"
int ArrayXiNonZeros(ArrayType *array)
{

    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.count();
}

// RETURNS THE SMALLEST COEFFICIENT OF THE ARRAY
extern "C"
int ArrayXiMinCoeff(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.minCoeff();
}

// RETURNS THE LARGEST COEFFICIENT OF THE ARRAY
extern "C"
int ArrayXiMaxCoeff(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.maxCoeff();
}

// RETURNS THE SUM OF ALL ELEMENTS OF AN ARRAY
extern "C"
long ArrayXiSum(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.sum();
}

// RETURNS THE MEAN OF THE ARRAY
extern "C"
double ArrayXiMean(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.mean();
}

// RETURNS THE ABSOLUTE OF THE ARRAY
extern "C"
ArrayType *ArrayXiAbs(ArrayType *array)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(array);

    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi.abs(), size);
}

// RETURNS A BINARY VERSION OF THE ARRAY, I.E. ALL ELEMENTS > 0 WILL BE 1
extern "C"
ArrayType *ArrayXiBinary(ArrayType *array)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(array);

    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype((arrayxi > 0).cast<int>(), size);
}

// SUM TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiAdd(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 + arrayxi2, size);
}

// SUBTRACTS TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiSub(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 - arrayxi2, size);
}

// MULTIPLIES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiMul(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 * arrayxi2, size);
}

// DIVIDES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXiDiv(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 / arrayxi2, size);
}


////////////////////////////SCALAR ARITHMETIC///////////////////////////////////


// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXiAddScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi + scalar, size);
}

// SUBTRACT SCALAR FROM EVERY ELEMENT
extern "C"
ArrayType *ArrayXiSubScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi - scalar, size);
}

// MULTIPLY SCALAR WITH EVERY ELEMENT
extern "C"
ArrayType *ArrayXiMulScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi * scalar, size);
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
extern "C"
bool ArrayXiEqual(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);
    
    return (arrayxi1==arrayxi2).all();
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
extern "C"
bool ArrayXiContains(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return ((arrayxi1 > 0) == (arrayxi2 > 0)).count() == arrayxi2.count();
}

// RETURNS TRUE IF THE ARRAYS HAVE AT LEAST ONE NON-NULL ELEMENT IN COMMON
extern "C"
bool ArrayXiOverlaps(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return ((arrayxi1 > 0) == (arrayxi2 > 0)).any();
}

// RETURNS THE INTERSECTION BETWEEN THE ARRAYS
extern "C"
ArrayType *ArrayXiIntersection(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype((arrayxi1==arrayxi2).select(arrayxi1, 0), size);
}

// RETURNS THE UNION OF BOTH ARRAYS AS THE MAXIMUM OF COFFICIENTS
extern "C"
ArrayType *ArrayXiUnion(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // DEFINE UNION AS THE MAXIMUM OF BOTH ARRAYS: A(2,3,4), B(4,2,3) = C(4,3,4)
    return arrayxi_to_arraytype(arrayxi1.max(arrayxi2), size);
}

// RETURNS THE BINARY UNION OF BOTH ARRAYS
extern "C"
ArrayType *ArrayXiBinaryUnion(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    ArrayXi binary_union = (arrayxi1.max(arrayxi2) > 0).cast<int>();
    
    return arrayxi_to_arraytype(binary_union, size);
}


///////////////////////NORMALIZED SIMILARITY METRICS////////////////////////////


// RETURNS THE BRAY-CURTIS DISSIMILARITY
extern "C"
double ArrayXiBrayCurtis(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return 1.0 - ((arrayxi1-arrayxi2).abs().sum() / (double) (arrayxi1+arrayxi2).sum());
}

// RETURNS THE DICE SIMILARITY
extern "C"
double ArrayXiDice(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return 2 * c / (double) size;
}

// RETURNS THE KULCZYNSKI SIMILARITY
extern "C"
double ArrayXiKulczynski(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();
    
    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c * (A + B) / (double) (2 * A * B);
    
    return similarity;
}

// RETURNS THE NORMALIZED EUCLIDEAN SIMILARITY
extern "C"
double ArrayXiNormEuclidean(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return sqrt((A + B - 2 * c) / (double) size);
}

// RETURNS THE NORMALIZED MANHATTAN SIMILARITY
extern "C"
double ArrayXiNormManhattan(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return (A + B - 2 * c) / (double) size;
}

// RETURNS THE OCHIAI/COSINE SIMILARITY
extern "C"
double ArrayXiOchiai(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / sqrt(A*B);
    
    return similarity;
}

// RETURNS THE RUSSELL-RAO SIMILARITY
extern "C"
double ArrayXiRussellRao(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return c / (double) size;
}

// RETURNS THE SIMPSON SIMILARITY - FUZCAV DEFAULT SIMILARITY
extern "C"
double ArrayXiSimpson(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / (double) std::min(A,B);
    
    return similarity;
}

// RETURNS THE SIMPSON SIMILARITY WITH MAX() INSTEAD OF MIN()
extern "C"
double ArrayXiSimpsonGlobal(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) similarity = c / (double) std::max(A,B);
    
    return similarity;
}

// RETURNS THE TVERSKY SIMILARITY
extern "C"
double ArrayXiTversky(ArrayType *a1, ArrayType *a2)
{
    double similarity = 0.0;
    
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // SET COUNTS ON THE INDIVIDUAL ARRAYS
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    // AVOID DIVISION BY ZERO
    if (A != 0 && B != 0) 
    {
        similarity = c / (double) (arrayxi_tversky_alpha * A + 
                                  arrayxi_tversky_beta * B + 
                                  (1 - arrayxi_tversky_alpha + arrayxi_tversky_beta) * c);
    }
        
    return similarity;
}


////////////////////////////////DISTANCE METRICS////////////////////////////////


// RETURNS THE EUCLIDEAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayXiEuclideanDist(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return sqrt((arrayxi1-arrayxi2).square().sum());
}

// RETURNS THE MANHATTAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayXiManhattanDist(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return (arrayxi1-arrayxi2).abs().sum();
}

// RETURNS THE MEAN HAMMING DISTANCE
extern "C"
double ArrayXiMeanHammingDist(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // UNIQUE COUNTS IN BOTH ARRAYS
    unsigned int a = UNIQUE_LEFT_SIZE(arrayxi1,arrayxi2);
    unsigned int b = UNIQUE_RIGHT_SIZE(arrayxi1,arrayxi2);
    
    return (a + b) / (double) size;
}


/////////////////////FUZCAV-SPECIFIC SIMILARITY METRICS/////////////////////////


// RETURNS THE FUZCAV SIMILARITY
extern "C"
double ArrayXiFuzCavSimGlobal(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // COUNTS THAT ARE SHARED BETWEEN THE FUZCAV FINGERPRINTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

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
    
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);
    
    // QUERY ARRAY HAS TO BE CONVERTED TO BINARY VERSION TO BE COMPATIBLE WITH
    // THE GIST INTERNAL NODES
    unsigned int c = INTERSECT_SIZE(arrayxi1, (arrayxi2 > 0).cast<int>());
    unsigned int A = arrayxi1.count();
    unsigned int B = arrayxi2.count();
    
    // IN GIST CONTEXT, A1 IS KEY A2 IS QUERY

    if (strcmp(metric,"dice") == 0) 
    {
        upper_bound = 2 * c / (float) B;
    }
    
    else if (strcmp(metric,"euclidean") == 0) 
    {
        upper_bound = sqrt((B - 2 * c) / (float) size);
    }
    
    else if (strcmp(metric,"kulczynski") == 0) 
    {
        upper_bound = A + B / (float) (2 * std::max(A,B));
    }
    
    else if (strcmp(metric,"manhattan") == 0) 
    {
        upper_bound = (B - 2 * c) / (float) size;
    }
    
    else if (strcmp(metric,"ochiai") == 0) 
    {
        upper_bound = c / sqrt(B);
    }
    
    else if (strcmp(metric,"russell-rao") == 0) 
    {
        upper_bound = B / (float) size;
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