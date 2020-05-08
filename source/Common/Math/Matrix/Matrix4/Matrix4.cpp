#include "./Matrix4.h"

template <class T> CMatrix4<T>::CMatrix4(void)
{
    m_pMatrix4[ 0] = (T) 1.0;
    m_pMatrix4[ 1] = (T) 0.0;
    m_pMatrix4[ 2] = (T) 0.0;
    m_pMatrix4[ 3] = (T) 0.0;

    m_pMatrix4[ 4] = (T) 0.0;
    m_pMatrix4[ 5] = (T) 1.0;
    m_pMatrix4[ 6] = (T) 0.0;
    m_pMatrix4[ 7] = (T) 0.0;

    m_pMatrix4[ 8] = (T) 0.0;
    m_pMatrix4[ 9] = (T) 0.0;
    m_pMatrix4[10] = (T) 1.0;
    m_pMatrix4[11] = (T) 0.0;

    m_pMatrix4[12] = (T) 0.0;
    m_pMatrix4[13] = (T) 0.0;
    m_pMatrix4[14] = (T) 0.0;
    m_pMatrix4[15] = (T) 1.0;
}

template <class T> void CMatrix4<T>::setIdentity(void)
{
    m_pMatrix4[ 0] = (T) 1.0;
    m_pMatrix4[ 1] = (T) 0.0;
    m_pMatrix4[ 2] = (T) 0.0;
    m_pMatrix4[ 3] = (T) 0.0;

    m_pMatrix4[ 4] = (T) 0.0;
    m_pMatrix4[ 5] = (T) 1.0;
    m_pMatrix4[ 6] = (T) 0.0;
    m_pMatrix4[ 7] = (T) 0.0;

    m_pMatrix4[ 8] = (T) 0.0;
    m_pMatrix4[ 9] = (T) 0.0;
    m_pMatrix4[10] = (T) 1.0;
    m_pMatrix4[11] = (T) 0.0;

    m_pMatrix4[12] = (T) 0.0;
    m_pMatrix4[13] = (T) 0.0;
    m_pMatrix4[14] = (T) 0.0;
    m_pMatrix4[15] = (T) 1.0;
}

