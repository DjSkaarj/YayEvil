#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <algorithm>

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


bool operator==(Vector2i a, Vector2i b);
bool operator==(Vector2f a, Vector2f b);
Vector2i operator+(Vector2i a, Vector2i b);
Vector2i operator-(Vector2i a, Vector2i b);
Vector2i operator*(Vector2i a, Vector2i b);
Vector2i operator/(Vector2i a, Vector2i b);
Vector2i operator%(Vector2i a, Vector2i b);
Vector2f operator+(Vector2f a, Vector2f b);
Vector2f operator-(Vector2f a, Vector2f b);
Vector2f operator*(Vector2f a, Vector2f b);
Vector2f operator/(Vector2f a, Vector2f b);

Vector2f operator+(Vector2i a, Vector2f b);
Vector2f operator-(Vector2i a, Vector2f b);
Vector2f operator*(Vector2i a, Vector2f b);
Vector2f operator/(Vector2i a, Vector2f b);

struct RectI;

struct RectIFillIterator
{
public:
    RectIFillIterator(const RectI *rect, int x, int y)
    {
        mRect = rect;
        mX = x;
        mY = y;
    }

    Vector2i operator*()
    {
        return Vector2i(mX, mY);
    }

    void operator++();

    friend bool operator!=(const RectIFillIterator &a, const RectIFillIterator &b);

private:
    const RectI *mRect;
    int mX;
    int mY;
};

bool operator!=(const RectIFillIterator &a, const RectIFillIterator &b);

struct RectI
{
public:
    int xMin;
    int xMax;
    int yMin;
    int yMax;

    RectI() {}

    RectI(int xMin, int xMax, int yMin, int yMax):
        xMin(xMin),
        xMax(xMax),
        yMin(yMin),
        yMax(yMax)
    {}

    RectI(Vector2i a, Vector2i b)
    {
        xMin = std::min(a.x, b.x);
        xMax = std::max(a.x, b.x);
        yMin = std::min(a.y, b.y);
        yMax = std::max(a.y, b.y);
    }

    RectI(int width, int height)
    {
        xMin = 0;
        xMax = width;
        yMin = 0;
        yMax = height;
    }

    RectI(Vector2i size)
    {
        xMin = 0;
        xMax = size.x;
        yMin = 0;
        yMax = size.y;
    }

    bool isNull() const
    {
        return xMin >= xMax || yMin >= yMax;
    }

    bool isValid() const
    {
        return !isNull();
    }

    bool isImaginary() const
    {
        return isNull();
    }

    RectIFillIterator begin() const
    {
        return RectIFillIterator(this, xMin, yMin);
    }

    RectIFillIterator end() const
    {
        return RectIFillIterator(this, xMin, yMax);
    }

    Vector2i size() const
    {
        return Vector2i(xMax - xMin, yMax - yMin);
    }

    int area() const
    {
        return size().area();
    }

    bool contains(Vector2i point) const
    {
        return point.x >= xMin && point.x < xMax && point.y >= yMin && point.y < yMax;
    }

    RectI unite(RectI rhs) const
    {
        return RectI(
                    std::min(xMin, rhs.xMin),
                    std::max(xMax, rhs.xMax),
                    std::min(yMin, rhs.yMin),
                    std::max(yMax, rhs.yMax));
    }

    RectI intersect(RectI rhs) const
    {
        return RectI(
                    std::max(xMin, rhs.xMin),
                    std::min(xMax, rhs.xMax),
                    std::max(yMin, rhs.yMin),
                    std::min(yMax, rhs.yMax));
    }

    bool intersects(RectI rhs) const
    {
        return intersect(rhs).isValid();
    }

    bool contains(RectI inner) const;
};

bool operator==(RectI a, RectI b);

struct RectF
{
    float xMin;
    float xMax;
    float yMin;
    float yMax;

    RectF() {}

    RectF(float xMin, float xMax, float yMin, float yMax):
        xMin(xMin),
        xMax(xMax),
        yMin(yMin),
        yMax(yMax)
    {}

    RectF(Vector2i a, Vector2i b)
    {
        xMin = std::min(a.x, b.x);
        xMax = std::max(a.x, b.x);
        yMin = std::min(a.y, b.y);
        yMax = std::max(a.y, b.y);
    }

    RectF(float width, float height)
    {
        xMin = 0;
        xMax = width;
        yMin = 0;
        yMax = height;
    }

    RectF(Vector2f size)
    {
        xMin = 0;
        xMax = size.x;
        yMin = 0;
        yMax = size.y;
    }

    bool isNull() const
    {
        return xMin >= xMax || yMin >= yMax;
    }

    bool isValid() const
    {
        return !isNull();
    }

    bool isImaginary() const
    {
        return isNull();
    }

    Vector2f size() const
    {
        return Vector2f(xMax - xMin, yMax - yMin);
    }

    float area() const
    {
        return size().area();
    }

    bool contains(Vector2i point) const
    {
        return point.x >= xMin && point.x < xMax && point.y >= yMin && point.y < yMax;
    }

    RectF unite(RectF rhs) const
    {
        return RectF(
                    std::min(xMin, rhs.xMin),
                    std::max(xMax, rhs.xMax),
                    std::min(yMin, rhs.yMin),
                    std::max(yMax, rhs.yMax));
    }

    RectF intersect(RectF rhs) const
    {
        return RectF(
                    std::max(xMin, rhs.xMin),
                    std::min(xMax, rhs.xMax),
                    std::max(yMin, rhs.yMin),
                    std::min(yMax, rhs.yMax));
    }

    bool intersects(RectF rhs) const
    {
        return intersect(rhs).isValid();
    }

    bool contains(RectF inner) const;
};

bool operator==(RectF a, RectF b);

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

