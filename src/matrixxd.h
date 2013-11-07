#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"

    ArrayType    *MatrixXdConstant(int rows, int cols, double value);
    ArrayType    *MatrixXdIdentity(int rows, int cols);
    ArrayType    *MatrixXdRandom(int rows, int cols);
    
    unsigned int  MatrixXdSize(ArrayType *array);
    bool          MatrixXdIsIdentity(ArrayType *array, double precision);
    
    ArrayType    *MatrixXdAdd(ArrayType *a1, ArrayType *a2);
    ArrayType    *MatrixXdSubtract(ArrayType *a1, ArrayType *a2);
    ArrayType    *MatrixXdMultiply(ArrayType *a1, ArrayType *a2);
    ArrayType    *MatrixXdScalarProduct(ArrayType *array, double scalar);
    ArrayType    *MatrixXdScalarDivision(ArrayType *array, double scalar);
    
    ArrayType    *MatrixXdColWiseSum(ArrayType *array);
    ArrayType    *MatrixXdColWiseMean(ArrayType *array);
    ArrayType    *MatrixXdRowWiseSum(ArrayType *array);
    ArrayType    *MatrixXdRowWiseMean(ArrayType *array);
    
    ArrayType    *MatrixXdHStack(ArrayType *a1, ArrayType *a2);
    ArrayType    *MatrixXdVStack(ArrayType *a1, ArrayType *a2);
    ArrayType    *MatrixXdHStackVector3d(ArrayType *matrix, ArrayType *vector);
    ArrayType    *MatrixXdVStackVector3d(ArrayType *matrix, ArrayType *vector);
    
#ifdef __cplusplus
}
#endif
