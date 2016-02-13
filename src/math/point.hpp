#pragma once

template <typename T>
class Point {
public:
    Point(T x = T{}, T y = T{});

    T xpos() const;

    T ypos() const;

    T& xpos();

    T& ypos();    

private:
    T _xpos;
    T _ypos;
};

using Point2i = Point<int>;

using Point2f = Point<float>;

template <typename T>
Point<T>::Point(T x, T y)
    : _xpos(x),
      _ypos(y)
{}

template <typename T>
T Point<T>::xpos() const
{
    return _xpos;
}

template <typename T>
T Point<T>::ypos() const
{
    return _ypos;
}

template <typename T>
T& Point<T>::xpos()
{
    return _xpos;
}

template <typename T>
T& Point<T>::ypos()
{
    return _ypos;
}
