#include "./Scale.h"

template <class T> CScale<T>::CScale(void)
{
}

template <class T> CScale<T>::CScale(T x, T y, T z)
{
    setScale(x, y, z);
}

template <class T> CScale<T>::CScale(const CVector4<T> &newScale)
{
    setScale(newScale.x, newScale.y, newScale.z);
}

template <class T> CScale<T>::CScale(const CVector3<T> &newScale)
{
    setScale(newScale.x, newScale.y, newScale.z);
}

template <class T> void CScale<T>::setScale(const CVector4<T> &newScale)
{
    setScale(newScale.x, newScale.y, newScale.z);
}

template <class T> void CScale<T>::setScale(const CVector3<T> &newScale)
{
    setScale(newScale.x, newScale.y, newScale.z);
}

template <class T> void CScale<T>::setScale (T x, T y, T z)
{
    m_pMatrix4[ 0] = x;
    m_pMatrix4[ 1] = (T) 0.0;
    m_pMatrix4[ 2] = (T) 0.0;
    m_pMatrix4[ 3] = (T) 0.0;

    m_pMatrix4[ 4] = (T) 0.0;
    m_pMatrix4[ 5] = y;
    m_pMatrix4[ 6] = (T) 0.0;
    m_pMatrix4[ 7] = (T) 0.0;

    m_pMatrix4[ 8] = (T) 0.0;
    m_pMatrix4[ 9] = (T) 0.0;
    m_pMatrix4[10] = z;
    m_pMatrix4[11] = (T) 0.0;

    m_pMatrix4[12] = (T) 0.0;
    m_pMatrix4[13] = (T) 0.0;
    m_pMatrix4[14] = (T) 0.0;
    m_pMatrix4[15] = (T) 1.0;
}

/* For linking */
template class CScale<double>;
template class CScale<float>;
template class CScale<int>;
