#pragma once

#include <cstdlib>

#define CONSTANTS_PI        3.14159265359f
#define CONSTANTS_TWO_PI    (CONSTANTS_PI * 2.0f)
#define CONSTANTS_HALF_PI   (CONSTANTS_PI * 0.5f)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define DEG2RAD(d) ((d) * (CONSTANTS_PI / 180.0f))
#define RAD2DEG(r) ((r) * (180.0f / CONSTANTS_PI))

#define ARRAYCOUNT(v) (sizeof(v) / sizeof((v)[0]))

template <class T> inline T clamp(T l_Val, T l_Min, T l_Max)
{
    return l_Val < l_Min ? l_Min : l_Val < l_Max ? l_Val : l_Max;
}

template <class T> inline T random(T l_Start, T l_End)
{
    return (T) (rand() * (l_End - l_Start) + l_Start);
}

template <class T> inline T random(T l_Range)
{
    return (T)(rand() * l_Range);
}
