#ifndef __CHECKSHAPES__
#define __CHECKSHAPES__
#include "rayIntersect.h"

Vec3i checkWhatCollides(const Ray &ray,const Scene &scene );
RayIntersect getIntersect(const Ray &ray,const Scene &scene);
/**
 * returns the collision point and; type and id of the shape if a collision happens
 */
RayIntersect checkOneSphere(const Ray &ray,const Sphere &sphere,const  int &shapeId,const  Scene &scene){
    //P = point on the sphere, C is center, r is radius
    // ∥P−C∥2=r2  //sphere 
    // dot((P−C),(P−C))=r2
    //A ray is p=(O+tD) origin + Direction* a number, this will give us a point on the ray
    //In order to know if the ray and sphere intersect, we must give the point on the 
    //    sphere, the ray equation must be written in the sphere equation.
    //      dot((O+tD−C),(O+tD−C))=r2
    // ... -r2 = 0  iki tane t degeri iki tane gectiyse kucuk olani t degerleri negatifse alma
    // t degerleri pozitifse, kucuk olani aldim
    // O + tD 
    Vec3f center = scene.vertex_data[sphere.center_vertex_id];
    parser::Vec3f ray_origin_to_sp_center = Vec3fminus(ray.start , center);
    auto radius = sphere.radius;

    auto a = dotProduct(ray.yon,ray.yon);
    auto b = 2.0 * dotProduct(ray_origin_to_sp_center, ray.yon);
    auto c = dotProduct(ray_origin_to_sp_center,ray_origin_to_sp_center) - radius*radius;
    float discriminant = b*b - 4.0*a*c;
    if(discriminant<0){
        // string anan = "No hit to the sphere " + to_string(radius) + " by the ray: "+ to_string(ray.start.x) 
        // +" "+ to_string(ray.start.y)  +" "+ to_string(ray.start.z)  +" "+ to_string(ray.yon.x)  +" "+ to_string(ray.yon.y)  +" "+ to_string(ray.yon.z)
        //  ;
        //p(anan);
        RayIntersect rayIntersect;
        rayIntersect.isThereIntersect = false;
        return rayIntersect;
    }else{
        //p("intersected!!");
        auto t1 = (-b-sqrt(discriminant))/(2.0*a);
        // p("t1:");
        // p(t1);
        auto t2 = (-b+sqrt(discriminant))/(2.0*a);
        // p("t2:");
        // p(t2);

        if(t1<0){
            //p("empty Ray Intersect bc of wrong side");
            return emptyRayIntersect;
        }
        if(t1<t2){
            RayIntersect res;
            res.isThereIntersect = true;
            res.lengthToTheOrigin = t1;
            //Shape shape;
            res.shape.id = shapeId;
            res.shape.form = SPHERE;
            //res.shape = shape;
            // Vec3f intersectPoint;
            res.intersectPoint.x = ray.start.x + t1*ray.yon.x;
            res.intersectPoint.y = ray.start.y + t1*ray.yon.y;
            res.intersectPoint.z = ray.start.z + t1*ray.yon.z;
            //Vec3f temp = Vec3fminus();
            res.lengthToTheOrigin = getDistance(ray.start, res.intersectPoint);
            res.normal = Vec3fminus(res.intersectPoint, center);
            res.normal = Vec3fDivision(res.normal,radius);//normalize
            return res;
        }else{
            RayIntersect res;
            res.isThereIntersect = true;
            res.lengthToTheOrigin = t2;
            Shape shape;
            shape.id = shapeId;
            shape.form = SPHERE;
            res.shape = shape;
            Vec3f intersectPoint;
            intersectPoint.x = ray.start.x + t1*ray.yon.x;
            intersectPoint.y = ray.start.y + t1*ray.yon.y;
            intersectPoint.z = ray.start.z + t1*ray.yon.z;
            res.intersectPoint = intersectPoint ;
            res.normal = Vec3fminus(res.intersectPoint, center);
            res.normal = Vec3fDivision(res.normal,radius);
            return res;
        }
    }

    
    
}
/** Checks all spheres and returns the nearest RayIntersect To the camera
 * 
*/
RayIntersect checkSpheres(const Ray &ray,const Scene &scene){ 

    RayIntersect rayIntersect = emptyRayIntersect;
    vector<RayIntersect> intersects = {};
    int size = scene.spheres.size();
    for(int i = 0; i<size ;i++){
        RayIntersect rayIntersect = checkOneSphere(ray, scene.spheres[i],i,scene);
        if(rayIntersect.isThereIntersect)
            intersects.push_back(rayIntersect);
    }
    if(intersects.size()==0){
        return emptyRayIntersect;
    }
    RayIntersect nearest=intersects[0];
    for(auto i: intersects){
        if(i.lengthToTheOrigin<nearest.lengthToTheOrigin)
            nearest = i;
    }
    return nearest; // t => mesafe katsayisi



}


//*******************************************///


