#ifndef __TMCPP__
#define __TMCPP__
#include <iostream>
#include <math.h>
#include "applyTransformations.h"

#define PI 3.14159265
using namespace std;

Vec3f texMapSphere(Scene scene, Sphere kure,int sphereId, Vec3f intersectionPoint, int nx, int ny ){
	float theta, fi, r, x, y, z, u, v, i, j;
	r = kure.radius;
	Vec3f center = scene.vertex_data[kure.center_vertex_id];
	x = intersectionPoint.x - center.x;
	y = intersectionPoint.y - center.y;
	z = intersectionPoint.z - center.z;

	theta = acos(y/r);
	fi = atan2(z,x);

	u = (-fi + PI ) / (2*PI);
	v = theta / PI;
				//  where nx is texture width and ny is texture height
	i =  (u*nx);
	j =  (v*ny);
	string n = scene.textures[scene.spheres[sphereId].texture_id].imageName;
	
	Vec3f color;
	if (scene.textures[scene.spheres[sphereId].texture_id].interpolation == "nearest"){
		int k = (int)(i+0.5) ;//EN YAKIN;
		int l = (int)(j+0.5) ;
		color = fetch(scene,n,k,l);
	}
	else if(scene.textures[scene.spheres[sphereId].texture_id].interpolation == "bilinear"){
		int p = floor(i);
		int q = floor(j);
		float dx = i-p;
		float dy = j-q;
		color = Vec3fSum( (Vec3fMultiply(fetch(scene,n,p,q),((1-dx)*(1-dy))) ), 
						(Vec3fSum( ( Vec3fMultiply(fetch(scene,n,p+1,q),((dx)*(1-dy))) ), 
							(Vec3fSum( (Vec3fMultiply(fetch(scene,n,p,q+1),((1-dx)*(dy))) ),  Vec3fMultiply(fetch(scene,n,p+1,q+1),((dx)*(dy))) )) )) );
	}					// (p,q) lar değiştirilecek   TODOOOOOOOOOOOOOOO
	else{
		p("Different type of texture interpolation on sphere error");
	}
	return color;
} 

Vec3f texMapTriangle(RayIntersect rayinter,Scene scene, int ucgen_id, Vec3f intersectionPoint ){
	



	
}
#endif