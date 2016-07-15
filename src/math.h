#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#define SQRT_2 1.414214
#define PI 3.14159265358979323846

#define DEG2RAD(x) ((x) * PI / 180.0f)
#define RAD2DEG(x) ((x) * 180.0f / PI)

#define RAD2NDEG(x) RAD2DEG(x < 0 ? PI*2 + x : x)
#define NDEG2RAD(x) DEG2RAD(x > 180.0 ? x - 360.0 : x)

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

template <typename T> T lerp(T a, T b, float alpha)
{
    return a * alpha + b * (1.0 - alpha);
}

template <typename T> T sign(T a)
{
    if (a > 0)
        return 1;
    else if (a < 0)
        return -1;
    else
        return 0;
}

std::string NumberToString (float number);

#endif // MATH_H_INCLUDED
