#ifndef __CHECKWHATCOLLIDES__
#define __CHECKWHATCOLLIDES__
#include "getColor.h"


RayIntersect getNearestIntersect(const RayIntersect &sphereInt,const  RayIntersect &triangleInt,const RayIntersect &meshInt){
    vector<RayIntersect> distances = {};
    
    if(triangleInt.isThereIntersect)
        distances.push_back(triangleInt);
    if(meshInt.isThereIntersect)
        distances.push_back(meshInt);
    if(sphereInt.isThereIntersect)
        distances.push_back(sphereInt);    
    if(distances.size()==0)
    {
        //return empty bg
        return emptyRayIntersect;
    }else{
        //p("intersect at nearest");
    }
    RayIntersect nearest = distances[0];
    for(auto i: distances){
        if(i.lengthToTheOrigin < nearest.lengthToTheOrigin){
            nearest = i;
        }
    }
    return nearest;
}

RayIntersect getIntersect(const Ray &ray,const Scene &scene){ 
    auto sphereIntersect = checkSpheres(ray,scene);//Returns the touch point,  id and type of the shape
    auto triangleIntersect = checkTriangles(ray, scene); // ucgene degisyosa
    auto meshIntersect = checkMeshes(ray,scene);   //meshe degiyosa
    // if(sphereIntersect.isThereIntersect){
    //     p("sphere intersect");
    // }
    // // // // // if(triangleIntersect.isThereIntersect){
    // // // // //     p("triangleIntersect");
    // // // // // }
    // // // // // // if(meshIntersect.isThereIntersect){
    //     p("meshIntersect");
    // }
    return getNearestIntersect(sphereIntersect, triangleIntersect, meshIntersect);
    // lengthToThe.. en kucuk olani alcaz

    //enYakinNoktayiSec();
    
}

//Returns the color of the pixel
Vec3i checkWhatCollides(const Ray &ray,const Scene &scene ){
    RayIntersect rayIntersect = getIntersect(ray,scene);//idsini verir
    Vec3f pixelAsFloat=getColorOfTheIntersection(rayIntersect, scene,ray,scene.max_recursion_depth);
    
    Vec3i v ={
        .x=(int)(pixelAsFloat.x),
        .y=(int)(pixelAsFloat.y),
        .z=(int)(pixelAsFloat.z)
    };
    if(v.x > 255) v.x = 255;
    if(v.y > 255) v.y = 255;
    if(v.z > 255) v.z = 255;

    if(v.x<0) v.x = 0;
    if(v.y<0) v.y = 0;
    if(v.z<0) v.z = 0;
    return v;
    
    //p("123");
    //p(materialId);
    //Vec3i res = getColorOfTheIntersection(rayIntersect, scene,cameraId,ray);

    ///return res;

}



/***
 * 
 * 
 * 
 * 
 * o + t*d 
 * origin
 * t katsayi ***
 * * direction
 */


#endif