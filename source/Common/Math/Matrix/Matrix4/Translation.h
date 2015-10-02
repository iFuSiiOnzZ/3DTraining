#pragma once

#include "./Matrix4.h"

template <class T> class CTranslation : public CMatrix4<T>
{
    public:
        CTranslation        (const CVector4<T> &newPos);
        CTranslation        (T x, T y, T z);
        CTranslation        (void);

        void setTranslation (const CVector4<T> &newPos);
        void setTranslation (T x, T y, T z);
};

typedef CTranslation<double> CTranslationd;
typedef CTranslation<float> CTranslationf;
typedef CTranslation<int> CTranslationi;
