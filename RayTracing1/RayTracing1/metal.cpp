#include "metal.h"


vec3 reflect(const vec3& v, const vec3& n) {
	/*获取镜面反射的反射光线的方向向量。具体计算，后面解释*/
	vec3 vp;
	return v - 2 * vp.dot(v, n)*n;
}

bool metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected);
	attenuation = albedo;
	return (reflected.dot(scattered.direction(), rec.normal) > 0);
}