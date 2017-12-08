#include <iostream>
#include <fstream>
#include <limits>

#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"


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

vec3 color(ray& r, hitable_list* list)
{
	hit_record rec;
	if (list->hit(r, 0.0, numeric_limits<float>().max(), rec))
	{
		vec3 N = unit_vector(rec.normal);
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
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

	hitable *list[2];
	list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100.0);

	hitable_list* hit_list = new hitable_list(list, 2);


	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col = vec3(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				/*ÿ�����ص��������ns�Σ��˴�ns=100*/
				float random = rand() % (100) / (float)(100);
				/*generate a random in range[0,1]��ÿ�����ص�����������������ĵ�Ϊ�����������Ϊ1�ķ�Χ�����ĵ�λ��+random�൱����������ص�������ڲ��� */
				float u = float(i + random) / float(nx);
				float v = float(j + random) / float(ny);
				ray r = cam.get_ray(u, v);
				/*���������ص�����������������ɫֵ�������Ѿ�����ɫ��ú�����װ��һ��������camera�����࣬���������������Ĵ���*/

				col += color(r, hit_list);
				/*��������ص����������ns��������������ɫֵ�ۼ�*/
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