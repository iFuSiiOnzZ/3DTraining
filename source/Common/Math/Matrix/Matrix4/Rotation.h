#pragma once
#include "./Matrix4.h"

template <class T> class CRotation : public CMatrix4<T>
{
    public:
        CRotation           (T rAngle, const CVector4<T> &rAxe);
        CRotation           (T rAngle, T x, T y, T z);
        CRotation           (void);

        void setRotation    (T rAngle, const CVector4<T> &rAxe);
        void setRotation    (T rAngle, T x, T y, T z);
};

typedef CRotation<double> CRotationd;
typedef CRotation<float> CRotationf;
typedef CRotation<int> CRotationi;
