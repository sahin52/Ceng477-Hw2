#ifndef __GETCOLOR__
#define __GETCOLOR__
#include "checkShapes.h"
//#include "generateRays.cpp"
using namespace std;
using namespace parser;

Vec3f getColorOfTheIntersection(const RayIntersect &rayIntersect,const Scene &scene,const Ray &ray, int max_recursion_depth);
Vec3f Irradiance(const PointLight &light,const Vec3f &point){
    float length = getDistance(light.position, point);
    float length_kare = length * length;
    Vec3f res ;
    res.x = light.intensity.x / length_kare;
    res.y = light.intensity.y / length_kare;
    res.z = light.intensity.z / length_kare;
    
    return res;
}

Vec3f Diffuse(const PointLight &light, const std::vector<Material> &materials,const  int &mat_id,const RayIntersect &ray){

    Vec3f irradiance = Irradiance(light, ray.intersectPoint);
    Vec3f w_i = normalize(Vec3fminus(light.position, ray.intersectPoint));
    Vec3f n = normalize(ray.normal);
    float cos = max(0.0f, dotProduct(w_i, n)) ;

    return {
        .x =  materials[mat_id].diffuse.x * cos * irradiance.x ,
        .y =  materials[mat_id].diffuse.y * cos * irradiance.y ,
        .z =  materials[mat_id].diffuse.z * cos * irradiance.z ,
    };
}

Vec3f Specular(const PointLight &light,const  RayIntersect &rayIntersect, Ray ray,const  Scene &scene,const  int &mat_id){
    
    Vec3f recieved_irr = Irradiance(light, rayIntersect.intersectPoint);
    Vec3f w_i = normalize(Vec3fminus(light.position, rayIntersect.intersectPoint));
    Vec3f w_0 = normalize(Vec3fminus(ray.start, rayIntersect.intersectPoint));

    float square_l = dotProduct(Vec3fSum( w_i, w_0), Vec3fSum( w_i, w_0)  ); 

    Vec3f half_v ;
    half_v.x = (w_i.x + w_0.x) / square_l;
    half_v.y = (w_i.y + w_0.y) / square_l;
    half_v.z = (w_i.z + w_0.z) / square_l;
    half_v = normalize(half_v);

    float cos = max(0.0f, dotProduct(rayIntersect.normal, half_v));
    float phong = scene.materials[mat_id].phong_exponent;

    return {
        .x = scene.materials[mat_id].specular.x * (float)pow(cos, phong) * recieved_irr.x ,
        .y = scene.materials[mat_id].specular.y * (float)pow(cos, phong) * recieved_irr.y ,
        .z = scene.materials[mat_id].specular.z * (float)pow(cos, phong) * recieved_irr.z ,
    };
}

