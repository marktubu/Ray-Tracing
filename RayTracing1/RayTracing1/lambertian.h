#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class lambertian : public material
{
public:
	lambertian(vec3 v) { albedo = v; }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const;
	vec3 albedo;
};


#endif 
