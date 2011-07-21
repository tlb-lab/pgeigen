#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"
    #include "catalog/pg_type.h"

    // ARRAY PROPERTIES
    int        ArrayxiSize(ArrayType *array);
    int        ArrayxiNonZeros(ArrayType *array);
    int        ArrayxiMinCoeff(ArrayType *array);
    int        ArrayxiMinCoeff(ArrayType *array);
    long       ArrayxiSum(ArrayType *array);
    double     ArrayxiMean(ArrayType *array);
    ArrayType *ArrayxiAbs(ArrayType *array);

    // ARRAYXI ARITHMETIC
    ArrayType *ArrayxiAdd(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxiSub(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxiMul(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxiDiv(ArrayType *a1, ArrayType *a2);

    ArrayType *ArrayxiAddScalar(ArrayType *array, int scalar);
    ArrayType *ArrayxiSubScalar(ArrayType *array, int scalar);
    ArrayType *ArrayxiMulScalar(ArrayType *array, int scalar);

    // ARRAY CREATION
    ArrayType *ArrayxiRandom(int size);
    ArrayType *ArrayxiConstant(int size, int value);

    // SET ALGEBRA
    bool       ArrayxiContains(ArrayType *a1, ArrayType *a2);
    bool       ArrayxiOverlaps(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxiIntersection(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayxiUnion(ArrayType *a1, ArrayType *a2);

    // DISTANCE METRICS
    double     ArrayxiEuclidean(ArrayType *a1, ArrayType *a2);
    double     ArrayxiManhattan(ArrayType *a1, ArrayType *a2);
    double     ArrayxiKulczynski(ArrayType *a1, ArrayType *a2);
    double     ArrayxiBrayCurtis(ArrayType *a1, ArrayType *a2);
    double     ArrayxiFuzCavSim(ArrayType *a1, ArrayType *a2);
    double     ArrayxiFuzCavSimGlobal(ArrayType *a1, ArrayType *a2);

#ifdef __cplusplus
}
#endif
