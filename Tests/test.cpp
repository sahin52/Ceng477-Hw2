#include <iostream>
#include <stdarg.h>
#include "../printer.h"
#include "../jpeg.h"

using namespace std;

void rotateTest(){
    auto rot = rotate({0.5, -0.5, -2},45,{0.0, 0.0, 1.0});
    p(rot);
}

void texMapSphere(Scene scene, Sphere kure,int sphereId, Vec3f intersectionPoint, int nx, int ny ){
	int i,j;
	float theta, fi, r, x, y, z, u, v;
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
	/*
	if (scene.textures[scene.spheres[sphereId].texture_id].interpolation == "nearest"){
		vec3f color = fetch(round(i),round(j))
	}
	else if (scene.textures[scene.spheres[sphereId].texture_id].interpolation == "bilinear"){
		int p = floor(i);
		int q = floor(j);
		float dx = i-p;
		float dx = j-q;
		Vec3f color = Vec3fSum( ((p,q)*(1-dx)*(1-dy)), 
						(Vec3fSum( ((p+1,q)*(dx)*(1-dy)), 
							(Vec3fSum( ((p,q+1)*(1-dx)*(dy)),  ((p+1,q+1)*(dx)*(dy)) )) )) )
	}					// (p,q) lar değiştirilecek   TODOOOOOOOOOOOOOOO
	*/
}
void jpegTest(Scene &scene){
    char * filename = "earth_hd.jpg";
    string str = scene.textures[0].imageName;
    int width;
    int height;
    p("3");
    read_jpeg_header(filename,width,height);
    p("4");
    p(width);
    p(height);
    unsigned char * image = new unsigned char[width*height*3];
    read_jpeg(filename,image,width,height);
    unsigned char* anan = new unsigned char[200];
    for(int i=0;i<100;i++){
        cout << (int) image[i]<<"\n";
        if(i%3==2)
            p(fetch(scene,str,0,i/3));
    }

    for(int i=0;i<100;i++){
        anan[i]=image[i];
    }
    cout <<"anan\n";
    cout << anan<<"\n";
}

int main(int argc, char* argv[]){
    //rotateTest();
    Scene scene;
    p("1");
    p(argv[1]);
    scene.loadFromXml(argv[1]);
    p("2");
    // translate();
    // scale();
    jpegTest(scene);

}