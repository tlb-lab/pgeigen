#ifndef VECTOR3D_H
#define VECTOR3D_H

#ifdef __cplusplus
extern "C"
{
#endif

    #include "postgres.h"
    #include "utils/array.h"
    
    int        Vector3dCmp(ArrayType *a1, ArrayType *a2);
    
    ArrayType *Vector3dConstant(double value);
    ArrayType *Vector3dRandom();
    
    ArrayType *Vector3dAdd(ArrayType *a1, ArrayType *a2);
    ArrayType *Vector3dSubtract(ArrayType *a1, ArrayType *a2);
    ArrayType *Vector3dScalarProduct(ArrayType *array, double scalar);
    ArrayType *Vector3dScalarDivision(ArrayType *array, double scalar);
    ArrayType *Vector3dCross(ArrayType *a1, ArrayType *a2);
    ArrayType *Vector3dNormalized(ArrayType *array);
    
    double     Vector3dDot(ArrayType *a1, ArrayType *a2);
    double     Vector3dNorm(ArrayType *array);
    double     Vector3dDistance(ArrayType *a1, ArrayType *a2);
    double     Vector3dAngle(ArrayType *a1, ArrayType *a2);
    double     Vector3dAbsAngle(ArrayType *a1, ArrayType *a2);

#ifdef __cplusplus
}
#endif

#endif