//*******************************************///
RayIntersect checkOneTriangle(const Ray &ray,const Scene &scene,const  int &TriangleId,const  Triangle &triangle,const Vec3f &v0,const  Vec3f &v1,const  Vec3f &v2){
   
    RayIntersect res;
    //return emptyRayIntersect;
    res.isThereIntersect = false;
    //res.lengthToTheOrigin;
    //res.intersectPoint;

    // Vec3f v0 = scene.vertex_data[triangle.indices.v0_id];
    // Vec3f v1 = scene.vertex_data[triangle.indices.v1_id];
    // Vec3f v2 = scene.vertex_data[triangle.indices.v2_id];

    Vec3f v1_v0 = Vec3fminus(v1,v0);
    Vec3f v2_v0 = Vec3fminus(v2,v0);
    Vec3f normalv = cross(v1_v0, v2_v0);

    //checking if direction of ray and normal are parallel
    float checkparallel = dotProduct(normalv, ray.yon);
    if (fabs(checkparallel) == 0.0)
    {
        return res;
    }


    float t = (determinant(Vec3fminus(v0,v1), Vec3fminus(v0,v2), Vec3fminus(v0,ray.start))) / checkparallel ;
    if(t <= 0.0f)
        return res;

    float gamma = (determinant(Vec3fminus(v0,v1),Vec3fminus(v0,ray.start), ray.yon)) / checkparallel ;
    if(gamma < 0 || gamma > 1)
        return res;

    float beta = (determinant(Vec3fminus(v0,ray.start), Vec3fminus(v0,v2), ray.yon)) / checkparallel ;
    if (beta + gamma > 1 || beta < 0  )
        return res;

 
    //finding if intersected point inside of triangle
    Vec3f point;
    point.x = ray.start.x + t*ray.yon.x ;
    point.y = ray.start.y + t*ray.yon.y ;
    point.z = ray.start.z + t*ray.yon.z ;

    float length = sqrt((point.x-ray.start.x)*(point.x-ray.start.x)+(point.y-ray.start.y)*(point.y-ray.start.y)+(point.z-ray.start.z)*(point.z-ray.start.z));

    // if none of the ifs above true than point is inside triangle
    res.normal = normalize(normalv);
    res.isThereIntersect = true;
    res.lengthToTheOrigin = length;
    res.intersectPoint = point;
    res.shape.form=TRIANGLE;
    res.shape.id = TriangleId;
    // isiktan pointe kesişim var mı hesapla
    //res.isThereIntersectwithLight = true;


    return res;
}
RayIntersect checkTriangles(const Ray &ray,const Scene &scene){
    // RayIntersect checkOneTriangle(Ray ray,Triangle triangle,int cameraId);

    RayIntersect rayIntersect = emptyRayIntersect;
    vector<RayIntersect> intersects={};
    int size = scene.triangles.size();
    for(int i=0;i<size;i++){
        Triangle triangle = scene.triangles[i];
        Vec3f v0 = scene.vertex_data[triangle.indices.v0_id];
        Vec3f v1 = scene.vertex_data[triangle.indices.v1_id];
        Vec3f v2 = scene.vertex_data[triangle.indices.v2_id];
        RayIntersect current = checkOneTriangle(ray,scene, i, triangle,v0,v1,v2);
        if(i==0)   rayIntersect = current;
        else if(current.isThereIntersect && current.lengthToTheOrigin<rayIntersect.lengthToTheOrigin){
            rayIntersect = current;
        }
        //intersects.push_back();
    }
    return rayIntersect;
};
//*******************************************///

//////?????????????????????????/////////// MESH START
RayIntersect checkOneMesh(const Ray &ray,const Mesh &mesh,const int &meshId,const Scene &scene){
    //mesh ucgenlerden olusur, mesh icerisindeki tum faceleri bir ucgen haline getirip checkonetriangle'da kullanabiliriz
    RayIntersect res = emptyRayIntersect;
    //return res;
    vector<RayIntersect> intersects = {};
    for(auto face: mesh.faces){
        Triangle tempTriangle;
        tempTriangle.indices=face;
        // tempTriangle.indices.v1_iface.v2_id;
        tempTriangle.material_id = mesh.material_id;
        Vec3f v0 = scene.vertex_data[tempTriangle.indices.v0_id];
        Vec3f v1 = scene.vertex_data[tempTriangle.indices.v1_id];
        Vec3f v2 = scene.vertex_data[tempTriangle.indices.v2_id];
        res = checkOneTriangle(ray,scene,1,tempTriangle,v0,v1,v2);
        res.shape.form = MESH;
        res.shape.id = meshId;
        if(res.isThereIntersect)
            intersects.push_back(res);
        //res.shape=mesh;
    }
    if(intersects.size()==0){
        return emptyRayIntersect;
    }
    RayIntersect nearest = intersects[0];
    for(auto intersect: intersects){
        if(intersect.lengthToTheOrigin < nearest.lengthToTheOrigin){
            nearest = intersect;
        }
    }
    return nearest;


    return res;
}

RayIntersect checkMeshes(const Ray &ray,const Scene &scene){
    RayIntersect res = emptyRayIntersect;
    vector<RayIntersect> rvector={};
    float size = scene.meshes.size();
    for(int i=0;i<size ;i++){
        RayIntersect temp = checkOneMesh(ray,scene.meshes[i],i,scene);
        if(temp.isThereIntersect)
            rvector.push_back(temp);
    }
    if(rvector.size()==0) return emptyRayIntersect;
    RayIntersect nearest = rvector[0];
    for(auto i:rvector){
        if(i.lengthToTheOrigin<nearest.lengthToTheOrigin)
            nearest = i;
    }
    return nearest;
    
    // RayIntersect rayIntersect;
    // rayIntersect.isThereIntersect = false;
};
//////?????????????????????????/////////// MESH END






#endif