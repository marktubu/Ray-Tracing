#include "camera.h"

vec3 random_in_unit_disk()
{
	vec3 p;
	do{
		p = 2.0*vec3(rand()%(100)/(float)(100), rand()%(100)/(float)(100),0) - vec3(1,1,0);
	}while(p.dot(p,p)>=1.0);

	return p;
}