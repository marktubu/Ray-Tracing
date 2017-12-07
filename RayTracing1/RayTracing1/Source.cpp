#include <iostream>
#include <fstream>

#include "ray.h"

using namespace std;


vec3 center = vec3(0.0, 0.0, -1.0);
float radius = 0.5;

float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = oc.dot(r.direction(), r.direction());
	float b = 2.0 * oc.dot(oc, r.direction());
	float c = oc.dot(oc, oc) - radius * radius;

	float discriminant = b*b - 4 * a*c;

	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0*a);
	}
}

vec3 color(ray& r)
{
	float t1 = hit_sphere(center, radius, r);
	if (t1 > 0.0)
	{
		vec3 N = unit_vector(r.point_at_parameter(t1) - center);
		std::cout << N << endl;
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 200;
	int ny = 100;

	ofstream outfile("mytest.txt", ios_base::out);
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 origin = vec3(0, 0, 0);
	vec3 horizontal = vec3(4.0, 0.0, 0.0);
	vec3 verticle = vec3(0.0, 2.0, 0.0);
	vec3 lower_left_corner = vec3(-2.0, -1.0, -1.0);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 u = float(i) / float(nx) * horizontal;
			vec3 v = float(j) / float(ny) * verticle;

			ray r = ray(origin, lower_left_corner + u + v);
			vec3 c = color(r);
			int ir = int(255.99*c[0]);
			int ig = int(255.99*c[1]);
			int ib = int(255.99*c[2]);

			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}
}