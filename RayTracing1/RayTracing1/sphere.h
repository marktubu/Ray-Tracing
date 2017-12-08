#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material* m) { center = cen; radius = r; ma = m; }

	virtual bool hit(ray& r, float t_min, float t_max, hit_record& rec) const;

	vec3 center;
	float radius;
	material* ma;
};

#endif