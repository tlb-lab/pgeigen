#include <Eigen/Dense>
#include "arrayxd.h"
#include <iostream>

#define ARRINTDATA(array)   ((double *)ARR_DATA_PTR(array))
#define ARRNELEMS(x)        ArrayGetNItems( ARR_NDIM(x), ARR_DIMS(x))
#define ARREQSIZE(a,b)      if (a != b) ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), errmsg("arrays must have the same number of elements.")))

using namespace Eigen;

// CONSTRUCTS A POSTGRESQL ARRAY FROM AN EIGEN ARRAY
ArrayType *arrayxd_to_arraytype(const ArrayXd &arrayxd, int size)
{
    const double *data = arrayxd.data();
    Datum *d = (Datum *) palloc(sizeof(Datum) * size);

    for (int i = 0; i < size; i++) d[i] = Float8GetDatum(data[i]);

    // CONSTRUCT ARRAY
    return construct_array(d, size, FLOAT8OID, sizeof(float8), true, 'd');
}

// RETURNS THE NUMBER OF COEFFICIENTS IN ARRAY
extern "C"
int ArrayXdSize(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), ARRNELEMS(array));

    // RETURNS THE SIZE FOR 1D ARRAY
    return arrayxd.innerSize();
}

// RETURNS THE NUMBER OF NON-NULL COEFFICIENTS
extern "C"
int ArrayXdNonZeros(ArrayType *array)
{

    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxd.count();
}

// RETURNS THE SMALLEST COEFFICIENT OF THE ARRAY
extern "C"
double ArrayXdMinCoeff(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxd.minCoeff();
}

// RETURNS THE LARGEST COEFFICIENT OF THE ARRAY
extern "C"
double ArrayXdMaxCoeff(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxd.maxCoeff();
}

// RETURNS THE SUM OF ALL ELEMENTS OF AN ARRAY
extern "C"
double ArrayXdSum(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxd.sum();
}

// RETURNS THE MEAN OF THE ARRAY
extern "C"
double ArrayXdMean(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), ARRNELEMS(array));

    return arrayxd.mean();
}

// RETURNS THE ABSULATE OF THE ARRAY
extern "C"
ArrayType *ArrayXdAbs(ArrayType *array)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(array);

    // MAP POSTGRESQL ARRAY TO
    Map<ArrayXd> arrayxd(ARRINTDATA(array), size);

    return arrayxd_to_arraytype(arrayxd.abs(), size);
}

// SUM TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdAdd(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return arrayxd_to_arraytype(arrayxd1 + arrayxd2, size);
}

// SUBTRACTS TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdSub(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return arrayxd_to_arraytype(arrayxd1 - arrayxd2, size);
}

// MULTIPLIES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdMul(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return arrayxd_to_arraytype(arrayxd1 * arrayxd2, size);
}

// DIVIDES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdDiv(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return arrayxd_to_arraytype(arrayxd1 / arrayxd2, size);
}

/* SCALAR ARITHMETIC */

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXdAddScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd(ARRINTDATA(array), size);

    return arrayxd_to_arraytype(arrayxd + scalar, size);
}

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXdSubScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd(ARRINTDATA(array), size);

    return arrayxd_to_arraytype(arrayxd - scalar, size);
}

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXdMulScalar(ArrayType *array, int scalar)
{
    int size = ARRNELEMS(array);

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd(ARRINTDATA(array), size);

    return arrayxd_to_arraytype(arrayxd * scalar, size);
}

/* DISTANCE METRICS */

// RETURNS THE EUCLIDEAN DISTANCE BETWEEN THE ARRAYS
extern "C"
double ArrayXdEuclidean(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return sqrt((arrayxd1-arrayxd2).square().sum());
}

// RETURNS THE MANHATTAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayXdManhattan(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return (arrayxd1-arrayxd2).abs().sum();
}

// RETURNS THE WEIGHTED USR MANHATTAN DISTANCE BETWEEN THE TWO ARRAYS
extern "C"
double ArrayXdUSRSim(ArrayType *a1, ArrayType *a2)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    return (arrayxd1-arrayxd2).abs().sum() / 12.0;
}

// RETURNS THE WEIGHTED USR MANHATTAN DISTANCE BETWEEN THE TWO ARRAYS / USRCAT VERSION WITH 60 VALUES
extern "C"
double ArrayXdUSRCatSim(ArrayType *a1, ArrayType *a2, float ow, float hw, float rw, float aw, float dw)
{
    // GET NUMBER OF ELEMENTS IN FIRST ARRAY
    int size = ARRNELEMS(a1);

    ARREQSIZE(size, ARRNELEMS(a2));

    // MAP DATA TO EIGEN ARRAYS
    Map<ArrayXd> arrayxd1(ARRINTDATA(a1), size);
    Map<ArrayXd> arrayxd2(ARRINTDATA(a2), size);

    double weights = ow * (arrayxd1.segment(0,12) - arrayxd2.segment(0,12)).abs().sum() +
                     hw * (arrayxd1.segment(12,12) - arrayxd2.segment(12,12)).abs().sum() +
                     rw * (arrayxd1.segment(24,12) - arrayxd2.segment(24,12)).abs().sum() +
                     aw * (arrayxd1.segment(36,12) - arrayxd2.segment(36,12)).abs().sum() +
                     dw * (arrayxd1.segment(48,12) - arrayxd2.segment(48,12)).abs().sum();

    return  1.0 / (1.0 + weights);
}