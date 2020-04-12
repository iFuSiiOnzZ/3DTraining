#pragma once

#include <cstdlib>

#define CONSTANTS_PI        3.14159265359f
#define CONSTANTS_TWO_PI    (CONSTANTS_PI * 2.0f)
#define CONSTANTS_HALF_PI   (CONSTANTS_PI * 0.5f)

template <class T> static inline T DEG2RAD(T d)
{
    return (T)(d * (CONSTANTS_PI / 180.0));
}

template <class T> static inline T RAD2DEG(T d)
{
    return (T)(d * (180.0 / CONSTANTS_PI));
}

template <class T, size_t sz> size_t GetNumElements(T(&)[sz])
{
    return sz;
}

template <class T> static inline T MAX(const T &a, const T &b)
{
    return a > b ? a : b;
}

template <class T> static inline T MIN(const T &a, const T &b)
{
    return a < b ? a : b;
}

template <class T> static inline T CLAMP(const T &min, const T &val, const T &max)
{
    return MIN(MAX(min, val), max);
}

template <class T> static inline T random(T start, T end)
{
    return (T) (rand() * (end - start) + start);
}

template <class T> static inline T random(T range)
{
    return (T)(rand() * range);
}
