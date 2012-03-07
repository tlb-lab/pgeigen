#include "eigen.h"
#include "arrayxd.h"

using namespace Eigen;

// CONVERTS A POSTGRESQL INTO AN EIGEN ARRAYXD
inline ArrayXd arraytype_to_arrayxd(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO EIGEN ARRAYXD
    Map<ArrayXd> arrayxd((double *) ARR_DATA_PTR(array), arraytype_num_elems(array));
    
    return arrayxd;
}

// RETURNS THE NUMBER OF COEFFICIENTS IN ARRAY
extern "C"
int ArrayXdSize(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    // RETURNS THE SIZE FOR 1D ARRAY
    return arrayxd.size();
}

// RETURNS THE NUMBER OF NON-NULL COEFFICIENTS
extern "C"
int ArrayXdNonZeros(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return arrayxd.count();
}

// RETURNS THE SMALLEST COEFFICIENT OF THE ARRAY
extern "C"
double ArrayXdMinCoeff(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return arrayxd.minCoeff();
}

// RETURNS THE LARGEST COEFFICIENT OF THE ARRAY
extern "C"
double ArrayXdMaxCoeff(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return arrayxd.maxCoeff();
}

// RETURNS THE SUM OF ALL ELEMENTS OF AN ARRAY
extern "C"
double ArrayXdSum(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return arrayxd.sum();
}

// RETURNS THE MEAN OF THE ARRAY
extern "C"
double ArrayXdMean(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return arrayxd.mean();
}

// RETURNS THE ABSOLUTE OF THE ARRAY
extern "C"
ArrayType *ArrayXdAbs(ArrayType *array)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return densebase_to_float8_arraytype(arrayxd.abs());
}

// SUM TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdAdd(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return densebase_to_float8_arraytype(arrayxd1 + arrayxd2);
}

// SUBTRACTS TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdSub(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return densebase_to_float8_arraytype(arrayxd1 - arrayxd2);
}

// MULTIPLIES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdMul(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return densebase_to_float8_arraytype(arrayxd1 * arrayxd2);
}

// DIVIDES TWO ARRAYS ELEMENTWISE
extern "C"
ArrayType *ArrayXdDiv(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return densebase_to_float8_arraytype(arrayxd1 / arrayxd2);
}

/* SCALAR ARITHMETIC */

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXdAddScalar(ArrayType *array, double scalar)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);
    
    return densebase_to_float8_arraytype(arrayxd + scalar);
}

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXdSubScalar(ArrayType *array, double scalar)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return densebase_to_float8_arraytype(arrayxd - scalar);
}

// ADD SCALAR TO EVERY ELEMENT
extern "C"
ArrayType *ArrayXdMulScalar(ArrayType *array, double scalar)
{
    ArrayXd arrayxd = arraytype_to_arrayxd(array);

    return densebase_to_float8_arraytype(arrayxd * scalar);
}

/* DISTANCE METRICS */

// RETURNS THE EUCLIDEAN DISTANCE BETWEEN THE ARRAYS
extern "C"
double ArrayXdEuclidean(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return sqrt((arrayxd1-arrayxd2).square().sum());
}

// RETURNS THE MANHATTAN DISTANCE BETWEEN BOTH ARRAYS
extern "C"
double ArrayXdManhattan(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return (arrayxd1-arrayxd2).abs().sum();
}

// RETURNS THE WEIGHTED USR MANHATTAN DISTANCE BETWEEN THE TWO ARRAYS
extern "C"
double ArrayXdUSRSim(ArrayType *a1, ArrayType *a2)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    return 1.0 / (1.0 + (arrayxd1-arrayxd2).abs().sum() / arrayxd1.size());
}

// RETURNS THE WEIGHTED USR MANHATTAN DISTANCE BETWEEN THE TWO ARRAYS / USRCAT VERSION WITH 60 VALUES
extern "C"
double ArrayXdUSRCatSim(ArrayType *a1, ArrayType *a2, float ow, float hw, float rw, float aw, float dw)
{
    // MAP DATA TO EIGEN ARRAYS
    ArrayXd arrayxd1 = arraytype_to_arrayxd(a1);
    ArrayXd arrayxd2 = arraytype_to_arrayxd(a2);

    // CHECK IF ARRAYS HAVE THE SAME NUMBER OF COEFFICIENTS
    EigenBaseEqSize(arrayxd1,arrayxd2);

    double weights = ow * (arrayxd1.segment(0,12) - arrayxd2.segment(0,12)).abs().sum() +
                     hw * (arrayxd1.segment(12,12) - arrayxd2.segment(12,12)).abs().sum() +
                     rw * (arrayxd1.segment(24,12) - arrayxd2.segment(24,12)).abs().sum() +
                     aw * (arrayxd1.segment(36,12) - arrayxd2.segment(36,12)).abs().sum() +
                     dw * (arrayxd1.segment(48,12) - arrayxd2.segment(48,12)).abs().sum();

    return  1.0 / (1.0 + weights / arrayxd1.size());
}