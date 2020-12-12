#ifndef __TMCPP__
#define __TMCPP__
#include <iostream>
#include <math.h>
#include "applyTransformations.h"

#define PI 3.14159265
using namespace std;

void texMapSphere(Scene scene,Sphere kure, Vec3f point ,int nx, int ny ){
	int i,j;
	float theta, fi, r, x, y, z, u, v;
	r = kure.radius;
	Vec3f center = scene.vertex_data[kure.center_vertex_id];
	x = point.x - center.x;
	y = point.y - center.y;
	z = point.z - center.z;

	theta = acos(y/r);
	fi = atan2(z,x);

	u = (-fi + PI ) / (2*PI);
	v = theta / PI;
				//  where nx is texture width and ny is texture height
	i = (int) (u*nx);
	j = (int) (v*ny);
	/*
	if (interpolation == "neares"){
		vec3f color = fetch(round(i,j))
	}
	else if (interpolation == "bilinear"){
		4 noktanin ortalamasını al
	}
	*/
}
#endif