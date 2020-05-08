#include "./Perspective.h"

template <class T> CPerspectiveProjection<T>::CPerspectiveProjection(void)
{
    CPerspectiveProjection<T>(60.0f, 16.0f/9.0f, 0.1f, 1000.0f);
}

template <class T> CPerspectiveProjection<T>::CPerspectiveProjection(float fovAngle, float aspectRatio, float zNear, float zFar)
{
    set(fovAngle, aspectRatio, zNear, zFar);
}

template <class T> CPerspectiveProjection<T>::CPerspectiveProjection(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar)
{
    set(fLeft, fRight, fTop, fBottom, fNear, fFar);
}

template <class T> void CPerspectiveProjection<T>::set(float fovAngle, float aspectRatio, float zNear, float zFar)
{
    float fScale = zNear * std::tan(fovAngle * 3.14159265f / 360.0f);

    float fRight = aspectRatio * fScale;
    float fLeft = -fRight;

    float fTop = fScale;
    float fBottom = -fTop;

    set(fLeft, fRight, fTop, fBottom, zNear, zFar);
}

template <class T> void CPerspectiveProjection<T>::set(float fLeft, float fRight, float fTop, float fBottom, float fNear, float fFar)
{
    m_pMatrix4[ 0] = (T) (2.0 * fNear / ((double)fRight - (double)fLeft));
    m_pMatrix4[ 1] = (T) 0.0;
    m_pMatrix4[ 2] = (T) 0.0;
    m_pMatrix4[ 3] = (T) 0.0;

    m_pMatrix4[ 4] = (T) 0.0;
    m_pMatrix4[ 5] = (T) (2.0 * fNear / ((double)fTop - (double)fBottom));
    m_pMatrix4[ 6] = (T) 0.0;
    m_pMatrix4[ 7] = (T) 0.0;

    m_pMatrix4[ 8] = (T)  ((fRight + fLeft) / (fRight - fLeft));
    m_pMatrix4[ 9] = (T)  ((fTop + fBottom) / (fTop - fBottom));
    m_pMatrix4[10] = (T) -((fFar + fNear) / (fFar - fNear));
    m_pMatrix4[11] = (T) -1.0;

    m_pMatrix4[12] = (T)  0.0;
    m_pMatrix4[13] = (T)  0.0;
    m_pMatrix4[14] = (T) -(2.0 * fFar * fNear / ((double)fFar - (double)fNear));
    m_pMatrix4[15] = (T)  0.0;
}

/* For linking */
template class CPerspectiveProjection<double>;
template class CPerspectiveProjection<float>;
template class CPerspectiveProjection<int>;
