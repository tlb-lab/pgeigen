#include "eigen.h"
#include "vector3d.h"

using namespace Eigen;

// CONVERTS A POSTGRESQL ARRAY INTO AN EIGEN VECTOR3D
RowVector3d arraytype_to_vector3d(ArrayType *array)
{
    // MAP POSTGRESQL ARRAY TO MATRIX
    Map<RowVector3d> vector3d((double *) ARR_DATA_PTR(array), 3);
    
    return vector3d;
}

// // HORIZONTALLY STACKS TWO MATRICES
// extern "C"
// ArrayType *matrixxd_to_vector3d(ArrayType *array)
// {
//     int *dmns = ARR_DIMS(array);
//     int *lbds = ARR_LBOUND(array);
//     
//     // EXTRACT THE MATRIX DIMENSIONS FROM THE POSTGRESQL ARRAYTYPE
//     int rows = arraytype_num_rows(dmns, lbds);
//     int cols = arraytype_num_cols(dmns, lbds);
//     
//     if (rows != 1 || cols != 3)
//     {
//         ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
//                         errmsg("cannot cast matrixxd to vector3d: incompatible matrix dimensions (%i,%i).", rows, cols)));
//     }
//     
//     return densebase_to_float8_arraytype(array);
// }


///////////////////////////VECTOR GENERATION METHODS////////////////////////////


// RETURNS VECTOR OF THE GIVEN SIZE WITH RANDOM COEFFICIENTS
extern "C"
ArrayType *Vector3dRandom()
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    RowVector3d vector3d = RowVector3d::Random();

    return densebase_to_float8_arraytype(vector3d);
}

// RETURNS VECTOR OF THE GIVEN SIZE WITH RANDOM COEFFICIENTS
extern "C"
ArrayType *Vector3dConstant(double value)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    RowVector3d vector3d = RowVector3d::Constant(value);

    return densebase_to_float8_arraytype(vector3d);
}

//////////////////////////////VECTOR ARITHMETIC/////////////////////////////////


//
extern "C"
ArrayType *Vector3dAdd(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return densebase_to_float8_arraytype(v1 + v2);
}

//
extern "C"
ArrayType *Vector3dSubtract(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return densebase_to_float8_arraytype(v1 - v2);
}

//
extern "C"
ArrayType *Vector3dScalarProduct(ArrayType *array, double scalar)
{
    RowVector3d vector3d = arraytype_to_vector3d(array);
    
    return densebase_to_float8_arraytype(vector3d * scalar);
}

//
extern "C"
ArrayType *Vector3dScalarDivision(ArrayType *array, double scalar)
{
    RowVector3d vector3d = arraytype_to_vector3d(array);
    
    return densebase_to_float8_arraytype(vector3d / scalar);
}

// RETURNS THE DOT PRODUCT
extern "C"
double Vector3dDot(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return v1.dot(v2);
}

// RETURNS THE CROSS PRODUCT
extern "C"
ArrayType *Vector3dCross(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return densebase_to_float8_arraytype(v1.cross(v2));
}

// RETURNS THE VECTOR NORM/LENGTH
extern "C"
double Vector3dNorm(ArrayType *array)
{
    RowVector3d vector3d = arraytype_to_vector3d(array);
    
    return vector3d.norm();
}

// RETURNS THE NORMALIZED VECTOR
extern "C"
ArrayType *Vector3dNormalized(ArrayType *array)
{
    RowVector3d vector3d = arraytype_to_vector3d(array);
    
    return densebase_to_float8_arraytype(vector3d.normalized());
}

// RETURNS THE DISTANCE BETWEEN TWO VECTORS
extern "C"
double Vector3dDistance(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return (v1-v2).norm();
}

// RETURNS THE ANGLE BETWEEN TWO VECTORS
extern "C"
double Vector3dAngle(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return acos(v1.dot(v2) / (v1.norm() * v2.norm()));
}

// RETURNS THE ABSOLUTE ANGLE BETWEEN TWO VECTORS
extern "C"
double Vector3dAbsAngle(ArrayType *a1, ArrayType *a2)
{
    RowVector3d v1 = arraytype_to_vector3d(a1);
    RowVector3d v2 = arraytype_to_vector3d(a2);
    
    return acos(fabs(v1.dot(v2) / (v1.norm() * v2.norm())));
}