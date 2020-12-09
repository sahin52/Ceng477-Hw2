#ifndef __UTILSH_
#define __UTILSH_
#include <iostream>
#include "parser.h"
#include "ppm.h"
#include <math.h>
#include "matrix.h"

using namespace std;
using namespace parser;

parser::Vec3f Vec3fminus(const parser::Vec3f &v1,const  parser::Vec3f &v2){
    parser::Vec3f res;
    res.x = v1.x-v2.x;
    res.y = v1.y-v2.y;
    res.z = v1.z-v2.z;
    return res;
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


Vec3f rotate(Vec3f ilkhal, float aci, Vec3f vector){//TODO

}

Vec3f scale(Vec3f  point, Vec3f scalingVector){///DONE
    Vec3f res;
    res.x = point.x * scalingVector.x;
    res.y = point.y * scalingVector.y;
    res.z = point.z * scalingVector.z;

}
Sphere scale(Sphere sphere, Vec3f scalingVector){//DONE
    Sphere res;
    res.radius = sphere.radius*scalingVector.x;
    return res;
}

Vec3f translate(Vec3f point, Vec3f translationVector){//DONE
    Vec3f res;
    res.x = point.x + translationVector.x;
    res.y = point.y + translationVector.y;
    res.z = point.z + translationVector.z;
    return res;
}

#endif