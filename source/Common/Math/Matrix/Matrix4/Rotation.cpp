#include "./Rotation.h"
#include <cstdio>

template <class T> CRotation<T>::CRotation(void)
{
}

template <class T> CRotation<T>::CRotation(T rAngle, const CVector4<T> &rAxe)
{
    setRotation(rAngle, rAxe.x, rAxe.y, rAxe.z);
}

template <class T> CRotation<T>::CRotation(T rAngle, T x, T y, T z)
{
    setRotation(rAngle, x, y, z);
}

template <class T> void CRotation<T>::setRotation(T rAngle, const CVector4<T> &rAxe)
{
    setRotation(rAngle, rAxe.x, rAxe.y, rAxe.z);
}

template <class T> void CRotation<T>::setRotation(T rAngle, T x, T y, T z)
{
    T c = (T) std::cos(-rAngle * 3.14159265 / 180.0);
    T s = (T) std::sin(-rAngle * 3.14159265 / 180.0);
    T t = (T) 1.0 - c;

    m_pMatrix4[ 0] = x * x * t + c;
    m_pMatrix4[ 1] = x * y * t - z * s;
    m_pMatrix4[ 2] = x * z * t + y * s;
    m_pMatrix4[ 3] = (T) 0.0;

    m_pMatrix4[ 4] = y * x * t + z * s;
    m_pMatrix4[ 5] = y * y * t + c;
    m_pMatrix4[ 6] = y * z * t - x * s;
    m_pMatrix4[ 7] = (T) 0.0;

    m_pMatrix4[ 8] = z * x * t - y * s;
    m_pMatrix4[ 9] = z * y * t + x * s;
    m_pMatrix4[10] = z * z * t + c;
    m_pMatrix4[11] = (T) 0.0;

    m_pMatrix4[12] = (T) 0.0;
    m_pMatrix4[13] = (T) 0.0;
    m_pMatrix4[14] = (T) 0.0;
    m_pMatrix4[15] = (T) 1.0;
}

/* For linking */
template class CRotation<double>;
template class CRotation<float>;
template class CRotation<int>;