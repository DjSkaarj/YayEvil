#include "common.h"

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
    return a.mY != a.mRect->yMax;
}
