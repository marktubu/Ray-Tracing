#include <iostream>
#include <fstream>
#include <limits>

#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"


using namespace std;


vec3 center = vec3(0.0, 0.0, -1.0);
float radius = 0.5;

int MAX_REFLECTION_COUNT = 10;


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

vec3 color(ray& r, hitable_list* list, int depth)
{
	hit_record rec;
	if (list->hit(r, 0.001, numeric_limits<float>::max(), rec))
	{
		r.count++;
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation*color(scattered, list, depth + 1);
		}
		else 
		{
			return vec3(0, 0, 0);
		}
	}
	
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main()
{
	camera cam;
	int ns = 100;
	int nx = 200;
	int ny = 100;

	ofstream outfile("mytest.txt", ios_base::out);
	outfile << "P3\n" << nx << " " << ny << "\n255\n";

	hitable *list[4];
	//list[2] = new sphere(vec3(0.0, 0.5, -1.0), 0.25);
	//list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5, new lambertian(vec3(1,1,1)));
	//list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0, new metal(vec3(1, 1, 1)));
	
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));

	hitable_list* hit_list = new hitable_list(list, 4);


	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col = vec3(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				/*每个像素点区域采样ns次，此处ns=100*/
				float random = rand() % (100) / (float)(100);
				/*generate a random in range[0,1]。每个像素点的区域是以像素中心点为中心向外距离为1的范围。中心点位置+random相当于在这个像素点的区域内采样 */
				float u = float(i + random) / float(nx);
				float v = float(j + random) / float(ny);
				ray r = cam.get_ray(u, v);
				/*获得这个像素点区域随机采样点的颜色值。我们已经将颜色获得函数封装成一个叫做“camera”的类，后续会贴出这个类的代码*/

				col += color(r, hit_list, 0);
				/*将这个像素点区域的所有ns个随机采样点的颜色值累加*/
			}
			col /= float(ns);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			outfile << ir << " " << ig << " " << ib << "\n";
		}
	}

	//system("pause");
}