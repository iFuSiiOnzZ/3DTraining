#pragma once
#include <cmath>
#include "./Matrix4.h"
#include "./../../Vector/Vector.h"

template <class T> class CMatrix4
{
    public:
        union
        {
            T m_pMatrix4[16];
            T biDimMax4[4][4];
        };

        CMatrix4<T>            (void);
        void setIdentity       (void);

        CMatrix4<T> operator * (const CMatrix4<T> &inputMatrix);
        CMatrix4<T> operator + (const CMatrix4<T> &inputMatrix);
        CMatrix4<T> operator - (const CMatrix4<T> &inputMatrix);
        CMatrix4<T> operator = (const CMatrix4<T> &inputMatrix);

        CVector4<T> operator * (const CVector4<T> &inputVector);
};

typedef CMatrix4<double> CMatrix4d;
typedef CMatrix4<float> CMatrix4f;
typedef CMatrix4<int> CMatrix4i;
