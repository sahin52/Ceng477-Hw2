#ifndef __UTILSH_
#define __UTILSH_
#include <iostream>
#include "parser.h"
#include "ppm.h"
#include <math.h>
#include "matrix.h"
#include "jpeg.h"

#define PI 3.14159265

using namespace std;
using namespace parser;

parser::Vec3f Vec3fminus(const parser::Vec3f &v1,const  parser::Vec3f &v2){
    parser::Vec3f res;
    res.x = v1.x-v2.x;
    res.y = v1.y-v2.y;
    res.z = v1.z-v2.z;
    return res;
}

struct Image{
    std::string name;
    unsigned char * image;
    int width;
    int height;
};

vector<Image> Images ;
bool areImagesLoaded = false;

vector<Image> loadImages(const Scene &scene){
    vector<Image> res;

    scene.meshes[0].texture_id;
    vector<Texture> textures;
    for(auto tex: scene.textures){
        textures.push_back(tex);
        int width, height;
        char *filename = (char *) tex.imageName.c_str();
       //const char* temp = (const char*) tex.imageName;
        read_jpeg_header(filename,width,height);
        unsigned char * image = new unsigned char[width*height*3];
        read_jpeg(filename,image,width,height);
        Image temp;
        temp.name = tex.imageName;
        temp.width = width;
        temp.height = height;
        temp.image = image;
        Images.push_back(temp);
        res.push_back(temp);
    }
    if(!areImagesLoaded){
        areImagesLoaded = true;
        Images = res;
    }
    return res;
}

Vec3f fetch(const Scene &scene, std::string imageName, int column, int row){
    if(!areImagesLoaded){
        loadImages(scene);
    }
    for(auto image: Images){
        if(image.name == imageName){
            auto tempX = (int) image.image[3*(row*image.width+column)];
            auto tempY = (int) image.image[3*(row*image.width+column)+1];
            auto tempZ = (int) image.image[3*(row*image.width+column)+2];

            
            return {(float) tempX,(float) tempY,(float) tempZ};
        }
    }
    cout << "ERROR! Couldn't find the image!"<< imageName << "\n";
    for(auto image: Images){
        cout<< image.name<< " is im name  ";
    }
    return{0,0,0};
};

//Returns the width of an image
int getWidth(const Scene &scene, string imageName){
    if(!areImagesLoaded){
        loadImages(scene);
    }
    for(auto image: Images){
        if(image.name == imageName){
            return image.width;
        }
    }
    cout << "ERROR! couldn't find the image " << imageName << "\n";
    return 100;
}

//Returns the height of an image
int getHeight(const Scene &scene, string imageName){
    if(!areImagesLoaded){
        loadImages(scene);
    }
    for(auto image: Images){
        if(image.name == imageName){
            return image.height;
        }
    }
    cout << "ERROR! couldn't find the image on width: "<<imageName<<"\n";
    return 100;
}

Vec3f normalize(const Vec3f &v)
{
    Vec3f result;
    float uzunluk =  sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    result.x = v.x / uzunluk;
    result.y = v.y / uzunluk;
    result.z = v.z / uzunluk;
    return result;
}

Vec3f Vec3fDivision(const Vec3f &vec, const float &sayi){
    Vec3f res;
    res.x = vec.x/sayi;
    res.y = vec.y/sayi;
    res.z = vec.z/sayi;
    return res;
}
Vec3f Vec3fMultiply(const Vec3f &vec,const  float &sayi){
    Vec3f res;
    res.x = vec.x*sayi;
    res.y = vec.y*sayi;
    res.z = vec.z*sayi;
    return res;
}
Vec3f Vec3fSum(const Vec3f &v1,const  Vec3f &v2){
    Vec3f res;
    res.x = v1.x+v2.x;
    res.y = v1.y+v2.y;
    res.z = v1.z + v2.z; 
    return res;
}
float getLength(const Vec3f &v){
   return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
//Aradaki uzunlugu verir
float getDistance(const Vec3f &v1,const Vec3f &v2){
    Vec3f fark = Vec3fminus(v1,v2);
    return getLength(fark);
}
float determinant(const Vec3f &v0, const Vec3f &v1, const Vec3f &v2)
{
    return v0.x * (v1.y*v2.z - v2.y*v1.z)
            + v0.y * (v2.x*v1.z - v1.x*v2.z)
            + v0.z * (v1.x*v2.y - v1.y*v2.x);
}
float dotProduct(const Vec3f &v1,const Vec3f &v2){
    return v1.x*v2.x   +   v1.y*v2.y   +   v1.z*v2.z;
}

Vec3f Vec3itoVec3f(const Vec3i &vec3i){
    Vec3f res ={
        .x = (float) vec3i.x,
        .y = (float) vec3i.y,
        .z = (float) vec3i.z
    };
    return res;
}
Vec3i Vec3ftoVec3i(const Vec3f &v){
    return {
        .x = (int)v.x,
        .y = (int)v.y,
        .z = (int)v.z
    };
}
Vec3f Vec3fMultiply(const Vec3f &v1,const Vec3f &v2){
    return {
        .x = v1.x*v2.x,
        .y = v1.y*v2.y,
        .z = v1.z*v2.z,
    };
}

matrix4x4 matrix4x4_Multiply(matrix4x4 mat1, matrix4x4 mat2){
    matrix4x4 res;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            res.mat[i][j]+= mat1.mat[i][0]*mat2.mat[0][j];
            res.mat[i][j]+= mat1.mat[i][1]*mat2.mat[1][j];
            res.mat[i][j]+= mat1.mat[i][2]*mat2.mat[2][j];
            res.mat[i][j]+= mat1.mat[i][3]*mat2.mat[3][j];
        }
    }
    return res;
}


