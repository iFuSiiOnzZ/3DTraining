#pragma once
#include "./Matrix4.h"

template <class T>  class CScale : public CMatrix4<T>
{
    public:
        CScale          (const CVector4<T> &newScale);
        CScale          (const CVector3<T> &newScale);

        CScale          (T x, T y, T z);
        CScale          (void);

        void setScale   (const CVector4<T> &newScale);
        void setScale   (const CVector3<T> &newScale);
        void setScale   (T x, T y, T z);
};

typedef CScale<double> CScaled;
typedef CScale<float> CScalef;
typedef CScale<int> CScalei;
