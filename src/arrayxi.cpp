#include <Eigen/Dense>
#include "arrayxi.h"

#define ARRINTDATA(array)   ((int *)ARR_DATA_PTR(array))
#define ARRNELEMS(x)        ArrayGetNItems( ARR_NDIM(x), ARR_DIMS(x))
#define ARREQSIZE(a,b)      if (a != b) ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), errmsg("arrays must have the same number of elements.")))
#define INTERSECT_SIZE(a,b) (a==b).select(a, 0).count();

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
ArrayType *ArrayXiConstant(int size, int value)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi(size);

    // SET ALL ELEMENTS TO RANDOM
    arrayxi.setConstant(value);

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS ARRAY WITH RANDON ELEMENTS
extern "C"
ArrayType *ArrayXiRandom(int size)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    ArrayXi arrayxi = ArrayXi::Random(size);

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

/* SCALAR ARITHMETIC */

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
bool ArrayXiContains(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Map<ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return (arrayxi1==arrayxi2).count() == arrayxi2.count();
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

    return (arrayxi1==arrayxi2).any();
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
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

    return 1.0 - ((arrayxi1-arrayxi2).abs().sum() / (float) (arrayxi1+arrayxi2).sum());
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

    return 2 * c / (float) size;
}

// RETURNS THE KULCZYNSKI SIMILARITY
extern "C"
double ArrayXiKulczynski(ArrayType *a1, ArrayType *a2)
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

    return c * (A + B) / (float) (2 * A * B);
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

    return sqrt((A + B - 2 * c) / (float) size);
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

    return (A + B - 2 * c) / (float) size;
}

// RETURNS THE OCHIAI/COSINE SIMILARITY
extern "C"
double ArrayXiOchiai(ArrayType *a1, ArrayType *a2)
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

    return c / sqrt(A*B);
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

    return c / (float) size;
}

// RETURNS THE SIMPSON SIMILARITY - FUZCAV DEFAULT SIMILARITY
extern "C"
double ArrayXiSimpson(ArrayType *a1, ArrayType *a2)
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

    return c / (float) std::min(A,B);
}

// RETURNS THE TVERSKY SIMILARITY
extern "C"
double ArrayXiTversky(ArrayType *a1, ArrayType *a2)
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

    return c / (float) arrayxi_tversky_alpha * A + arrayxi_tversky_beta * B + (1 - arrayxi_tversky_alpha + arrayxi_tversky_beta) * c;
}


//////////////////////////NORMAL DISTANCE METRICS///////////////////////////////


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
    double common_counts = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return (common_counts / std::max(arrayxi1.count(), arrayxi2.count()));
}