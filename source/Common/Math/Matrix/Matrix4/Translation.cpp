#include "./Translation.h"

template <class T> CTranslation<T>::CTranslation(void)
{
}

template <class T> CTranslation<T>::CTranslation(T x, T y, T z)
{
    setTranslation(x, y, z);
}

template <class T> CTranslation<T>::CTranslation(const CVector4<T> &newPos)
{
    setTranslation(newPos.x, newPos.y, newPos.z);
}

template <class T> CTranslation<T>::CTranslation(const CVector3<T> &newPos)
{
    setTranslation(newPos.x, newPos.y, newPos.z);
}

template <class T> void CTranslation<T>::setTranslation (const CVector4<T> &newPos)
{
    setTranslation(newPos.x, newPos.y, newPos.z);
}

template <class T> void CTranslation<T>::setTranslation(const CVector3<T> &newPos)
{
    setTranslation(newPos.x, newPos.y, newPos.z);
}

template <class T> void CTranslation<T>::setTranslation (T x, T y, T z)
{
    m_pMatrix4[ 0] = (T) 1.0;
    m_pMatrix4[ 1] = (T) 0.0;
    m_pMatrix4[ 2] = (T) 0.0;
    m_pMatrix4[ 3] = x;

    m_pMatrix4[ 4] = (T) 0.0;
    m_pMatrix4[ 5] = (T) 1.0;
    m_pMatrix4[ 6] = (T) 0.0;
    m_pMatrix4[ 7] = y;

    m_pMatrix4[ 8] = (T) 0.0;
    m_pMatrix4[ 9] = (T) 0.0;
    m_pMatrix4[10] = (T) 1.0;
    m_pMatrix4[11] = z;

    m_pMatrix4[12] = (T) 0.0;
    m_pMatrix4[13] = (T) 0.0;
    m_pMatrix4[14] = (T) 0.0;
    m_pMatrix4[15] = (T) 1.0;
}

/* For linking */
template class CTranslation<double>;
template class CTranslation<float>;
template class CTranslation<int>;
