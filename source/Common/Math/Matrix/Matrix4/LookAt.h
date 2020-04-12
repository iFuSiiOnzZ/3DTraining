#pragma once

#include "./Matrix4.h"
#include "./../../Vector/Vector.h"

template <class T> class CLookAt : public CMatrix4<T>
{
    public:
        CLookAt         (void);

        CLookAt         (const CVector4<T> &eyePos, const CVector4<T> &lookAt, const CVector4<T> &upVector);
        CLookAt         (const CVector3<T> &eyePos, const CVector3<T> &lookAt, const CVector3<T> &upVector);

        void setLookAt  (const CVector4<T> &eyePos, const CVector4<T> &lookAt, const CVector4<T> &upVector);
        void setLookAt  (const CVector3<T> &eyePos, const CVector3<T> &lookAt, const CVector3<T> &upVector);
};

typedef CLookAt<double> CLookAtd;
typedef CLookAt<float> CLookAtf;
typedef CLookAt<int> CLookAti;
