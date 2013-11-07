#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"
    #include "catalog/pg_type.h"

#ifdef __cplusplus
}
#endif

#include <eigen3/Eigen/Dense>

#define PG_ROW_DIM    1
#define PG_COL_DIM    2

using namespace Eigen;

// Arrays are stored in a RowMajor manner by PostgreSQL
typedef Matrix<double, Dynamic, Dynamic, RowMajor> MatrixRowMajorXd;

/////////////////////POSTGRESQL ARRAYTYPE FUNCTIONS/////////////////////////////


// RETURNS THE NUMBER OF ELEMENTS IN THE POSTGRESQL ARRAYTYPE
inline unsigned int arraytype_num_elems(ArrayType *array)
{
    return ArrayGetNItems(ARR_NDIM(array), ARR_DIMS(array));
}

// RETURNS TRUE IF THE POSTGRESQL ARRAYTYPE IS EMPTY
inline bool arraytype_is_empty(ArrayType *array)
{
    return arraytype_num_elems(array) == 0;
}

// RETURNS THE NUMBER OF ROWS IN THE POSTGRESQL ARRAYTYPE
inline int arraytype_num_rows(int *dmns, int *lbds)
{
    return dmns[PG_ROW_DIM - 1] + lbds[PG_ROW_DIM - 1] - 1;
}

// RETURNS THE NUMBER OF COLUMNS IN THE POSTGRESQL ARRAYTYPE
inline int arraytype_dim_num_elems(int dim, int *dmns, int *lbds)
{
    return dmns[dim - 1] + lbds[dim - 1] - 1;
}

// CHECKS IF EIGEN OBJECTS HAVE THE SAME NUMBER OF COEFFICIENTS
template<typename Derived1, typename Derived2>
inline void EigenBaseEqSize(const DenseBase<Derived1>& d1, const DenseBase<Derived2>& d2)
{
    if (d1.size() != d2.size()) 
    {
        ereport(ERROR, (errcode(ERRCODE_DATA_EXCEPTION), 
                        errmsg("eigen objects must have the same number of coefficients.")));
    }
}

// CONSTRUCTS A POSTGRESQL ARRAY FROM AN EIGEN DENSEBASE
template<typename Derived>
ArrayType *densebase_to_float8_arraytype(const DenseBase<Derived> &densebase)
{
    // NUMBER OF DIMENSIONS: IF MORE THAN ONE COLUMN THAN 2
    int ndims = densebase.rows() > 1 ? 2 : 1;
    
    // LOWER AND UPPER BOUNDS OF DIMENSIONS
    int lbs[ndims], dims[ndims];
    
    // LOWER BOUNDS ALWAYS START AT ONE
    std::fill_n(lbs, ndims, 1);
    
    // SET THE UPPER BOUNDS OF THE ARRAY DIMENSIONS
    if (ndims==1) dims[0] = densebase.size();

    else
    {
        dims[0] = densebase.rows();
        dims[1] = densebase.cols();
    }
    
    Datum *datums = (Datum *) palloc(sizeof(Datum) * densebase.size());
    
    // THE STORAGE ORDER OF EIGEN OBJECTS DOES NOT NECESSARILY CORRESPOND
    // TO THE ACTUAL ORDER OF COEFFICIENTS
    for (int row = 0; row < densebase.rows(); row++)
    {
        for (int col = 0; col < densebase.cols(); col++) 
        {
            datums[row*densebase.cols() + col] = Float8GetDatum(densebase(row,col));
        }
    }
    
    return construct_md_array(datums, NULL, ndims, dims, lbs, FLOAT8OID, 8, true, 'd');
}

// CONSTRUCTS A POSTGRESQL ARRAY FROM AN EIGEN DENSEBASE
template<typename Derived>
ArrayType *densebase_to_int32_arraytype(const DenseBase<Derived> &densebase)
{
    // NUMBER OF DIMENSIONS: IF MORE THAN ONE COLUMN THAN 2
    int ndims = densebase.rows() > 1 ? 1 : 2;
    
    // LOWER AND UPPER BOUNDS OF DIMENSIONS
    int lbs[ndims], dims[ndims];
    
    // LOWER BOUNDS ALWAYS START AT ONE
    std::fill_n(lbs, ndims, 1); // memset(lbs, 1, ndims);
    
    // SET THE UPPER BOUNDS OF THE ARRAY DIMENSIONS
    if (ndims==1) dims[0] = densebase.size();

    else
    {
        dims[0] = densebase.rows();
        dims[1] = densebase.cols();
    }

    Datum *datums = (Datum *) palloc(sizeof(Datum) * densebase.size());
    
    // THE STORAGE ORDER OF EIGEN OBJECTS DOES NOT NECESSARILY CORRESPOND
    // TO THE ACTUAL ORDER OF COEFFICIENTS
    for (int row = 0; row < densebase.rows(); row++)
    {
        for (int col = 0; col < densebase.cols(); col++) 
        {
            datums[row*densebase.cols() + col] = Int32GetDatum(densebase(row,col));
        }
    }
    
    return construct_md_array(datums, NULL, ndims, dims, lbs, INT4OID, 4, true, 'i');
}