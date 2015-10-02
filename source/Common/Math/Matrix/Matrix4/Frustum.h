#pragma once

#include "./Matrix4.h"

template <class T> class CFrustum : public CMatrix4<T>
{
    public:
        CFrustum<T>     (float fovAngle, float aspectRatio, float zNear, float zFar);
        CFrustum<T>     (float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);

        void setFrustum (float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);
};

typedef CFrustum<double> CFrustumd;
typedef CFrustum<float> CFrustumf;
typedef CFrustum<int> CFrustumi;
