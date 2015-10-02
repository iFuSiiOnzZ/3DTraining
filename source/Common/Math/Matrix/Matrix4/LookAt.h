#pragma once

#include "./Matrix4.h"
#include "./../../Vector/Vector.h"

template <class T> class CLookAt : public CMatrix4<T>
{
    public:
        CLookAt         (CVector4<T> &eyePos, CVector4<T> &lookAt, CVector4<T> &upVector);

        void setLookAt  (CVector4<T> &eyePos, CVector4<T> &lookAt, CVector4<T> &upVector);
};

typedef CLookAt<double> CLookAtd;
typedef CLookAt<float> CLookAtf;
typedef CLookAt<int> CLookAti;
