#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"

    #define PG_GETARG_TEXT_AS_CSTRING(x)    (text_to_cstring(PG_GETARG_TEXT_PP(x)))
    
    // ARRAYXI SIMILARITY METRICS DEFAULT VALUES
    extern float4 arrayxi_dice_limit;
    extern float4 arrayxi_euclidean_limit;
    extern float4 arrayxi_kulcz_limit;
    extern float4 arrayxi_manhattan_limit;
    extern float4 arrayxi_ochiai_limit;
    extern float4 arrayxi_russell_rao_limit;
    extern float4 arrayxi_simpson_limit;
    extern float4 arrayxi_tversky_limit;
    extern float4 arrayxi_tversky_alpha;
    extern float4 arrayxi_tversky_beta;
    
    // ARRAY PROPERTIES
    int        ArrayXiSize(ArrayType *array);
    int        ArrayXiNonZeros(ArrayType *array);
    int        ArrayXiMinCoeff(ArrayType *array);
    int        ArrayXiMinCoeff(ArrayType *array);
    long       ArrayXiSum(ArrayType *array);
    double     ArrayXiMean(ArrayType *array);
    ArrayType *ArrayXiAbs(ArrayType *array);
    ArrayType *ArrayXiBinary(ArrayType *array);

    // ARRAYXI ARITHMETIC
    ArrayType *ArrayXiAdd(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXiSub(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXiMul(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXiDiv(ArrayType *a1, ArrayType *a2);

    ArrayType *ArrayXiAddScalar(ArrayType *array, int scalar);
    ArrayType *ArrayXiSubScalar(ArrayType *array, int scalar);
    ArrayType *ArrayXiMulScalar(ArrayType *array, int scalar);

    // ARRAY CREATION
    ArrayType *ArrayXiCopy(ArrayType *array);
    ArrayType *ArrayXiRandom(int size);
    ArrayType *ArrayXiConstant(int size, int value);
    ArrayType *ArrayXiLinSpaced(int size, int low, int high);

    // SET ALGEBRA
    bool       ArrayXiEqual(ArrayType *a1, ArrayType *a2);
    bool       ArrayXiContains(ArrayType *a1, ArrayType *a2);
    bool       ArrayXiOverlaps(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXiIntersection(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXiUnion(ArrayType *a1, ArrayType *a2);
    ArrayType *ArrayXiBinaryUnion(ArrayType *a1, ArrayType *a2);

    // NORMALIZED SIMILARITY METRICS
    double     ArrayXiBrayCurtis(ArrayType *a1, ArrayType *a2);
    double     ArrayXiDice(ArrayType *a1, ArrayType *a2);
    double     ArrayXiKulczynski(ArrayType *a1, ArrayType *a2);
    double     ArrayXiNormEuclidean(ArrayType *a1, ArrayType *a2);
    double     ArrayXiNormManhattan(ArrayType *a1, ArrayType *a2);
    double     ArrayXiOchiai(ArrayType *a1, ArrayType *a2);
    double     ArrayXiRussellRao(ArrayType *a1, ArrayType *a2);
    double     ArrayXiSimpson(ArrayType *a1, ArrayType *a2);
    double     ArrayXiSimpsonGlobal(ArrayType *a1, ArrayType *a2);
    double     ArrayXiTanimoto(ArrayType *a1, ArrayType *a2);
    double     ArrayXiTversky(ArrayType *a1, ArrayType *a2);

    float      SimilarityUpperBound(ArrayType *a1, ArrayType *a2, char *metric);
    
    // FUZCAV METRIC
    double     ArrayXiFuzCavSimGlobal(ArrayType *a1, ArrayType *a2);

    // QUANTITATIVE / NON-BINARY METRICS 
    double     ArrayXiTanimotoNB(ArrayType *a1, ArrayType *a2);
    double     ArrayXiDiceNB(ArrayType *a1, ArrayType *a2);
    double     ArrayXiCosineNB(ArrayType *a1, ArrayType *a2);

    // DISTANCE METRICS
    double     ArrayXiEuclideanDist(ArrayType *a1, ArrayType *a2);
    double     ArrayXiManhattanDist(ArrayType *a1, ArrayType *a2);
    double     ArrayXiMeanHammingDist(ArrayType *a1, ArrayType *a2);


#ifdef __cplusplus
}
#endif
