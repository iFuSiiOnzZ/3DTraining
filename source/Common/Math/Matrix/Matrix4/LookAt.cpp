#include "./LookAt.h"

template <class T> CLookAt<T>::CLookAt(void) : CMatrix4<T>()
{
    setLookAt(CVector4<T>(1, 1, 1), CVector4<T>(), CVector4<T>(0, 1, 0));
}

template <class T> CLookAt<T>::CLookAt(const CVector4<T> &eyePos, const CVector4<T> &lookAt, const CVector4<T> &upVector) : CMatrix4<T>()
{
    setLookAt(eyePos, lookAt, upVector);
}

template <class T> CLookAt<T>::CLookAt(const CVector3<T> &eyePos, const CVector3<T> &lookAt, const CVector3<T> &upVector) : CMatrix4<T>()
{
    setLookAt(eyePos, lookAt, upVector);
}
template <class T> void CLookAt<T>::setLookAt(const CVector4<T> &eyePos, const CVector4<T> &lookAt, const CVector4<T> &upVector)
{
    setLookAt(eyePos.xyz, lookAt.xyz, upVector.xyz);
}

template <class T> void CLookAt<T>::setLookAt(const CVector3<T> &eyePos, const CVector3<T> &lookAt, const CVector3<T> &upVector)
{
    CVector3<T> zAxis = (eyePos - lookAt).normalize();
    CVector3<T> xAxis = (upVector ^ zAxis).normalize();
    CVector3<T> yAxis = (zAxis ^ xAxis).normalize();

    m_pMatrix4[ 0] = xAxis.x;
    m_pMatrix4[ 1] = yAxis.x;
    m_pMatrix4[ 2] = zAxis.x;
    m_pMatrix4[ 3] = (T) 0.0;

    m_pMatrix4[ 4] = xAxis.y;
    m_pMatrix4[ 5] = yAxis.y;
    m_pMatrix4[ 6] = zAxis.y;
    m_pMatrix4[ 7] = (T) 0.0;

    m_pMatrix4[ 8] = xAxis.z;
    m_pMatrix4[ 9] = yAxis.z;
    m_pMatrix4[10] = zAxis.z;
    m_pMatrix4[11] = (T) 0.0;

    m_pMatrix4[12] = -(xAxis & eyePos);
    m_pMatrix4[13] = -(yAxis & eyePos);
    m_pMatrix4[14] = -(zAxis & eyePos);
    m_pMatrix4[15] = (T) 1.0;
}

/* For linking */
template class CLookAt<double>;
template class CLookAt<float>;
template class CLookAt<int>;
