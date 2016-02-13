#include "geometry.h"

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


Vector2f operator+(Vector2i a, float b)
{
    return Vector2f(a.x + b, a.y + b);
}

Vector2f operator-(Vector2i a, float b)
{
    return Vector2f(a.x - b, a.y - b);
}

Vector2f operator*(Vector2i a, float b)
{
    return Vector2f(a.x * b, a.y * b);
}

Vector2f operator/(Vector2i a, float b)
{
    return Vector2f(a.x / b, a.y / b);
}


Vector2f operator+(Vector2f a, float b)
{
    return Vector2f(a.x + b, a.y + b);
}

Vector2f operator-(Vector2f a, float b)
{
    return Vector2f(a.x - b, a.y - b);
}

Vector2f operator*(Vector2f a, float b)
{
    return Vector2f(a.x * b, a.y * b);
}

Vector2f operator/(Vector2f a, float b)
{
    return Vector2f(a.x / b, a.y / b);
}


bool operator==(RectI a, RectI b)
{
    return a.xMin == b.xMin && a.xMax == b.xMax && a.yMin == b.yMin && a.yMax == b.yMax;
}

bool RectI::contains(RectI inner) const
{
    return intersect(inner) == inner;
}

bool operator==(RectF a, RectF b)
{
    return a.xMin == b.xMin && a.xMax == b.xMax && a.yMin == b.yMin && a.yMax == b.yMax;
}

bool RectF::contains(RectF inner) const
{
    return intersect(inner) == inner;
}


void RectIFillIterator::operator++()
{
    mX++;
    if (mX == mRect->xMax)
    {
        mX = 0;
        mY++;
    }
}

bool operator!=(const RectIFillIterator &a, const RectIFillIterator &b)
{
    UNUSED(b);
    return a.mY != a.mRect->yMax;
}

RectF::RectF(RectI rect)
{
    xMin = rect.xMin;
    xMax = rect.xMax;
    yMin = rect.yMin;
    yMax = rect.yMax;
}

RectI operator+(RectI a, float b)
{
    return RectI(a.xMin + b, a.xMax + b, a.yMin + b, a.yMax + b);
}

RectI operator-(RectI a, float b)
{
    return RectI(a.xMin - b, a.xMax - b, a.yMin - b, a.yMax - b);
}

RectI operator*(RectI a, float b)
{
    return RectI(a.xMin * b, a.xMax * b, a.yMin * b, a.yMax * b);
}

RectI operator/(RectI a, float b)
{
    return RectI(a.xMin / b, a.xMax / b, a.yMin / b, a.yMax / b);
}


RectF operator+(RectF a, float b)
{
    return RectF(a.xMin + b, a.xMax + b, a.yMin + b, a.yMax + b);
}

RectF operator-(RectF a, float b)
{
    return RectF(a.xMin - b, a.xMax - b, a.yMin - b, a.yMax - b);
}

RectF operator*(RectF a, float b)
{
    return RectF(a.xMin * b, a.xMax * b, a.yMin * b, a.yMax * b);
}

RectF operator/(RectF a, float b)
{
    return RectF(a.xMin / b, a.xMax / b, a.yMin / b, a.yMax / b);
}


RectI operator+(RectI a, Vector2f b)
{
    return RectI(a.xMin + b.x, a.xMax + b.x, a.yMin + b.y, a.yMax + b.y);
}

RectI operator-(RectI a, Vector2f b)
{
    return RectI(a.xMin - b.x, a.xMax - b.x, a.yMin - b.y, a.yMax - b.y);
}

RectI operator*(RectI a, Vector2f b)
{
    return RectI(a.xMin * b.x, a.xMax * b.x, a.yMin * b.y, a.yMax * b.y);
}

RectI operator/(RectI a, Vector2f b)
{
    return RectI(a.xMin / b.x, a.xMax / b.x, a.yMin / b.y, a.yMax / b.y);
}


RectF operator+(RectF a, Vector2f b)
{
    return RectF(a.xMin + b.x, a.xMax + b.x, a.yMin + b.y, a.yMax + b.y);
}

RectF operator-(RectF a, Vector2f b)
{
    return RectF(a.xMin - b.x, a.xMax - b.x, a.yMin - b.y, a.yMax - b.y);
}

RectF operator*(RectF a, Vector2f b)
{
    return RectF(a.xMin * b.x, a.xMax * b.x, a.yMin * b.y, a.yMax * b.y);
}

RectF operator/(RectF a, Vector2f b)
{
    return RectF(a.xMin / b.x, a.xMax / b.x, a.yMin / b.y, a.yMax / b.y);
}

RectF operator-(RectF a, Vector2f b);
RectF operator*(RectF a, Vector2f b);
RectF operator/(RectF a, Vector2f b);