//Added newly
Vec4f matrix4x4_Vec4f_Multiply(matrix4x4 mat, Vec4f v){ //done with best performing algorithm
    Vec4f res;
    res.x = mat.mat[0][0]*v.x + mat.mat[0][1]*v.y + mat.mat[0][2]*v.z + mat.mat[0][3]*v.w;
    res.y = mat.mat[1][0]*v.x + mat.mat[1][1]*v.y + mat.mat[1][2]*v.z + mat.mat[1][3]*v.w;
    res.z = mat.mat[2][0]*v.x + mat.mat[2][1]*v.y + mat.mat[2][2]*v.z + mat.mat[2][3]*v.w;
    res.w = mat.mat[3][0]*v.x + mat.mat[3][1]*v.y + mat.mat[3][2]*v.z + mat.mat[3][3]*v.w;
    return res;
}


Vec3f rotate(const Vec3f &ilkhal,const float &aci,const Vec3f &vector){//TODO
    // Rx(-a)*Ry(b)*Rz(t)*Ry(-b)*Rx(a)
    if(ilkhal.x == 0. && ilkhal.y == 0. && ilkhal.z == 0.){
        return {0,0,0};
    }
    Vec4f res;
    Vec3f u = normalize(vector);
    Vec3f up; up.x=0; up.y=u.y; up.z=u.z;
    float upl = getLength(up);

    matrix4x4 Rx;
    Rx.mat[0][0]=1.;    Rx.mat[0][1]=0.;        Rx.mat[0][2]=0.;        Rx.mat[0][3]=0.;
    Rx.mat[1][0]=0.;    Rx.mat[1][1]=u.z/upl;   Rx.mat[1][2]=-u.y/upl;  Rx.mat[1][3]=0.;
    Rx.mat[2][0]=0.;    Rx.mat[2][1]=u.y/upl;   Rx.mat[2][2]=u.z/upl;   Rx.mat[2][3]=0.;
    Rx.mat[3][0]=0.;    Rx.mat[3][1]=0.;        Rx.mat[3][2]=0.;        Rx.mat[3][3]=1.;
    matrix4x4 Ry;
    Ry.mat[0][0]=upl;    Ry.mat[0][1]=0.;   Ry.mat[0][2]=-u.x;    Ry.mat[0][3]=0.;
    Ry.mat[1][0]=0.;     Ry.mat[1][1]=1.;   Ry.mat[1][2]=0.;      Ry.mat[1][3]=0.;
    Ry.mat[2][0]=u.x;   Ry.mat[2][1]=0.;   Ry.mat[2][2]=upl;     Ry.mat[2][3]=0.;
    Ry.mat[3][0]=0.;     Ry.mat[3][1]=0.;   Ry.mat[3][2]=0.;      Ry.mat[3][3]=1.;
    matrix4x4 Rz;
    Rz.mat[0][0]=cos(aci*PI/180.0);    Rz.mat[0][1]=-sin(aci*PI/180.0);     Rz.mat[0][2]=0.;    Rz.mat[0][3]=0.;
    Rz.mat[1][0]=sin(aci*PI/180.0);    Rz.mat[1][1]=cos(aci*PI/180.0);      Rz.mat[1][2]=0.;    Rz.mat[1][3]=0.;
    Rz.mat[2][0]=0.;                   Rz.mat[2][1]=0.;                     Rz.mat[2][2]=1.;    Rz.mat[2][3]=0.;
    Rz.mat[3][0]=0.;                   Rz.mat[3][1]=0.;                     Rz.mat[3][2]=0.;    Rz.mat[3][3]=1.;

    Vec4f ilk;
    ilk.x=ilkhal.x; ilk.y=ilkhal.y; ilk.z=ilkhal.z; ilk.w=1;

    res = matrix4x4_Vec4f_Multiply(Rz,matrix4x4_Vec4f_Multiply(Ry,matrix4x4_Vec4f_Multiply(Rx,ilk)));
    Ry.mat[0][2]=u.x; Ry.mat[2][0]=-u.x;
    Rx.mat[1][2]=u.y/upl; Rx.mat[2][1]=-u.y/upl;
    res = matrix4x4_Vec4f_Multiply(Rx,matrix4x4_Vec4f_Multiply(Ry,res));
    return {
        .x=res.x,
        .y=res.y,
        .z=res.z,
    };
 
}

Vec3f scale(const Vec3f &point,const Vec3f &scalingVector){///DONE
    Vec3f res;
    res.x = point.x * scalingVector.x;
    res.y = point.y * scalingVector.y;
    res.z = point.z * scalingVector.z;
    return res;

}
Sphere scale(const Sphere &sphere,const Vec3f &scalingVector){//DONE
    Sphere res;
    res.radius = sphere.radius*scalingVector.x;
    return res;
}

Vec3f translate(const Vec3f &point,const Vec3f &translationVector){//DONE
    Vec3f res;
    res.x = point.x + translationVector.x;
    res.y = point.y + translationVector.y;
    res.z = point.z + translationVector.z;
    return res;
}

#endif