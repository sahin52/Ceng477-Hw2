#ifndef __GENERATESRAYS__
#define __GENERATESRAYS__
#include "printer.h"


struct RaySabitleri{
    Vec3f vector_u;
    Vec3f vector_v;
    Vec3f sol_en_ust;
};
struct Ray
{
    Vec3f start;
    Vec3f yon;
};

Vec3f cross(const Vec3f &v1,const Vec3f &v2)
{
    float x = v1.y*v2.z - v1.z*v2.y;
    float y = v1.z*v2.x - v1.x*v2.z;
    float z = v1.x*v2.y - v1.y*v2.x;
    Vec3f result;
    result.x = x; result.y = y; result.z = z;
    return result;
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

/*
 * Generates A Ray
 * Ray will have an origin which is the poisition of the camera
 * and a direction which is the direction of the given pixel
 * 
 * 
 * 
*/
Ray generateRay(const int &row, const int &column,const Camera &cam,const RaySabitleri &raySabitleri)
{
    Vec3f vector_u = raySabitleri.vector_u;
    Vec3f vector_v = raySabitleri.vector_v;
    Vec3f sol_en_ust = raySabitleri.sol_en_ust;
    //leftten pixele olan mesafe
    float yatay_pixel_mesafesi = (cam.near_plane.y - cam.near_plane.x) * (column + 0.5) / cam.image_width ;
    //yukaridan pixele olan mesafe
    float dikey_pixel_mesafesi = (cam.near_plane.w - cam.near_plane.z) * (row + 0.5) / cam.image_height ;

    Vec3f hedef_pixel; //gidecegimiz pixel
    hedef_pixel.x = sol_en_ust.x + vector_u.x*yatay_pixel_mesafesi - vector_v.x*dikey_pixel_mesafesi;
    hedef_pixel.y = sol_en_ust.y + vector_u.y*yatay_pixel_mesafesi - vector_v.y*dikey_pixel_mesafesi;
    hedef_pixel.z = sol_en_ust.z + vector_u.z*yatay_pixel_mesafesi - vector_v.z*dikey_pixel_mesafesi;

    Ray ray;
    ray.start = cam.position;
    ray.yon.x = hedef_pixel.x - cam.position.x;
    ray.yon.y = hedef_pixel.y - cam.position.y;
    ray.yon.z = hedef_pixel.z - cam.position.z;
    ray.yon = normalize(ray.yon);

    return ray;
}



#endif