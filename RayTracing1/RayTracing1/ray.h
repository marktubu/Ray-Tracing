#ifndef RAY_H
#define RAY_H

#include "vec3.h"

#define M_PI 3.14

class ray
{
public:
	ray(){}
	ray(const vec3& a, const vec3& b) { A = a; B = b; count = 0; }
	vec3 origin()const { return A; }
	vec3 direction() const { return B; }
	vec3 point_at_parameter(float t) { return A + t*B; }

	vec3 A;
	vec3 B;
	int count;

};


#endif
