#include "eigen.h"
#include "hvstack.h"
#include "matrixxd.h"

#include <iostream>

using namespace Eigen;

// CONVERTS A POSTGRESQL ARRAYTYPE INTO AN EIGEN MATRIX OF DOUBLES
MatrixXd arraytype_to_matrixxd(ArrayType *array)
{
    MatrixXd matrixxd;
    
    // CHECK IF ARRAY IS NOT EMPTY
    if (!arraytype_is_empty(array))
    {
        int rows, cols;
        
        int *dmns = ARR_DIMS(array);
        int *lbds = ARR_LBOUND(array);

        if (ARR_NDIM(array) == 1)
        {
            rows = 1;
            cols = arraytype_dim_num_elems(1, dmns, lbds);
        }
        
        else
        {
            // EXTRACT THE MATRIX DIMENSIONS FROM THE POSTGRESQL ARRAYTYPE
            rows = arraytype_dim_num_elems(1, dmns, lbds); 
            cols = arraytype_dim_num_elems(2, dmns, lbds); 
        }
        
        ereport(NOTICE, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("rows: %i cols: %i.", rows, cols)));
        
        // MAP POSTGRESQL ARRAY TO MATRIX
        Map<MatrixXd> matrixxd((double *) ARR_DATA_PTR(array), rows, cols);
        
        return matrixxd;
    }
  
    return matrixxd;
}


/////////////////////////MATRIX CONSTRUCTION METHODS////////////////////////////


// RETURNS MATRIX WITH GIVEN CONSTANT VALUES
extern "C"
ArrayType *MatrixXdConstant(int rows, int cols, double value)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    MatrixXd matrixxd = MatrixXd::Constant(rows, cols, value);

    return densebase_to_float8_arraytype(matrixxd);
}

//
extern "C"
ArrayType *MatrixXdIdentity(int rows, int cols)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    MatrixXd matrixxd = MatrixXd::Identity(rows, cols);

    return densebase_to_float8_arraytype(matrixxd);
}

// RETURNS MATRIX WITH RANDOM COEFFICIENTS
extern "C"
ArrayType *MatrixXdRandom(int rows, int cols)
{
    // INITIALIZE ARRAY ACCORDING TO THE GIVEN SIZE
    MatrixXd matrixxd = MatrixXd::Random(rows, cols);

    return densebase_to_float8_arraytype(matrixxd);
}


//////////////////////////////MATRIX PROPERTIES/////////////////////////////////


// RETURNS THE NUMBER OF COEFFICIENTS IN MATRIX
extern "C"
unsigned int MatrixXdSize(ArrayType *array)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);

    // RETURNS THE TOTAL NUMBER OF COEFFICIENTS
    return matrixxd.size();
}

// RETURNS TRUE IF THE GIVEN MATRIX IS APPROXIMATELY EQUAL TO THE IDENTITY MATRIX 
// (NOT NECESSARILY SQUARE), WITHIN THE GIVEN PRECISION
extern "C"
bool MatrixXdIsIdentity(ArrayType *array, double precision)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return matrixxd.isIdentity(precision);
}


//////////////////////////////MATRIX ARITHMETIC/////////////////////////////////


// RETURNS THE SUM OF TWO MATRICES
extern "C"
ArrayType *MatrixXdAdd(ArrayType *a1, ArrayType *a2)
{
    MatrixXd m1 = arraytype_to_matrixxd(a1);
    MatrixXd m2 = arraytype_to_matrixxd(a2);
    
    return densebase_to_float8_arraytype(m1 + m2);
}

// SUBTRACTS THE SECOND MATRIX FROM THE FIRST
extern "C"
ArrayType *MatrixXdSubtract(ArrayType *a1, ArrayType *a2)
{
    MatrixXd m1 = arraytype_to_matrixxd(a1);
    MatrixXd m2 = arraytype_to_matrixxd(a2);
    
    return densebase_to_float8_arraytype(m1 - m2);
}

// MATRIX MULTIPLICATION
extern "C"
ArrayType *MatrixXdMultiply(ArrayType *a1, ArrayType *a2)
{
    MatrixXd m1 = arraytype_to_matrixxd(a1);
    MatrixXd m2 = arraytype_to_matrixxd(a2);
    
    return densebase_to_float8_arraytype(m1 * m2);
}

// RETURNS THE SCALAR PRODUCT
extern "C"
ArrayType *MatrixXdScalarProduct(ArrayType *array, double scalar)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return densebase_to_float8_arraytype(matrixxd * scalar);
}

