#include <iostream>

#include "vec3.h"
#include "vec3_utility.h"
#include "ray.h"


double hit_sphere(const point3& center, double radius, const ray& r) 
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-half_b - sqrt(discriminant)) / a;
	}
}

color ray_color(const ray& r)
{
	point3 sphereCenter(0,0,-1);
	double t = hit_sphere(sphereCenter, 0.5, r);
	if(t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - sphereCenter);
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0,1.0,1.0) + t * color(0.5,0.7,1.0);
}

int main() 
{
	// Canvas
	const double aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);


	// Camera
	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point3 origin = point3(0.0, 0.0,0.0);
	vec3 horizontal = vec3(viewport_width,0,0);
	vec3 vertical = vec3(0,viewport_height,0);
	vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length);


	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for (int j = image_height - 1; j >= 0; --j) 
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) 
		{
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);

			ray r(origin,lower_left_corner + u * horizontal + v * vertical - origin);

			color pixel_color = ray_color(r);//(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";
}