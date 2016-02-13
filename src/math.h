#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

template <typename T> T lerp(T a, T b, float alpha)
{
    return a * alpha + b * (1.0 - alpha);
}

#endif // MATH_H_INCLUDED