// RETURNS THE SCALAR DIVISION
extern "C"
ArrayType *MatrixXdScalarDivision(ArrayType *array, double scalar)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return densebase_to_float8_arraytype(matrixxd / scalar);
}


///////////////////////COLUMN-WISE OPERATIONS ON MATRICES///////////////////////


// RETURNS THE COLUMN-WISE SUM
extern "C"
ArrayType *MatrixXdColWiseSum(ArrayType *array)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return densebase_to_float8_arraytype(matrixxd.colwise().sum());
}

// RETURNS THE COLUMN-WISE MEAN
extern "C"
ArrayType *MatrixXdColWiseMean(ArrayType *array)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return densebase_to_float8_arraytype(matrixxd.colwise().mean());
}


////////////////////////ROW-WISE OPERATIONS ON MATRICES/////////////////////////


// RETURNS THE ROW-WISE SUM
extern "C"
ArrayType *MatrixXdRowWiseSum(ArrayType *array)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return densebase_to_float8_arraytype(matrixxd.rowwise().sum());
}

// RETURNS THE ROW-WISE SUM
extern "C"
ArrayType *MatrixXdRowWiseMean(ArrayType *array)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(array);
    
    return densebase_to_float8_arraytype(matrixxd.rowwise().mean());
}


///////////////////////MATRICES AND OTHER EIGEN OBJECTS/////////////////////////


// HORIZONTALLY STACKS TWO MATRICES
extern "C"
ArrayType *MatrixXdHStack(ArrayType *a1, ArrayType *a2)
{
    MatrixXd m1 = arraytype_to_matrixxd(a1);
    MatrixXd m2 = arraytype_to_matrixxd(a2);

    // RETURN THE OTHER MATRIX IF ONE OF THEM IS EMPTY
    if (m1.size() == 0) return a2;
    else if (m2.size() == 0) return a1;
    
    if (m1.rows() != m2.rows())
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("cannot hstack matrixxd: matrices must have the same number of rows.")));
    }
    
    return densebase_to_float8_arraytype(HStack(m1,m2));
}

// VERTICAL STACKS TWO MATRICES
extern "C"
ArrayType *MatrixXdVStack(ArrayType *a1, ArrayType *a2)
{
    MatrixXd m1 = arraytype_to_matrixxd(a1);
    MatrixXd m2 = arraytype_to_matrixxd(a2);
    
    MatrixXd m3;
    m3.resize(m1.rows() + m2.rows(), m1.cols());
    
    std::cout << m3.rows() << "x" << m3.cols() << std::endl;
    
    m3 << m1, m2;
    
    // RETURN THE OTHER MATRIX IF ONE OF THEM IS EMPTY
    if (m1.size() == 0) return a2;
    else if (m2.size() == 0) return a1;
    
    else if (m1.cols() != m2.cols())
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("cannot vstack matrixxd: matrices must have the same number of columns.")));
    }
    
    return densebase_to_float8_arraytype(VStack(m1,m2));
}

// HORIZONTALLY STACKS A VECTOR3D ONTO A MATRIX
extern "C"
ArrayType *MatrixXdHStackVector3d(ArrayType *matrix, ArrayType *vector)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(matrix);
    Map<RowVector3d> vector3d((double *) ARR_DATA_PTR(vector), 3);

    // RETURN THE OTHER TYPE IF ONE OF THEM IS EMPTY
    if (matrixxd.size() == 0) return densebase_to_float8_arraytype(vector3d);
    else if (vector3d.size() == 0) return densebase_to_float8_arraytype(matrixxd);
    
    // ROW VECTOR!
    if (matrixxd.rows() > 1)
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("cannot hstack vector3d: matrix must not have more than one row.")));
    }
    
    return densebase_to_float8_arraytype(HStack(matrixxd,vector3d));
}

// VERTICALLY STACKS A VECTOR3D ONTO A MATRIX
extern "C"
ArrayType *MatrixXdVStackVector3d(ArrayType *matrix, ArrayType *vector)
{
    MatrixXd matrixxd = arraytype_to_matrixxd(matrix);
    Map<RowVector3d> vector3d((double *) ARR_DATA_PTR(vector), 3);

    // RETURN THE OTHER TYPE IF ONE OF THEM IS EMPTY
    if (matrixxd.size() == 0) return vector;
    else if (vector3d.size() == 0) return matrix;
    
    else if (matrixxd.cols() > 3)
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("cannot vstack vector3d: matrix must not have more than three columns.")));
    }
    
    return densebase_to_float8_arraytype(VStack(matrixxd,vector3d));
}
