#ifndef DIELECTIC_H
#define DIELECTIC_H

#include "material.h"
#include "metal.h"

class dielectic : public material
{
public:
	dielectic(float ri):ref_idx(ri){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const;
	float ref_idx;
};

#endif