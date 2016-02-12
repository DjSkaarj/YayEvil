#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "common.h"

struct Vector2i
{
    int x;
    int y;

    Vector2i() {}

    Vector2i(int x, int y):
        x(x),
        y(y)
    {}

    void operator+=(Vector2i rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    void operator-=(Vector2i rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
    }

    void operator*=(Vector2i rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
    }

    void operator/=(Vector2i rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
    }

    void operator%=(Vector2i rhs)
    {
        x %= rhs.x;
        y %= rhs.y;
    }

    int area() const
    {
        return x * y;
    }

    float length() const
    {
        return sqrt(x * x + y * y);
    }

    // Length squared.
    float length2() const
    {
        return x * x + y * y;
    }
};

struct Vector2f
{
    float x;
    float y;

    Vector2f() {}

    Vector2f(float x, float y):
        x(x),
        y(y)
    {}

    Vector2f(Vector2i rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }

    Vector2i floor()
    {
        return Vector2i(::floor(x), ::floor(y));
    }

    Vector2i ceil()
    {
        return Vector2i(::ceil(x), ::ceil(y));
    }

    Vector2i trunc()
    {
        return Vector2i(::trunc(x), ::trunc(y));
    }

    void operator+=(Vector2f rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    void operator-=(Vector2f rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
    }

    void operator*=(Vector2f rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
    }

    void operator/=(Vector2f rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
    }

    int area() const
    {
        return x * y;
    }

    float length() const
    {
        return sqrt(x * x + y * y);
    }

    // Length squared.
    float length2() const
    {
        return x * x + y * y;
    }
};

bool operator==(Vector2i a, Vector2i b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator==(Vector2f a, Vector2f b)
{
    return a.x == b.x && a.y == b.y;
}

Vector2i operator+(Vector2i a, Vector2i b)
{
    return Vector2i(a.x + b.x, a.y + b.y);
}

Vector2i operator-(Vector2i a, Vector2i b)
{
    return Vector2i(a.x - b.x, a.y - b.y);
}

Vector2i operator*(Vector2i a, Vector2i b)
{
    return Vector2i(a.x * b.x, a.y * b.y);
}

Vector2i operator/(Vector2i a, Vector2i b)
{
    return Vector2i(a.x / b.x, a.y / b.y);
}

Vector2i operator%(Vector2i a, Vector2i b)
{
    return Vector2i(a.x % b.x, a.y % b.y);
}

Vector2f operator+(Vector2f a, Vector2f b)
{
    return Vector2f(a.x + b.x, a.y + b.y);
}

Vector2f operator-(Vector2f a, Vector2f b)
{
    return Vector2f(a.x - b.x, a.y - b.y);
}

Vector2f operator*(Vector2f a, Vector2f b)
{
    return Vector2f(a.x * b.x, a.y * b.y);
}

Vector2f operator/(Vector2f a, Vector2f b)
{
    return Vector2f(a.x / b.x, a.y / b.y);
}


Vector2f operator+(Vector2i a, Vector2f b)
{
    return Vector2i(float(a.x) + b.x, float(a.y) + b.y);
}

Vector2f operator-(Vector2i a, Vector2f b)
{
    return Vector2i(float(a.x) - b.x, float(a.y) - b.y);
}

Vector2f operator*(Vector2i a, Vector2f b)
{
    return Vector2i(float(a.x) * b.x, float(a.y) * b.y);
}

Vector2f operator/(Vector2i a, Vector2f b)
{
    return Vector2i(float(a.x) / b.x, float(a.y) / b.y);
}

class RectI
{
public:
    RectI() {}

    RectI(int minX, int maxX, int minY, int maxY)
    {
        mMinX = minX;
        mMaxX = maxX;
        mMinY = minY;
        mMaxY = maxY;
    }

    RectI(Vector2i a, Vector2i b)
    {
        mMinX = min(a.x, b.x);
        mMaxX = max(a.x, b.x);
        mMinY = min(a.y, b.y);
        mMaxY = max(a.y, b.y);
    }

    bool isNull() const
    {
        return minX() > maxX() || minY() > maxY();
    }

    bool isValid() const
    {
        return !isNull();
    }

    bool isImaginary() const
    {
        return isNull();
    }

    int minX() const
    {
        return mMinX;
    }

    int maxX() const
    {
        return mMaxX;
    }

    int minY() const
    {
        return mMinY;
    }

    int maxY() const
    {
        return mMaxY;
    }

    Vector2i size() const
    {
        return Vector2i(maxX() - minX() + 1, maxY() - minY() + 1);
    }

    int area() const
    {
        return size().area();
    }

    bool contains(Vector2i point) const
    {
        return point.x >= minX() && point.x <= maxX() && point.y >= minY() && point.y <= maxY();
    }

    RectI unite(RectI rhs) const
    {
        return RectI(
                    min(minX(), rhs.minX()),
                    max(maxX(), rhs.maxX()),
                    min(minY(), rhs.minY()),
                    max(maxY(), rhs.maxY()));
    }

    RectI intersect(RectI rhs) const
    {
        return RectI(
                    max(minX(), rhs.minX()),
                    min(maxX(), rhs.maxX()),
                    max(minY(), rhs.minY()),
                    min(maxY(), rhs.maxY()));
    }

    bool intersects(RectI rhs) const
    {
        return intersect(rhs).isValid();
    }

    bool contains(RectI inner) const;

private:
    int mMinX;
    int mMaxX;
    int mMinY;
    int mMaxY;
};

bool operator==(RectI a, RectI b)
{
    return a.minX() == b.minX() && a.maxX() == b.maxX() && a.minY() == b.minY() && a.maxY() == b.maxY();
}

bool RectI::contains(RectI inner) const
{
    return intersect(inner) == inner;
}

class RectF
{
public:
    RectF() {}

    RectF(float minX, float maxX, float minY, float maxY)
    {
        mMinX = minX;
        mMaxX = maxX;
        mMinY = minY;
        mMaxY = maxY;
    }

    RectF(Vector2i a, Vector2i b)
    {
        mMinX = min(a.x, b.x);
        mMaxX = max(a.x, b.x);
        mMinY = min(a.y, b.y);
        mMaxY = max(a.y, b.y);
    }

    bool isNull() const
    {
        return minX() > maxX() || minY() > maxY();
    }

    bool isValid() const
    {
        return !isNull();
    }

    bool isImaginary() const
    {
        return isNull();
    }

    float minX() const
    {
        return mMinX;
    }

    float maxX() const
    {
        return mMaxX;
    }

    float minY() const
    {
        return mMinY;
    }

    float maxY() const
    {
        return mMaxY;
    }

    Vector2i size() const
    {
        return Vector2i(maxX() - minX() + 1, maxY() - minY() + 1);
    }

    float area() const
    {
        return size().area();
    }

    bool contains(Vector2i point) const
    {
        return point.x >= minX() && point.x <= maxX() && point.y >= minY() && point.y <= maxY();
    }

    RectF unite(RectF rhs) const
    {
        return RectF(
                    min(minX(), rhs.minX()),
                    max(maxX(), rhs.maxX()),
                    min(minY(), rhs.minY()),
                    max(maxY(), rhs.maxY()));
    }

    RectF intersect(RectF rhs) const
    {
        return RectF(
                    max(minX(), rhs.minX()),
                    min(maxX(), rhs.maxX()),
                    max(minY(), rhs.minY()),
                    min(maxY(), rhs.maxY()));
    }

    bool intersects(RectF rhs) const
    {
        return intersect(rhs).isValid();
    }

    bool contains(RectF inner) const;

private:
    float mMinX;
    float mMaxX;
    float mMinY;
    float mMaxY;
};

bool operator==(RectF a, RectF b)
{
    return a.minX() == b.minX() && a.maxX() == b.maxX() && a.minY() == b.minY() && a.maxY() == b.maxY();
}

bool RectF::contains(RectF inner) const
{
    return intersect(inner) == inner;
}

namespace std
{
    template <> struct hash<Vector2i>
    {
        size_t operator()(Vector2i key) const
        {
            return (key.x << 16) + key.y;
        }
    };
}



#endif // GEOMETRY_H_INCLUDED

