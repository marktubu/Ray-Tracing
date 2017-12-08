#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "hitable.h"

class hitable_list : public hitable{
public:
	hitable_list(){}
	hitable_list(hitable **l, int size) { list = l; listsize = size; }

	virtual bool hit(ray& r, float t_min, float t_max, hit_record& rec) const;
	
	hitable **list;
	int listsize;
};

#endif