#include "arrayxi.h"
#include "fmgr.h"
#include <utils/builtins.h>
#include "matrixxd.h"


//////////////////////////MATRIX CONSTRUCTION METHODS///////////////////////////


// RETURNS MATRIX WITH ALL COEFFICIENTS SET TO THE GIVEN VALUE
PG_FUNCTION_INFO_V1(matrixxd_constant);
Datum matrixxd_constant(PG_FUNCTION_ARGS)
{
    int rows = PG_GETARG_INT32(0);
    int cols = PG_GETARG_INT32(1);
    double value = PG_GETARG_FLOAT8(2);
    
    PG_RETURN_ARRAYTYPE_P(MatrixXdConstant(rows, cols, value));
}

// RETURNS AN IDENTITY MATRIX OF THE GIVEN DIMENSIONS
PG_FUNCTION_INFO_V1(matrixxd_identity);
Datum matrixxd_identity(PG_FUNCTION_ARGS)
{
    int rows = PG_GETARG_INT32(0);
    int cols = PG_GETARG_INT32(1);
    
    PG_RETURN_ARRAYTYPE_P(MatrixXdIdentity(rows, cols));
}

// RETURNS MATRIX OF THE GIVEN DIMENSIONS WITH RANDOM COEFFICIENTS
PG_FUNCTION_INFO_V1(matrixxd_random);
Datum matrixxd_random(PG_FUNCTION_ARGS)
{
    int rows = PG_GETARG_INT32(0);
    int cols = PG_GETARG_INT32(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdRandom(rows, cols));
}


///////////////////////////////MATRIX PROPERTIES////////////////////////////////


// RETURNS TRUE IF THE GIVEN MATRIX IS APPROXIMATELY EQUAL TO THE IDENTITY MATRIX 
// (NOT NECESSARILY SQUARE), WITHIN THE GIVEN PRECISION
PG_FUNCTION_INFO_V1(matrixxd_is_identity);
Datum matrixxd_is_identity(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     precision = PG_GETARG_FLOAT8(1);

    PG_RETURN_BOOL(MatrixXdIsIdentity(array, precision));
}

// RETURNS THE NUMBER OF ELEMENTS IN THE ARRAY
PG_FUNCTION_INFO_V1(matrixxd_size);
Datum matrixxd_size(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_INT32(MatrixXdSize(array));
}


//////////////////////////////MATRIX ARITHMETIC/////////////////////////////////


// RETURNS THE SUM OF TWO MATRICES
PG_FUNCTION_INFO_V1(matrixxd_add);
Datum matrixxd_add(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdAdd(a1, a2));
}

// SUBTRACTS THE SECOND MATRIX FROM THE FIRST
PG_FUNCTION_INFO_V1(matrixxd_subtract);
Datum matrixxd_subtract(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdSubtract(a1, a2));
}

// SUBTRACTS THE SECOND MATRIX FROM THE FIRST
PG_FUNCTION_INFO_V1(matrixxd_multiply);
Datum matrixxd_multiply(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdMultiply(a1, a2));
}

// RETURNS THE SCALAR PRODUCT
PG_FUNCTION_INFO_V1(matrixxd_scalar_product);
Datum matrixxd_scalar_product(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdScalarProduct(array, scalar));
}

// RETURNS THE SCALAR DIVISION
PG_FUNCTION_INFO_V1(matrixxd_scalar_division);
Datum matrixxd_scalar_division(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);
    double     scalar = PG_GETARG_FLOAT8(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdScalarDivision(array, scalar));
}


////////////////////////COL-WISE OPERATIONS ON MATRICES/////////////////////////


// RETURNS THE COL-WISE MEAN OF THE MATRIX
PG_FUNCTION_INFO_V1(matrixxd_cw_mean);
Datum matrixxd_cw_mean(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(MatrixXdColWiseMean(array));
}


// RETURNS THE ROW-WISE SUM OF THE MATRIX
PG_FUNCTION_INFO_V1(matrixxd_cw_sum);
Datum matrixxd_cw_sum(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(MatrixXdColWiseSum(array));
}


////////////////////////ROW-WISE OPERATIONS ON MATRICES/////////////////////////


// RETURNS THE ROW-WISE MEAN OF THE MATRIX
PG_FUNCTION_INFO_V1(matrixxd_rw_mean);
Datum matrixxd_rw_mean(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(MatrixXdRowWiseMean(array));
}


// RETURNS THE ROW-WISE SUM OF THE MATRIX
PG_FUNCTION_INFO_V1(matrixxd_rw_sum);
Datum matrixxd_rw_sum(PG_FUNCTION_ARGS)
{
    ArrayType *array = PG_GETARG_ARRAYTYPE_P(0);

    PG_RETURN_ARRAYTYPE_P(MatrixXdRowWiseSum(array));
}


///////////////////////MATRICES AND OTHER EIGEN OBJECTS/////////////////////////


// HORIZONTALLY STACKS THE SECOND MATRIX ONTO THE FIRST
PG_FUNCTION_INFO_V1(matrixxd_hstack);
Datum matrixxd_hstack(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdHStack(a1, a2));
}

// VERTICALLY STACKS THE SECOND MATRIX ONTO THE FIRST
PG_FUNCTION_INFO_V1(matrixxd_vstack);
Datum matrixxd_vstack(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdVStack(a1, a2));
}

// HORIZONTALLY STACKS VECTOR3D ONTO MATRIX
PG_FUNCTION_INFO_V1(matrixxd_hstack_vector3d);
Datum matrixxd_hstack_vector3d(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdHStackVector3d(a1, a2));
}

// VERTICALLY STACKS VECTOR3D ONTO MATRIX
PG_FUNCTION_INFO_V1(matrixxd_vstack_vector3d);
Datum matrixxd_vstack_vector3d(PG_FUNCTION_ARGS)
{
    ArrayType *a1 = PG_GETARG_ARRAYTYPE_P(0);
    ArrayType *a2 = PG_GETARG_ARRAYTYPE_P(1);

    PG_RETURN_ARRAYTYPE_P(MatrixXdVStackVector3d(a1, a2));
}