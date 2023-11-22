// This ensures the header is only included once during compilation to prevent redefinition errors.
#pragma once

// Including necessary standard and SFML header files
#include <SFML/System.hpp> // For SFML's System module
#include <cmath> // For standard math functions
#include <iostream> // For input/output streaming
#include <vector> // For the vector container

// Extending the sf namespace which is part of the SFML library
namespace sf {
    // Define a new type Vector2ul using size_t as the type for both components
    typedef Vector2<size_t> Vector2ul;

    // Template function to calculate the length (magnitude) of a vector
    template <typename T>
    double length(const Vector2<T>& v) {
        return sqrt(static_cast<double>(v.x * v.x + v.y * v.y));
    }

    // Template function to return a normalized (unit length) vector
    template <typename T>
    Vector2<T> normalize(const Vector2<T>& v) {
        Vector2<T> vector;
        double l = length(v);
        if (l != 0) {
            vector.x = static_cast<T>(v.x / l);
            vector.y = static_cast<T>(v.y / l);
        }
        return vector;
    }

    // Template function to cast a vector from one type to another
    template <typename T, typename U>
    Vector2<T> Vcast(const Vector2<U>& v) {
        return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));
    };

    // Function to convert degrees to radians
    static double deg2rad(double degrees) {
        return degrees * 3.14159265359 / 180.0;
    }

    // Template function to rotate a vector by a given angle in degrees
    template <typename T>
    Vector2<T> rotate(const Vector2<T>& v, const double degrees) {
        const double theta = deg2rad(degrees);
        const double cs = cos(theta);
        const double sn = sin(theta);
        return { (T)(v.x * cs - v.y * sn), (T)(v.x * sn + v.y * cs) };
    }

    // Template to enable output streaming of vectors using cout
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
        os << '(' << v.x << ',' << v.y << ')';
        return os;
    }
}
