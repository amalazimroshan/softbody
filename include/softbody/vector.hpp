#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace softbody {

// Forward declarations for friend functions
template <typename T, std::size_t N>
class Vector;

template <typename T, std::size_t N>
Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs);

template <typename T, std::size_t N>
Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs);

template <typename T, std::size_t N>
Vector<T, N> operator*(const Vector<T, N>& lhs, const T& scalar);

template <typename T, std::size_t N>
Vector<T, N> operator/(const Vector<T, N>& lhs, const T& scalar);

// Base template
template <typename T, std::size_t N>
class Vector {
 public:
  using scalar_type = T;
  static constexpr std::size_t dimension = N;

  std::array<T, N> coords;

  // Default constructor
  Vector() : coords{} {}

  // Initializer list constructor
  Vector(std::initializer_list<T> list) {
    if (list.size() != N) {
      throw std::invalid_argument(
          "Initializer list size must match vector dimensions.");
    }
    std::copy(list.begin(), list.end(), coords.begin());
  }

  // Variadic constructor
  template <typename... Args>
    requires(sizeof...(Args) == N)
  explicit Vector(Args&&... args)
      : coords{static_cast<T>(std::forward<Args>(args))...} {}

  // Accessors
  T& operator[](std::size_t i) { return coords[i]; }
  const T& operator[](std::size_t i) const { return coords[i]; }

  // Arithmetic operations
  Vector& operator+=(const Vector& v) {
    for (std::size_t i = 0; i < N; ++i) coords[i] += v[i];
    return *this;
  }

  Vector& operator-=(const Vector& v) {
    for (std::size_t i = 0; i < N; ++i) coords[i] -= v[i];
    return *this;
  }

  Vector& operator*=(const T& scalar) {
    for (std::size_t i = 0; i < N; ++i) coords[i] *= scalar;
    return *this;
  }

  Vector& operator/=(const T& scalar) {
    if (scalar == T(0)) throw std::runtime_error("Division by zero");
    for (std::size_t i = 0; i < N; ++i) coords[i] /= scalar;
    return *this;
  }

  // Friend operators
  friend Vector operator+ <>(const Vector& lhs, const Vector& rhs);
  friend Vector operator- <>(const Vector& lhs, const Vector& rhs);
  friend Vector operator* <>(const Vector& lhs, const T& scalar);
  friend Vector operator/ <>(const Vector& lhs, const T& scalar);

  // Static methods
  static Vector zero() { return Vector(); }
};

// Specialization for 2D
template <typename T>
class Vector<T, 2> {
 public:
  T x, y;

  Vector() : x(T(0)), y(T(0)) {}
  Vector(T x_, T y_) : x(x_), y(y_) {}
  Vector(std::initializer_list<T> list) {
    if (list.size() != 2) {
      throw std::invalid_argument(
          "Initializer list size must match vector dimensions.");
    }
    auto it = list.begin();
    x = *it++;
    y = *it;
  }

  T& operator[](std::size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    throw std::out_of_range("Index out of range for 2D vector");
  }

  const T& operator[](std::size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    throw std::out_of_range("Index out of range for 2D vector");
  }

  Vector& operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  Vector& operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  Vector& operator*=(const T& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vector& operator/=(const T& scalar) {
    if (scalar == T(0)) throw std::runtime_error("Division by zero");
    x /= scalar;
    y /= scalar;
    return *this;
  }
};

// Specialization for 3D
template <typename T>
class Vector<T, 3> {
 public:
  T x, y, z;

  Vector() : x(T(0)), y(T(0)), z(T(0)) {}
  Vector(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
  Vector(std::initializer_list<T> list) {
    if (list.size() != 3) {
      throw std::invalid_argument(
          "Initializer list size must match vector dimensions.");
    }
    auto it = list.begin();
    x = *it++;
    y = *it++;
    z = *it;
  }

  T& operator[](std::size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    throw std::out_of_range("Index out of range for 3D vector");
  }

  const T& operator[](std::size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    throw std::out_of_range("Index out of range for 3D vector");
  }

  Vector& operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  Vector& operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  Vector& operator*=(const T& scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
  }

  Vector& operator/=(const T& scalar) {
    if (scalar == T(0)) throw std::runtime_error("Division by zero");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
  }
};

// Specialization for 4D
template <typename T>
class Vector<T, 4> {
 public:
  T x, y, z, w;

  Vector() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
  Vector(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}
  Vector(std::initializer_list<T> list) {
    if (list.size() != 4) {
      throw std::invalid_argument(
          "Initializer list size must match vector dimensions.");
    }
    auto it = list.begin();
    x = *it++;
    y = *it++;
    z = *it++;
    w = *it;
  }

  T& operator[](std::size_t i) {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    if (i == 3) return w;
    throw std::out_of_range("Index out of range for 4D vector");
  }

  const T& operator[](std::size_t i) const {
    if (i == 0) return x;
    if (i == 1) return y;
    if (i == 2) return z;
    if (i == 3) return w;
    throw std::out_of_range("Index out of range for 4D vector");
  }

  Vector& operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  Vector& operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  Vector& operator*=(const T& scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
  }

  Vector& operator/=(const T& scalar) {
    if (scalar == T(0)) throw std::runtime_error("Division by zero");
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
  }
};

// Non-member operators
template <typename T, std::size_t N>
Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
  Vector<T, N> result = lhs;
  result += rhs;
  return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
  Vector<T, N> result = lhs;
  result -= rhs;
  return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator*(const Vector<T, N>& lhs, const T& scalar) {
  Vector<T, N> result = lhs;
  result *= scalar;
  return result;
}

template <typename T, std::size_t N>
Vector<T, N> operator/(const Vector<T, N>& lhs, const T& scalar) {
  Vector<T, N> result = lhs;
  result /= scalar;
  return result;
}

// Dot product
template <typename T, std::size_t N>
T dot(const Vector<T, N>& v1, const Vector<T, N>& v2) {
  T result = T(0);
  for (std::size_t i = 0; i < N; ++i) result += v1[i] * v2[i];
  return result;
}

// Magnitude (length)
template <typename T, std::size_t N>
T magnitude(const Vector<T, N>& v) {
  return std::sqrt(dot(v, v));
}

// Normalize
template <typename T, std::size_t N>
Vector<T, N> normalize(const Vector<T, N>& v) {
  T mag = magnitude(v);
  if (mag == T(0)) throw std::runtime_error("Cannot normalize zero vector");
  return v / mag;
}

// Stream operator
template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<T, N>& v) {
  os << "(";
  for (std::size_t i = 0; i < N; ++i) {
    os << v[i];
    if (i < N - 1) os << ", ";
  }
  os << ")";
  return os;
}
}