template <class T> CMatrix4<T> CMatrix4<T>::operator * (const CMatrix4<T> &inputMatrix)
{
    CMatrix4<T> newMatrix;

    newMatrix.m_pMatrix4[ 0] = m_pMatrix4[ 0] * inputMatrix.m_pMatrix4[ 0] + m_pMatrix4[ 1] * inputMatrix.m_pMatrix4[ 4] + m_pMatrix4[ 2] * inputMatrix.m_pMatrix4[ 8] + m_pMatrix4[ 3] * inputMatrix.m_pMatrix4[12];
    newMatrix.m_pMatrix4[ 1] = m_pMatrix4[ 0] * inputMatrix.m_pMatrix4[ 1] + m_pMatrix4[ 1] * inputMatrix.m_pMatrix4[ 5] + m_pMatrix4[ 2] * inputMatrix.m_pMatrix4[ 9] + m_pMatrix4[ 3] * inputMatrix.m_pMatrix4[13];
    newMatrix.m_pMatrix4[ 2] = m_pMatrix4[ 0] * inputMatrix.m_pMatrix4[ 2] + m_pMatrix4[ 1] * inputMatrix.m_pMatrix4[ 6] + m_pMatrix4[ 2] * inputMatrix.m_pMatrix4[10] + m_pMatrix4[ 3] * inputMatrix.m_pMatrix4[14];
    newMatrix.m_pMatrix4[ 3] = m_pMatrix4[ 0] * inputMatrix.m_pMatrix4[ 3] + m_pMatrix4[ 1] * inputMatrix.m_pMatrix4[ 7] + m_pMatrix4[ 2] * inputMatrix.m_pMatrix4[11] + m_pMatrix4[ 3] * inputMatrix.m_pMatrix4[15];

    newMatrix.m_pMatrix4[ 4] = m_pMatrix4[ 4] * inputMatrix.m_pMatrix4[ 0] + m_pMatrix4[ 5] * inputMatrix.m_pMatrix4[ 4] + m_pMatrix4[ 6] * inputMatrix.m_pMatrix4[ 8] + m_pMatrix4[ 7] * inputMatrix.m_pMatrix4[12];
    newMatrix.m_pMatrix4[ 5] = m_pMatrix4[ 4] * inputMatrix.m_pMatrix4[ 1] + m_pMatrix4[ 5] * inputMatrix.m_pMatrix4[ 5] + m_pMatrix4[ 6] * inputMatrix.m_pMatrix4[ 9] + m_pMatrix4[ 7] * inputMatrix.m_pMatrix4[13];
    newMatrix.m_pMatrix4[ 6] = m_pMatrix4[ 4] * inputMatrix.m_pMatrix4[ 2] + m_pMatrix4[ 5] * inputMatrix.m_pMatrix4[ 6] + m_pMatrix4[ 6] * inputMatrix.m_pMatrix4[10] + m_pMatrix4[ 7] * inputMatrix.m_pMatrix4[14];
    newMatrix.m_pMatrix4[ 7] = m_pMatrix4[ 4] * inputMatrix.m_pMatrix4[ 3] + m_pMatrix4[ 5] * inputMatrix.m_pMatrix4[ 7] + m_pMatrix4[ 6] * inputMatrix.m_pMatrix4[11] + m_pMatrix4[ 7] * inputMatrix.m_pMatrix4[15];

    newMatrix.m_pMatrix4[ 8] = m_pMatrix4[ 8] * inputMatrix.m_pMatrix4[ 0] + m_pMatrix4[ 9] * inputMatrix.m_pMatrix4[ 4] + m_pMatrix4[10] * inputMatrix.m_pMatrix4[ 8] + m_pMatrix4[11] * inputMatrix.m_pMatrix4[12];
    newMatrix.m_pMatrix4[ 9] = m_pMatrix4[ 8] * inputMatrix.m_pMatrix4[ 1] + m_pMatrix4[ 9] * inputMatrix.m_pMatrix4[ 5] + m_pMatrix4[10] * inputMatrix.m_pMatrix4[ 9] + m_pMatrix4[11] * inputMatrix.m_pMatrix4[13];
    newMatrix.m_pMatrix4[10] = m_pMatrix4[ 8] * inputMatrix.m_pMatrix4[ 2] + m_pMatrix4[ 9] * inputMatrix.m_pMatrix4[ 6] + m_pMatrix4[10] * inputMatrix.m_pMatrix4[10] + m_pMatrix4[11] * inputMatrix.m_pMatrix4[14];
    newMatrix.m_pMatrix4[11] = m_pMatrix4[ 8] * inputMatrix.m_pMatrix4[ 3] + m_pMatrix4[ 9] * inputMatrix.m_pMatrix4[ 7] + m_pMatrix4[10] * inputMatrix.m_pMatrix4[11] + m_pMatrix4[11] * inputMatrix.m_pMatrix4[15];

    newMatrix.m_pMatrix4[12] = m_pMatrix4[12] * inputMatrix.m_pMatrix4[ 0] + m_pMatrix4[13] * inputMatrix.m_pMatrix4[ 4] + m_pMatrix4[14] * inputMatrix.m_pMatrix4[ 8] + m_pMatrix4[15] * inputMatrix.m_pMatrix4[12];
    newMatrix.m_pMatrix4[13] = m_pMatrix4[12] * inputMatrix.m_pMatrix4[ 1] + m_pMatrix4[13] * inputMatrix.m_pMatrix4[ 5] + m_pMatrix4[14] * inputMatrix.m_pMatrix4[ 9] + m_pMatrix4[15] * inputMatrix.m_pMatrix4[13];
    newMatrix.m_pMatrix4[14] = m_pMatrix4[12] * inputMatrix.m_pMatrix4[ 2] + m_pMatrix4[13] * inputMatrix.m_pMatrix4[ 6] + m_pMatrix4[14] * inputMatrix.m_pMatrix4[10] + m_pMatrix4[15] * inputMatrix.m_pMatrix4[14];
    newMatrix.m_pMatrix4[15] = m_pMatrix4[12] * inputMatrix.m_pMatrix4[ 3] + m_pMatrix4[13] * inputMatrix.m_pMatrix4[ 7] + m_pMatrix4[14] * inputMatrix.m_pMatrix4[11] + m_pMatrix4[15] * inputMatrix.m_pMatrix4[15];

    return(newMatrix);
}

