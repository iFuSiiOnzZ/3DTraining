#pragma once

#include "./Matrix4.h"

template <class T> class CPerspectiveProjection : public CMatrix4<T>
{
    public:
        CPerspectiveProjection<T>     (void);
        CPerspectiveProjection<T>     (float fovAngle, float aspectRatio, float zNear, float zFar);
        CPerspectiveProjection<T>     (float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);

        void set (float fovAngle, float aspectRatio, float zNear, float zFar);
        void set (float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar);
};

typedef CPerspectiveProjection<double> CPerspectiveProjectiond;
typedef CPerspectiveProjection<float> CPerspectiveProjectionf;
typedef CPerspectiveProjection<int> CPerspectiveProjectioni;
