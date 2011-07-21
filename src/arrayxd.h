#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"
    #include "catalog/pg_type.h"

    // ARRAY PROPERTIES
    int        ArrayxdSize(ArrayType *array);
    int        ArrayxdNonZeros(ArrayType *array);
    double     ArrayxdMinCoeff(ArrayType *array);
    double     ArrayxdMinCoeff(ArrayType *array);
    double     ArrayxdSum(ArrayType *array);
    double     ArrayxdMean(ArrayType *array);
    ArrayType *ArrayxdAbs(ArrayType *array);

    // ARRAY ARITHMETIC
    ArrayType *ArrayxdAdd(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxdSub(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxdMul(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxdDiv(ArrayType *a1, ArrayType *a2);

    ArrayType *ArrayxdAddScalar(ArrayType *array, int scalar);
    ArrayType *ArrayxdSubScalar(ArrayType *array, int scalar);
    ArrayType *ArrayxdMulScalar(ArrayType *array, int scalar);

    // ARRAY CREATION
    ArrayType *ArrayxdRandom(int size);
    ArrayType *ArrayxdConstant(int size, int value);

    // DISTANCE METRICS
    double     ArrayxdEuclidean(ArrayType *a1, ArrayType *a2);
    double     ArrayxdManhattan(ArrayType *a1, ArrayType *a2);
    double     ArrayxdUSRSim(ArrayType *a1, ArrayType *a2);
    double     ArrayxdUSRCatSim(ArrayType *a1, ArrayType *a2, float ow, float hw, float rw, float aw, float dw);

#ifdef __cplusplus
}
#endif