template <class T> CMatrix4<T> CMatrix4<T>::operator + (const CMatrix4<T> &inputMatrix)
{
    CMatrix4<T> newMatrix;

    newMatrix.m_pMatrix4[ 0] = m_pMatrix4[ 0] + inputMatrix.m_pMatrix4[ 0];
    newMatrix.m_pMatrix4[ 1] = m_pMatrix4[ 1] + inputMatrix.m_pMatrix4[ 1];
    newMatrix.m_pMatrix4[ 2] = m_pMatrix4[ 2] + inputMatrix.m_pMatrix4[ 2];
    newMatrix.m_pMatrix4[ 3] = m_pMatrix4[ 3] + inputMatrix.m_pMatrix4[ 3];

    newMatrix.m_pMatrix4[ 4] = m_pMatrix4[ 4] + inputMatrix.m_pMatrix4[ 4];
    newMatrix.m_pMatrix4[ 5] = m_pMatrix4[ 5] + inputMatrix.m_pMatrix4[ 5];
    newMatrix.m_pMatrix4[ 6] = m_pMatrix4[ 6] + inputMatrix.m_pMatrix4[ 6];
    newMatrix.m_pMatrix4[ 7] = m_pMatrix4[ 7] + inputMatrix.m_pMatrix4[ 7];

    newMatrix.m_pMatrix4[ 8] = m_pMatrix4[ 8] + inputMatrix.m_pMatrix4[ 8];
    newMatrix.m_pMatrix4[ 9] = m_pMatrix4[ 9] + inputMatrix.m_pMatrix4[ 9];
    newMatrix.m_pMatrix4[10] = m_pMatrix4[10] + inputMatrix.m_pMatrix4[10];
    newMatrix.m_pMatrix4[11] = m_pMatrix4[11] + inputMatrix.m_pMatrix4[11];

    newMatrix.m_pMatrix4[12] = m_pMatrix4[12] + inputMatrix.m_pMatrix4[12];
    newMatrix.m_pMatrix4[13] = m_pMatrix4[13] + inputMatrix.m_pMatrix4[13];
    newMatrix.m_pMatrix4[14] = m_pMatrix4[14] + inputMatrix.m_pMatrix4[14];
    newMatrix.m_pMatrix4[15] = m_pMatrix4[15] + inputMatrix.m_pMatrix4[15];

    return(newMatrix);
}

