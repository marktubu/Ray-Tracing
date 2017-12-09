#include "dielectic.h"


//反射
vec3 reflect(const vec3& v, const vec3& n) {
	/*»ñÈ¡¾µÃæ·´ÉäµÄ·´Éä¹âÏßµÄ·½ÏòÏòÁ¿¡£¾ßÌå¼ÆËã£¬ºóÃæ½âÊÍ*/
	vec3 vp;
	return v - 2 * vp.dot(v, n)*n;
}


// 折射
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv,n);
	float discriminat = 1.0 - ni_over_nt * ni_over_nt *(1-dt*dt);
	if(discriminat > 0)
	{
		refracted = ni_over_nt*(uv-n*dt) - n*sqrt(discriminat);
		return true;
	}
	else
	{
		return false;
	}
}

//实现 schlick's approximation
float schlick(float cosine, float ref_idx)
{
	float r0 = (1-ref_idx)/(1+ref_idx);
	r0=r0*r0;
	return r0 +(1-r0)*pow((1-cosine), 5);
}

bool dielectic::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
{
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0,1.0,1.0);
	vec3 refracted;
	float reflect_prob;
	float cosine;

	if(dot(r_in.direction(), rec.normal) > 0)
	{
		outward_normal = -rec.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx*dot(r_in.direction(), rec.normal)/r_in.direction().length();
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0/ref_idx;
		cosine = -dot(r_in.direction(), rec.normal)/r_in.direction().length();
	}

	if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
	{
		reflect_prob = schlick(cosine, ref_idx);
	}
	else
	{
	 	reflect_prob = 1.0;
	}

	if ((rand()%(100)/(float)(100))< reflect_prob) {
		/*产生一个（0，1）的随机数，如果随机数小于反射系数，则设置为反射光线，反之，设置为折射光线。
		也就是只有反射光线或折射光线中的一个咯，为什么？不是说好反射光线和折射光线都有吗？
		考虑到一个像素点被设置为采样100次，这100次中反射光线的条数基本和reflect_prob的值正相关，
		所以，100次的平均值也就是该像素点出反射光线和折射光线的叠加*/
        scattered = ray(rec.p, reflected);
    }
    else 
    {
        scattered = ray(rec.p, refracted);
    }

	 return true;
}

