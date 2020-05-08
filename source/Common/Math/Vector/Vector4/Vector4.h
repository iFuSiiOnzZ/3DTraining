#pragma once

template <class T> class CVector2
{
public:
    union
    {
        struct { T x; T y; };
        T u[3];
    };

    CVector2(void) : x((T)0), y((T)0) {}
    CVector2(T xx, T yy) : x(xx), y(yy) {}

    T length(void)
    {
        return((T)std::sqrtl(x * x + y * y));
    }

    CVector2<T> normalize(void)
    {
        T l = (T)(1.0 / length());
        return CVector2<T>(x * l, y * l);
    }
};

template <class T> class CVector3
{
public:
    union
    {
        struct { T x; T y; T z; };
        struct { T r; T g; T b; };

        CVector2<T> xy;
        T u[3];
    };

    CVector3(void) : x((T)0), y((T)0), z((T)0) {}
    CVector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}

    T length(void)
    {
        return((T)std::sqrt(x * x + y * y + z * z));
    }

    CVector3<T> normalize(void)
    {
        T l = (T)(1.0 / length());
        return CVector3<T>(x * l, y * l, z * l);
    }
};

template <class T> class CVector4
{
    public:
        union
        {
            struct { T x; T y; T z; T w; };
            struct { T r; T g; T b; T a; };

            CVector3<T> xyz;
            T u[4];
        };

        CVector4(void) : x((T)0), y((T)0), z((T)0), w((T)0){}
        CVector4(T xx, T yy, T zz) : x(xx), y(yy), z(zz), w((T)1){}
        CVector4(T xx, T yy, T zz, T ww) :  x(xx), y(yy), z(zz), w(ww) {}

        T                  length(void)
        {
            return((T)std::sqrtl(x * x + y * y + z * z + w * w));
        }

        CVector4<T>        normalize(void)
        {
            T l = (T)(1.0 / length());
            return(CVector4<T>(x * l, y * l, z * l, w * l));
        }
};

///////////////////////////////////////////////////////////////////////////////

template <class T> CVector3<T> operator - (const CVector3<T> &v)
{
    return CVector3<T>(-v.x, -v.y, -v.z);
}

template <class T> CVector3<T> operator + (const CVector3<T> &v1, const CVector3<T> &v2)
{
    return CVector3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

template <class T> CVector3<T> operator - (const CVector3<T> &v1, const CVector3<T> &v2)
{
    return CVector3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

template <class T> CVector3<T> operator * (const CVector3<T> &v, T n)
{
    return CVector3<T>(v.x * n, v.y * n, v.z * n);
}

template <class T> CVector3<T> operator / (const CVector3<T> &v, T n)
{
    T l = (T)(1.0 / n);
    return CVector3<T>(v.x * l, v.y * l, v.z * l);
}

template <class T> CVector3<T> operator ^ (const CVector3<T> &v1, const CVector3<T> &v2)
{
    T x = v1.y * v2.z - v1.z * v2.y;
    T y = v1.z * v2.x - v1.x * v2.z;
    T z = v1.x * v2.y - v1.y * v2.x;

    return CVector3<T>(x, y, z);
}

template <class T> T operator & (const CVector3<T> &v1, const CVector3<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

///////////////////////////////////////////////////////////////////////////////

template <class T> CVector4<T> operator - (const CVector4<T> &v)
{
    return CVector4<T>(-v.x, -v.y, -v.z, -v.w);
}

template <class T> CVector4<T> operator + (const CVector4<T> &v1, const CVector4<T> &v2)
{
    return CVector4<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

template <class T> CVector4<T> operator - (const CVector4<T> &v1, const CVector4<T> &v2)
{
    return CVector4<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

template <class T> CVector4<T> operator * (const CVector4<T> &v, T n)
{
    return CVector4<T>(v.x * n, v.y * n, v.z * n, v.w * n);
}

template <class T> CVector4<T> operator / (const CVector4<T> &v, T n)
{
    T l = (T)(1.0 / n);
    return CVector4<T>(v.x * l, v.y * l, v.z * l, v.w * l);
}

template <class T> CVector4<T> operator ^ (const CVector4<T> &v1, const CVector4<T> &v2)
{
    T x = v1.y * v2.z - v1.z * v2.y;
    T y = v1.z * v2.x - v1.x * v2.z;
    T z = v1.x * v2.y - v1.y * v2.x;

    return CVector4<T>(x, y, z);
}

template <class T> T operator & (const CVector4<T> &v1, const CVector4<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

///////////////////////////////////////////////////////////////////////////////

typedef CVector2<double> CVector2d;
typedef CVector2<float> CVector2f;
typedef CVector2<int> CVector2i;

typedef CVector3<double> CVector3d;
typedef CVector3<float> CVector3f;
typedef CVector3<int> CVector3i;

typedef CVector4<double> CVector4d;
typedef CVector4<float> CVector4f;
typedef CVector4<int> CVector4i;
