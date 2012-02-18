#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"
    #include "catalog/pg_type.h"

    // ARRAY PROPERTIES
    int        ArrayXdSize(ArrayType *array);
    int        ArrayXdNonZeros(ArrayType *array);
    double     ArrayXdMinCoeff(ArrayType *array);
    double     ArrayXdMinCoeff(ArrayType *array);
    double     ArrayXdSum(ArrayType *array);
    double     ArrayXdMean(ArrayType *array);
    ArrayType *ArrayXdAbs(ArrayType *array);

    // ARRAY ARITHMETIC
    ArrayType *ArrayXdAdd(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXdSub(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXdMul(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXdDiv(ArrayType *a1, ArrayType *a2);

    ArrayType *ArrayXdAddScalar(ArrayType *array, double scalar);
    ArrayType *ArrayXdSubScalar(ArrayType *array, double scalar);
    ArrayType *ArrayXdMulScalar(ArrayType *array, double scalar);

    // ARRAY CREATION
    ArrayType *ArrayXdRandom(int size);
    ArrayType *ArrayXdConstant(int size, int value);

    // DISTANCE METRICS
    double     ArrayXdEuclidean(ArrayType *a1, ArrayType *a2);
    double     ArrayXdManhattan(ArrayType *a1, ArrayType *a2);
    double     ArrayXdUSRSim(ArrayType *a1, ArrayType *a2);
    double     ArrayXdUSRCatSim(ArrayType *a1, ArrayType *a2, float ow, float hw, float rw, float aw, float dw);

#ifdef __cplusplus
}
#endif