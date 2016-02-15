#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "common.h"

struct Vector2i
{
    int x;
    int y;

    Vector2i() {}

#ifdef QT_VERSION
    Vector2i(QPoint point)
    {
        x = point.x();
        y = point.y();
    }
#endif // QT_VERSION

    Vector2i(int n)
    {
        x = n;
        y = n;
    }

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

#ifdef QT_VERSION
    Vector2f(QPointF point)
    {
        x = point.x();
        y = point.y();
    }
#endif // QT_VERSION

    Vector2f(float n)
    {
        x = n;
        y = n;
    }

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

struct RectF;

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
        xMin = min(a.x, b.x);
        xMax = max(a.x, b.x);
        yMin = min(a.y, b.y);
        yMax = max(a.y, b.y);
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
        return xMin == xMax && yMin == yMax;
    }

    bool isValid() const
    {
        return xMin <= xMax && yMin <= yMax;
    }

    bool isImaginary() const
    {
        return !isValid();
    }

    RectIFillIterator begin() const
    {
        return RectIFillIterator(this, xMin, yMin);
    }

    RectIFillIterator end() const
    {
        return RectIFillIterator(this, xMin, yMax);
    }

    Vector2i lb()
    {
        return Vector2i(xMin, yMin);
    }

    Vector2i lu()
    {
        return Vector2i(xMin, yMax);
    }

    Vector2i rb()
    {
        return Vector2i(xMax, yMin);
    }

    Vector2i ru()
    {
        return Vector2i(xMax, yMax);
    }

    Vector2i size() const
    {
        return Vector2i(xMax - xMin, yMax - yMin);
    }

    int area() const
    {
        return size().area();
    }

    bool contains(int x, int y) const
    {
        return x >= xMin && x < xMax && y >= yMin && y < yMax;
    }

    bool contains(Vector2i point) const
    {
        return contains(point.x, point.y);
    }

    RectI unite(RectI rhs) const
    {
        return RectI(
                    min(xMin, rhs.xMin),
                    max(xMax, rhs.xMax),
                    min(yMin, rhs.yMin),
                    max(yMax, rhs.yMax));
    }

    RectI intersect(RectI rhs) const
    {
        RectI rect = RectI(
                    max(xMin, rhs.xMin),
                    min(xMax, rhs.xMax),
                    max(yMin, rhs.yMin),
                    min(yMax, rhs.yMax));

        if (rect.isValid())
            return rect;
        return RectI(0, 0, 0, 0);
    }

    bool intersects(RectI rhs) const
    {
        return !intersect(rhs).isNull();
    }

    bool contains(RectI inner) const;
};

struct RectF
{
    float xMin;
    float xMax;
    float yMin;
    float yMax;

    RectF() {}

    RectF(RectI rect);

    RectF(float xMin, float xMax, float yMin, float yMax):
        xMin(xMin),
        xMax(xMax),
        yMin(yMin),
        yMax(yMax)
    {}

    RectF(Vector2i a, Vector2i b)
    {
        xMin = min(a.x, b.x);
        xMax = max(a.x, b.x);
        yMin = min(a.y, b.y);
        yMax = max(a.y, b.y);
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
        return xMin == xMax && yMin == yMax;
    }

    bool isValid() const
    {
        return xMin <= xMax && yMin <= yMax;
    }

    bool isImaginary() const
    {
        return !isValid();
    }

    Vector2f lb()
    {
        return Vector2f(xMin, yMin);
    }

    Vector2f lu()
    {
        return Vector2f(xMin, yMax);
    }

    Vector2f rb()
    {
        return Vector2f(xMax, yMin);
    }

    Vector2f ru()
    {
        return Vector2f(xMax, yMax);
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
                    min(xMin, rhs.xMin),
                    max(xMax, rhs.xMax),
                    min(yMin, rhs.yMin),
                    max(yMax, rhs.yMax));
    }

    RectF intersect(RectF rhs) const
    {
        RectF rect = RectF(
                    max(xMin, rhs.xMin),
                    min(xMax, rhs.xMax),
                    max(yMin, rhs.yMin),
                    min(yMax, rhs.yMax));

        if (rect.isValid())
            return rect;
        return RectF(0, 0, 0, 0);
    }

    bool intersects(RectF rhs) const
    {
        return !intersect(rhs).isNull();
    }

    bool contains(RectF inner) const;

    RectI toInt() const
    {
        return RectI(floor(xMin), ceil(xMax), floor(yMin), ceil(yMax));
    }
};

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


bool operator==(Vector2i a, Vector2i b);
bool operator==(Vector2f a, Vector2f b);
bool operator==(RectI a, RectI b);
bool operator==(RectF a, RectF b);

RectI operator+(RectI a, float b);
RectI operator-(RectI a, float b);
RectI operator*(RectI a, float b);
RectI operator/(RectI a, float b);

RectF operator+(RectF a, float b);
RectF operator-(RectF a, float b);
RectF operator*(RectF a, float b);
RectF operator/(RectF a, float b);

RectI operator+(RectI a, Vector2i b);
RectI operator-(RectI a, Vector2i b);
RectI operator*(RectI a, Vector2i b);
RectI operator/(RectI a, Vector2i b);

RectF operator+(RectF a, Vector2f b);
RectF operator-(RectF a, Vector2f b);
RectF operator*(RectF a, Vector2f b);
RectF operator/(RectF a, Vector2f b);

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

Vector2f operator+(Vector2i a, float b);
Vector2f operator-(Vector2i a, float b);
Vector2f operator*(Vector2i a, float b);
Vector2f operator/(Vector2i a, float b);

Vector2f operator+(Vector2f a, float b);
Vector2f operator-(Vector2f a, float b);
Vector2f operator*(Vector2f a, float b);
Vector2f operator/(Vector2f a, float b);


#endif // GEOMETRY_H_INCLUDED

