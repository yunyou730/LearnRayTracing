#pragma once
#include "vec3.h"

#include <cmath>
#include <limits>
#include <memory>

// vec3 ext
std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(vec3 v, double t);
double dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(vec3 v);

// write color
void write_color(std::ostream& out, color pixel_color);

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;


// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
double degrees_to_radians(double degrees);

