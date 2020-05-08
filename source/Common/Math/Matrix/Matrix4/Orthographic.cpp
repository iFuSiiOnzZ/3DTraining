#include "Orthographic.h"

template<class T> inline COrthographicProjection<T>::COrthographicProjection(void)
{
    set(16.0f / 9.0f, 10.0f, 10.0f, 0.1f, 1000.0f);
}

template<class T> COrthographicProjection<T>::COrthographicProjection(float aspectRatio, float left, float top, float zNear, float zFar)
{
    set(aspectRatio, left, top, zNear, zFar);
}

template<class T> COrthographicProjection<T>::COrthographicProjection(float fLeft, float fRight, float fTop, float fBottom, float zNear, float zFar)
{
    set(fLeft, fRight, fTop, fBottom, zNear, zFar);
}

template<class T> void COrthographicProjection<T>::set(float aspectRatio, float left, float top, float zNear, float zFar)
{
    float fRight = aspectRatio * left;
    float fLeft = -fRight;

    float fTop = top;
    float fBottom = -fTop;

    set(fLeft, fRight, fTop, fBottom, zNear, zFar);
}
template<class T> void COrthographicProjection<T>::set(float fLeft, float fRight, float fTop, float fBottom, float zNear, float zFar)
{
    m_pMatrix4[ 0] = (T)(2.0 / ((double)fRight - (double)fLeft));
    m_pMatrix4[ 1] = (T)0.0;
    m_pMatrix4[ 2] = (T)0.0;
    m_pMatrix4[ 3] = (T)0.0;

    m_pMatrix4[ 4] = (T)0.0;
    m_pMatrix4[ 5] = (T)(2.0 / ((double)fTop - (double)fBottom));
    m_pMatrix4[ 6] = (T)0.0;
    m_pMatrix4[ 7] = (T)0.0;

    m_pMatrix4[ 8] = (T)0.0;
    m_pMatrix4[ 9] = (T)0.0;
    m_pMatrix4[10] = (T)(-2.0 / ((double)zFar - (double)zNear));
    m_pMatrix4[11] = (T)0.0;

    m_pMatrix4[12] = (T)-((fRight + fLeft) / (fRight - fLeft));
    m_pMatrix4[13] = (T)-((fTop + fBottom) / (fTop - fBottom));
    m_pMatrix4[14] = (T)-((zFar + zNear) / (zFar - zNear));
    m_pMatrix4[15] = (T)1.0;

}

/* For linking */
template class COrthographicProjection<double>;
template class COrthographicProjection<float>;
template class COrthographicProjection<int>;

