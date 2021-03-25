#ifndef vector2_hpp
#define vector2_hpp

#include <iostream> // For IO operations
#include <cmath>    // For sqrt() function

template<typename T>
class vector2
{
public:
    T x; // x component of the 2 dimensional vector
    T y; // y component of the 2 dimensional vector

    // (1) Addition in place
    vector2<T>& operator+=(vector2<T> const& v){
        x += v.x;
        y += v.y;
        return *this;
    }

    // (2) Substraction in place
    vector2<T>& operator-=(vector2<T> const& v){
        x -= v.x;
        y -= v.y;
        return *this;
    }

    // (3) Multiplication with scalar in place
    vector2<T>& operator*=(T const& a){
        x *= a;
        y *= a;
        return *this;
    }

    // (4) Division with scalar in place
    vector2<T>& operator/=(T const& a){
        x /= a;
        y /= a;
        return *this;
    }

};

// (1) Addition of two vectors and returning with result
template<typename T>
vector2<T> operator+(vector2<T> const& u, vector2<T> const& v){
    return vector2<T>{u.x + v.x, u.y + v.y};
}

// (2) Substraction of two vectors and returning with result
template<typename T>
vector2<T> operator-(vector2<T> const& u, vector2<T> const& v){
    return vector2<T>{u.x - v.x, u.y - v.y};
}

// (3.1) Multiplication of a vector with a scalar value from right and returning with result
template<typename T>
vector2<T> operator*(vector2<T> const& u, T const& c){
    return vector2<T>{u.x * c, u.y * c};
}

// (3.2) Multiplication of a vector with a scalar value from left and returning with result
template<typename T>
vector2<T> operator*(T const& c, vector2<T> const& u){
    return vector2<T>{c * u.x, c* u.y};
}

// (4) Division of a vector with a scalar value and returning with result
template<typename T>
vector2<T> operator/(vector2<T> const& u, T const& c){
    return vector2<T>{u.x / c, u.y / c};
}

// (5.1) Lenght of a given vector
template<typename T>
double length(vector2<T> const& u){
    return {sqrt(u.x * u.x + u.y * u.y)};
}

// (5.2) Square of the lenght of a given vector
template<typename T>
double sqlength(vector2<T> const& u){
    return double(u.x * u.x + u.y * u.y);
}

// (6) Dot product of two vectors and returning with result
template<typename T>
T dot(vector2<T> const& u, vector2<T> const& v){
    return {u.x * v.x + u.y * v.y};
}

// (7) Normalise a vector and returning with result
template<typename T>
vector2<double> normalise(vector2<T> const& u){
    return vector2<double>{u.x / length(u), u.y / length(u)};
}

// (8) Write out the components of the vector to standard output
template<typename T>
std::ostream& operator<<(std::ostream& o, vector2<T> const& u){
    o << "(" << u.x << ", " << u.y << ")";
    return o;
}

// (9) Read vector components from standard input
template<typename T>
std::istream& operator>>(std::istream& i, vector2<T>& u){
    i >> u.x;
    i >> u.y;
    return i;
}

#endif /* vector2_hpp */