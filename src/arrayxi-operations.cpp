#include <Eigen/Dense>
#include "arrayxi.h"

#define ARRINTDATA(array)   ((int *)ARR_DATA_PTR(array))
#define ARRNELEMS(x)        ArrayGetNItems( ARR_NDIM(x), ARR_DIMS(x))
#define ARREQSIZE(a,b)      if (a != b) ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), errmsg("arrays must have the same number of elements.")))
#define INTERSECT_SIZE(a,b) (a==b).select(a, 0).count();

// CONSTRUCTS A POSTGRESQL ARRAY FROM AN EIGEN OBJECTS
ArrayType *arrayxi_to_arraytype(const Eigen::ArrayXi &arrayxi, int size)
{
    const int *data = arrayxi.data();
    Datum *d = (Datum *) palloc(sizeof(Datum) * size);

    for (int i = 0; i < size; i++) d[i] = Int32GetDatum(data[i]);

    // CONSTRUCT ARRAY
    return construct_array(d, size, INT4OID, sizeof(int4), true, 'i');
}

// RETURNS ARRAY WITH GIVEN CONSTANT VALUE
extern "C"
ArrayType *ArrayxiConstant(int size, int value)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    Eigen::ArrayXi arrayxi(size);

    // SET ALL ELEMENTS TO RANDOM
    arrayxi.setConstant(value);

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS ARRAY WITH RANDON ELEMENTS
extern "C"
ArrayType *ArrayxiRandom(int size)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    Eigen::ArrayXi arrayxi(size);

    // SET ALL ELEMENTS TO RANDOM
    arrayxi.setRandom();

    return arrayxi_to_arraytype(arrayxi, size);
}

// RETURNS THE NUMBER OF COEFFICIENTS
extern "C"
int ArrayxiSize(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    // RETURNS THE SIZE FOR 1D ARRAY
    return arrayxi.innerSize();
}

// RETURNS THE NUMBER OF NON-NULL COEFFICIENTS
extern "C"
int ArrayxiNonZeros(ArrayType *array)
{

    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.count();
}

// RETURNS THE SMALLEST COEFFICIENT OF THE ARRAY
extern "C"
int ArrayxiMinCoeff(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.minCoeff();
}

// RETURNS THE LARGEST COEFFICIENT OF THE ARRAY
extern "C"
int ArrayxiMaxCoeff(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.maxCoeff();
}

// RETURNS THE SUM OF ALL ELEMENTS OF AN ARRAY
extern "C"
long ArrayxiSum(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.sum();
}

// RETURNS THE MEAN OF THE ARRAY
extern "C"
double ArrayxiMean(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxi.mean();
}

// RETURNS THE ABSULATE OF THE ARRAY
extern "C"
ArrayType *ArrayxiAbs(ArrayType *array)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(array);

    // MAP POSTGRESQL ARRAY TO
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi.abs(), size);
}

// SUM TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayxiAdd(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 + arrayxi2, size);
}

// SUBTRACTS TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayxiSub(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 - arrayxi2, size);
}

// MULTIPLIES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayxiMul(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 * arrayxi2, size);
}

// DIVIDES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayxiDiv(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype(arrayxi1 / arrayxi2, size);
}

/* SCALAR ARITHMETIC */

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayxiAddScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi + scalar, size);
}

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayxiSubScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi - scalar, size);
}

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayxiMulScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi(ARRINTDATA(array), size);

    return arrayxi_to_arraytype(arrayxi * scalar, size);
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
extern "C"
bool ArrayxiContains(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return (arrayxi1==arrayxi2).count() == arrayxi2.count();
}

// RETURNS TRUE IF THE ARRAYS HAVE AT LEAST ONE NON-NULL ELEMENT IN COMMON
extern "C"
bool ArrayxiOverlaps(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return (arrayxi1==arrayxi2).any();
}

// RETURNS TRUE IF THE FIRST ARRAY CONTAINS ALL ELEMENTS OF THE SECOND
extern "C"
ArrayType *ArrayxiIntersection(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return arrayxi_to_arraytype((arrayxi1==arrayxi2).select(arrayxi1, 0), size);
}

// RETURNS THE UNION OF BOTH ARRAYS
extern "C"
ArrayType *ArrayxiUnion(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // DEFINE UNION AS THE MAXIMUM OF BOTH ARRAYS: A(2,3,4), B(4,2,3) = C(4,3,4)
    return arrayxi_to_arraytype(arrayxi1.max(arrayxi2), size);
}

/* DISTANCE METRICS */

// RETURNS THE MANHATTAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayxiManhattan(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return (arrayxi1-arrayxi2).abs().sum();
}

// RETURNS THE EUCLIDEAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayxiEuclidean(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return sqrt((arrayxi1-arrayxi2).square().sum());
}

// RETURNS THE OCHIAI SIMILARITY
extern "C"
double ArrayxiOchiai(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // UNIQUE COUNTS OF THE ARRAYS
    unsigned int a = (arrayxi1!=arrayxi2).select(arrayxi1, 0).count();
    unsigned int b = (arrayxi1!=arrayxi2).select(arrayxi2, 0).count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return c / sqrt((a+c)*(b+c));
}

// RETURNS THE KULCZYNSKI SIMILARITY
extern "C"
double ArrayxiKulczynski(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // UNIQUE COUNTS OF THE ARRAYS
    double a = (arrayxi1!=arrayxi2).select(arrayxi1, 0).count();
    double b = (arrayxi1!=arrayxi2).select(arrayxi2, 0).count();

    // COMMON COUNTS
    unsigned int c = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return 0.5 * (c/(a+c) + c/(b+c));
}


// RETURNS THE BRAY-CURTIS DISSIMILARITY
extern "C"
double ArrayxiBrayCurtis(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    return 1.0 - ((arrayxi1-arrayxi2).abs().sum() / (arrayxi1+arrayxi2).sum());
}


// RETURNS THE FUZCAV SIMILARITY
extern "C"
double ArrayxiFuzCavSim(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // COUNTS THAT ARE SHARED BETWEEN THE FUZCAV FINGERPRINTS
    double common_counts = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return (common_counts / std::min(arrayxi1.count(), arrayxi2.count()));
}

// RETURNS THE FUZCAV SIMILARITY
extern "C"
double ArrayxiFuzCavSimGlobal(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Eigen::Map<Eigen::ArrayXi> arrayxi1(ARRINTDATA(a1), size);
    Eigen::Map<Eigen::ArrayXi> arrayxi2(ARRINTDATA(a2), size);

    // COUNTS THAT ARE SHARED BETWEEN THE FUZCAV FINGERPRINTS
    double common_counts = INTERSECT_SIZE(arrayxi1,arrayxi2);

    return (common_counts / std::max(arrayxi1.count(), arrayxi2.count()));
}