template <class T> CMatrix4<T> CMatrix4<T>::operator - (const CMatrix4<T> &inputMatrix)
{
    CMatrix4<T> newMatrix;

    newMatrix.m_pMatrix4[ 0] = m_pMatrix4[ 0] - inputMatrix.m_pMatrix4[ 0];
    newMatrix.m_pMatrix4[ 1] = m_pMatrix4[ 1] - inputMatrix.m_pMatrix4[ 1];
    newMatrix.m_pMatrix4[ 2] = m_pMatrix4[ 2] - inputMatrix.m_pMatrix4[ 2];
    newMatrix.m_pMatrix4[ 3] = m_pMatrix4[ 3] - inputMatrix.m_pMatrix4[ 3];

    newMatrix.m_pMatrix4[ 4] = m_pMatrix4[ 4] - inputMatrix.m_pMatrix4[ 4];
    newMatrix.m_pMatrix4[ 5] = m_pMatrix4[ 5] - inputMatrix.m_pMatrix4[ 5];
    newMatrix.m_pMatrix4[ 6] = m_pMatrix4[ 6] - inputMatrix.m_pMatrix4[ 6];
    newMatrix.m_pMatrix4[ 7] = m_pMatrix4[ 7] - inputMatrix.m_pMatrix4[ 7];

    newMatrix.m_pMatrix4[ 8] = m_pMatrix4[ 8] - inputMatrix.m_pMatrix4[ 8];
    newMatrix.m_pMatrix4[ 9] = m_pMatrix4[ 9] - inputMatrix.m_pMatrix4[ 9];
    newMatrix.m_pMatrix4[10] = m_pMatrix4[10] - inputMatrix.m_pMatrix4[10];
    newMatrix.m_pMatrix4[11] = m_pMatrix4[11] - inputMatrix.m_pMatrix4[11];

    newMatrix.m_pMatrix4[12] = m_pMatrix4[12] - inputMatrix.m_pMatrix4[12];
    newMatrix.m_pMatrix4[13] = m_pMatrix4[13] - inputMatrix.m_pMatrix4[13];
    newMatrix.m_pMatrix4[14] = m_pMatrix4[14] - inputMatrix.m_pMatrix4[14];
    newMatrix.m_pMatrix4[15] = m_pMatrix4[15] - inputMatrix.m_pMatrix4[15];

    return(newMatrix);
}

template <class T> CMatrix4<T> CMatrix4<T>::operator = (const CMatrix4<T> &inputMatrix)
{
    m_pMatrix4[ 0] = inputMatrix.m_pMatrix4[ 0];
    m_pMatrix4[ 1] = inputMatrix.m_pMatrix4[ 1];
    m_pMatrix4[ 2] = inputMatrix.m_pMatrix4[ 2];
    m_pMatrix4[ 3] = inputMatrix.m_pMatrix4[ 3];

    m_pMatrix4[ 4] = inputMatrix.m_pMatrix4[ 4];
    m_pMatrix4[ 5] = inputMatrix.m_pMatrix4[ 5];
    m_pMatrix4[ 6] = inputMatrix.m_pMatrix4[ 6];
    m_pMatrix4[ 7] = inputMatrix.m_pMatrix4[ 7];

    m_pMatrix4[ 8] = inputMatrix.m_pMatrix4[ 8];
    m_pMatrix4[ 9] = inputMatrix.m_pMatrix4[ 9];
    m_pMatrix4[10] = inputMatrix.m_pMatrix4[10];
    m_pMatrix4[11] = inputMatrix.m_pMatrix4[11];

    m_pMatrix4[12] = inputMatrix.m_pMatrix4[12];
    m_pMatrix4[13] = inputMatrix.m_pMatrix4[13];
    m_pMatrix4[14] = inputMatrix.m_pMatrix4[14];
    m_pMatrix4[15] = inputMatrix.m_pMatrix4[15];

    return(*this);
}

template <class T> CVector4<T> CMatrix4<T>::operator * (const CVector4<T> &inputVector)
{
    CVector4<T> newVector;

    newVector.x = m_pMatrix4[ 0] * inputVector.x + m_pMatrix4[ 1] * inputVector.y + m_pMatrix4[ 2] * inputVector.z + m_pMatrix4[ 3] * inputVector.w;
    newVector.y = m_pMatrix4[ 4] * inputVector.x + m_pMatrix4[ 5] * inputVector.y + m_pMatrix4[ 6] * inputVector.z + m_pMatrix4[ 7] * inputVector.w;
    newVector.z = m_pMatrix4[ 8] * inputVector.x + m_pMatrix4[ 9] * inputVector.y + m_pMatrix4[10] * inputVector.z + m_pMatrix4[11] * inputVector.w;
    newVector.w = m_pMatrix4[12] * inputVector.x + m_pMatrix4[13] * inputVector.y + m_pMatrix4[14] * inputVector.z + m_pMatrix4[15] * inputVector.w;

    return(newVector);
}

/* For linking */
template class CMatrix4<double>;
template class CMatrix4<float>;
template class CMatrix4<int>;