//Returns whether a point is in shadow from the pointlight
bool golgedemi(const Vec3f &pointToCheck,const Scene &scene,const PointLight &currentLight){
    bool res=false;
    //intersection point ve light arasi ray
    Ray ray;
    ray.yon = Vec3fminus(pointToCheck,currentLight.position);//TODO yon dogru mu
    ray.start = currentLight.position;
    RayIntersect sphereIntersect = checkSpheres(ray,scene);
    //RayIntersect rayIntersect; //uzunluktan gitmek gerek ilk carpma noktasina
    if(sphereIntersect.isThereIntersect && 
            sphereIntersect.lengthToTheOrigin<(getDistance(pointToCheck,currentLight.position)-scene.shadow_ray_epsilon)){
        // p("---------");
        // p(scene.shadow_ray_epsilon);
        // p(sphereIntersect.lengthToTheOrigin);
        // p(getDistance(pointToCheck,currentLight.position));
        return true;
    }
    
    RayIntersect triangleIntersect = checkTriangles(ray,scene);
    if(triangleIntersect.isThereIntersect && triangleIntersect.lengthToTheOrigin<(getDistance(pointToCheck,currentLight.position)-scene.shadow_ray_epsilon*10)){
        return true;
    }
    RayIntersect meshIntersect = checkMeshes(ray,scene);
    if(meshIntersect.isThereIntersect && meshIntersect.lengthToTheOrigin<(getDistance(pointToCheck,currentLight.position)-scene.shadow_ray_epsilon*10)){
        return true;
    }

    return false;
};
Vec3f addLightFromLightSources(const RayIntersect &rayIntersect,const Scene &scene,const Ray &ray, Vec3f pixelAsFloat){
    int numberOfLights = scene.point_lights.size();
    int materialId=1;
    if(rayIntersect.shape.form == SPHERE){
        materialId = scene.spheres[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == TRIANGLE){
        materialId = scene.triangles[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == MESH){
        materialId = scene.meshes[rayIntersect.shape.id].material_id;
    }

    for(int i=0;i<numberOfLights;i++){
        PointLight currentLight = scene.point_lights[i];
        if(golgedemi(rayIntersect.intersectPoint, scene, currentLight)){ //Golgede kalmis do nothing
            //return pixelAsFloat;
        }else{  //isik vuruyor, o isiktan gelen isik degerlerini ekle
            pixelAsFloat = Vec3fSum(pixelAsFloat, Diffuse(currentLight, scene.materials, materialId, rayIntersect));
            pixelAsFloat = Vec3fSum(pixelAsFloat, Specular(currentLight, rayIntersect,ray, scene,materialId));
        }
    }
    return pixelAsFloat;
}
Vec3f *doesTheMaterialHaveMirrorness(const Scene &scene,const Shape &shape){
    int material_id;   
    if(shape.form==SPHERE){
        material_id = scene.spheres[shape.id].material_id;
    }else if(shape.form == TRIANGLE){
        material_id = scene.triangles[shape.id].material_id;
    }else{
        material_id = scene.meshes[shape.id].material_id;
    }
    Vec3f r = scene.materials[material_id].mirror;
    Vec3f * res= new Vec3f;
    *res = scene.materials[material_id].mirror;
    //res = &r;
    if(r.x !=0 || r.y!=0 || r.z!=0)
        return res;
    else 
        return nullptr;
    //return &(scene.materials[material_id].mirror);
            //TODO mirror var miyi ilk seferde calistir her seferinde hesaplama
    //return false;
}

Vec3f addTheYansimas(const RayIntersect &rayIntersect,const Scene &scene,const Ray &ray, Vec3f &pixelAsFloat, int max_recursion_depth){
    auto mirrorness =doesTheMaterialHaveMirrorness(scene, rayIntersect.shape);
    if(mirrorness && max_recursion_depth > 0){
        //giden rayin yonunde bulunan cismin rengine bakip katsayiyla carpip topluyosun
        //r=d − 2(d⋅n)n
        Vec3f wr_yansiyanRay = Vec3fSum(ray.yon ,Vec3fMultiply(rayIntersect.normal, -2 * dotProduct(ray.yon,rayIntersect.normal)));
        wr_yansiyanRay = normalize(wr_yansiyanRay);
        
        Vec3f epsilon =  Vec3fMultiply(wr_yansiyanRay, scene.shadow_ray_epsilon);

        Ray reflectance_ray = {
            .start=Vec3fSum( rayIntersect.intersectPoint , epsilon),
            .yon = wr_yansiyanRay
        };
        RayIntersect rayInt = getIntersect(reflectance_ray,scene);
        
        int material_id;   
        Shape shape = rayIntersect.shape;
        if(shape.form==SPHERE){
            material_id = scene.spheres[shape.id].material_id;
        }else if(shape.form == TRIANGLE){
            material_id = scene.triangles[shape.id].material_id;
        }else{
            material_id = scene.meshes[shape.id].material_id;
        }

        Vec3f reflected;
        if(rayInt.isThereIntersect)
        {
            reflected = getColorOfTheIntersection(rayInt, scene,reflectance_ray, max_recursion_depth-1);
            pixelAsFloat = Vec3fSum(pixelAsFloat,(Vec3fMultiply(reflected,scene.materials[material_id].mirror)));
        }
        
        return pixelAsFloat;        
        
    }else
        return pixelAsFloat;
}


Vec3f getColorOfTheIntersection(const RayIntersect &rayIntersect,const Scene &scene,const Ray &ray, int max_recursion_depth){

    int materialId = 0;
    Vec3f pixelAsFloat;
    // if(rayIntersect.isThereIntersect)
    //     return {100,100,100};
    // else
    //     return {200,50,125};
    if(!rayIntersect.isThereIntersect){
        return Vec3itoVec3f(scene.background_color);
    }
    
    if(rayIntersect.shape.form == SPHERE){
        materialId = scene.spheres[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == TRIANGLE){
        materialId = scene.triangles[rayIntersect.shape.id].material_id;
    }
    if(rayIntersect.shape.form == MESH){
        materialId = scene.meshes[rayIntersect.shape.id].material_id;
    }

    

    pixelAsFloat.x = scene.ambient_light.x* scene.materials[materialId].ambient.x;
    pixelAsFloat.y = scene.ambient_light.y* scene.materials[materialId].ambient.y;
    pixelAsFloat.z = scene.ambient_light.z* scene.materials[materialId].ambient.z;
    if(rayIntersect.isThereIntersect) 
    pixelAsFloat = addLightFromLightSources(rayIntersect, scene, ray, pixelAsFloat);
    //pixelAsFloat = addMirroring(pixelAsFloat);
    //Get the light from the light sources,
    pixelAsFloat = addTheYansimas(rayIntersect, scene, ray, pixelAsFloat,max_recursion_depth);
    //Get the yansima
    

    return pixelAsFloat;
    //return bisi;

}








#endif