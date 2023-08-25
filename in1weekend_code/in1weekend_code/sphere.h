#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
public:
	sphere() {};
	sphere(const point3& cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

private:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	const double a = r.direction().length_squared();
	const double half_b = dot(oc, r.direction());
	const double c = oc.length_squared() - radius * radius;
	const double delta = half_b * half_b - a * c;

	if (delta < 0) return false;

	// delta >= 0 ʱ���ж�t�Ƿ����޶���Χ�ڣ�ȡ����۾�����
	double root = (-half_b - sqrt(delta)) / a;
	if (root < t_min || root > t_max) {
		root = (-half_b + sqrt(delta)) / a;
		if (root < t_min || root > t_max) return false;
	}

	// ��������������ཻ�����Ϣ
	rec.t = root;
	rec.p = r.at(root);
	vec3 outward_normal = (rec.p - center) / radius;  // Բ��ָ������ĳһ����԰뾶���õ��õ�ĵ�λ����
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;
}

#endif // !SPHERE_H
