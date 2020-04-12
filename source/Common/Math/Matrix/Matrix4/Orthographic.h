#pragma once
#include "Matrix4.h"

template <class T> class COrthographicProjection : public CMatrix4<T>
{
public:
    COrthographicProjection<T>(void);
    COrthographicProjection<T>(float aspectRatio, float left, float top, float zNear, float zFar);
    COrthographicProjection<T>(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);

    void set(float aspectRatio, float left, float top, float zNear, float zFar);
    void set(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);
};

typedef COrthographicProjection<double> COrthographicProjectiond;
typedef COrthographicProjection<float> COrthographicProjectionf;
typedef COrthographicProjection<int> COrthographicProjectioni;
