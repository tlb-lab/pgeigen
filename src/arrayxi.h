#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"
    #include "catalog/pg_type.h"

    #define PG_GETARG_TEXT_AS_CSTRING(x)    (text_to_cstring(PG_GETARG_TEXT_PP(x)))

    extern float4 arrayxi_tversky_alpha;
    extern float4 arrayxi_tversky_beta;
    
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

    // NORMALIZED SIMILARITY METRICS
    double     ArrayxiBrayCurtis(ArrayType *a1, ArrayType *a2);
    double     ArrayxiDice(ArrayType *a1, ArrayType *a2);
    double     ArrayxiKulczynski(ArrayType *a1, ArrayType *a2);
    double     ArrayxiNormEuclidean(ArrayType *a1, ArrayType *a2);
    double     ArrayxiNormManhattan(ArrayType *a1, ArrayType *a2);
    double     ArrayxiOchiai(ArrayType *a1, ArrayType *a2);
    double     ArrayxiRussellRao(ArrayType *a1, ArrayType *a2);
    double     ArrayxiSimpson(ArrayType *a1, ArrayType *a2);
    double     ArrayxiTversky(ArrayType *a1, ArrayType *a2);
    
    // FUZCAV METRIC
    double     ArrayxiFuzCavSimGlobal(ArrayType *a1, ArrayType *a2);
    
    // DISTANCE METRICS
    double     ArrayxiEuclideanDist(ArrayType *a1, ArrayType *a2);
    double     ArrayxiManhattanDist(ArrayType *a1, ArrayType *a2);
    

#ifdef __cplusplus
}
#endif
